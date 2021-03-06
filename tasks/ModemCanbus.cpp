/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "ModemCanbus.hpp"
#include <modemdriver_tritech/ModemParser.hpp>
#include <modemdriver_tritech/AckDriverStats.hpp>
#include <sysmon/SysMonTypes.hpp>


using namespace modemdriver;
#define MAX_CAN_SIZE 8
#define MODEM_ID 0x500
#define BITRATE 40

ModemCanbus::ModemCanbus(std::string const& name)
    : ModemCanbusBase(name), send_data_buffer(500), receive_data_buffer(500)
{
}

ModemCanbus::ModemCanbus(std::string const& name, RTT::ExecutionEngine* engine)
    : ModemCanbusBase(name, engine)//, send_data_buffer(500), receive_data_buffer(500)
{
}

ModemCanbus::~ModemCanbus()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See ModemCanbus.hpp for more detailed
// documentation about them.

bool ModemCanbus::configureHook()
{
    if (! ModemCanbusBase::configureHook())
        return false;

    ack_driver.setDriver(this);
    return true;
}
bool ModemCanbus::startHook()
{
    count = 0;
    if (! ModemCanbusBase::startHook())
        return false;

    return true;
}
void ModemCanbus::updateHook()
{
    ModemCanbusBase::updateHook();
    canbus::Message msg;
    if (_can_in.read(msg) == RTT::NewData){
        for (int i=0; i < msg.size; i++){
            receive_data_buffer.push_back(msg.data[i]);
        }
    }
    ack_driver.process();
    AckDriverStats s = ack_driver.getDriverStats();
    _stats.write(s);
    if (count > 10) {
            std::cout << "Last send Ack Bit:" <<(int) s.last_send_ack_bit << std::endl; 
            std::cout << "Last receive Ack Bit:" <<(int) s.last_receive_ack_bit << std::endl; 
            std::cout << "Acked Data Packets:" <<(int) s.acked_data_packets << std::endl; 
            std::cout << "Acked Protocol Packets:" <<(int) s.acked_protocol_packets << std::endl; 
            std::cout << "Received Protocol Packets:" <<(int) s.received_protocol_packets << std::endl; 
            std::cout << "Received Data Packets:" <<(int) s.received_data_packets << std::endl; 
            std::cout << "Last valid packet (since seconds):" << (base::Time::now()-s.last_valid_packet).toSeconds() << std::endl; 
            std::cout << "Retry:" <<(int) s.retries << std::endl; 
            std::cout << "Rejected Packets:" <<(int) s.rejected_packets << std::endl; 

            count = 0;
    }
    count++;
    if (ack_driver.hasReceivedData()){
        uint8_t data = ack_driver.getNextReceivedData();
        std::vector<char> message (1);
        message[0] = data;
        std::string message_str(message.begin(), message.end());
        modemdriver::modem_message m_message;
        m_message.message = message_str;
        m_message.time = base::Time::now();
        _data_out.write(m_message);
        
        /*if (data < 32){
            sysmon::ModemSubstate substate;
            substate.time = base::Time::now();
            substate.substate = data;
            _out_modem_substates.write(substate);
        }*/
    }

}
void ModemCanbus::errorHook()
{
    ModemCanbusBase::errorHook();
}
void ModemCanbus::stopHook()
{
    ModemCanbusBase::stopHook();
}
void ModemCanbus::cleanupHook()
{
    ModemCanbusBase::cleanupHook();
}
size_t ModemCanbus::process(){
    if ((int) last_process.toSeconds() != (int) base::Time::now().toSeconds()){
        last_process = base::Time::now();
        send_last_second = 0;
    }
    uint8_t can_data[MAX_CAN_SIZE];
    //Can Packets if there is bandswith and data
    while (send_last_second < BITRATE && !send_data_buffer.empty()){
        std::cout << "send buffer is not empty" << std::endl;
        size_t size = 0;
        //Fill Canpackets if there is space in the packet and data and bandswidth
        while (send_last_second < BITRATE && size < MAX_CAN_SIZE && !send_data_buffer.empty()){
            can_data[size++] = send_data_buffer[0];
            send_data_buffer.pop_front();
            send_last_second += 8;
        } 
        if (size) {
            canbus::Message msg;
            msg.time = base::Time::now();
            msg.size = size;
            msg.can_id = MODEM_ID;
            for (int i=0; i<size; i++){
                msg.data[i] = can_data[i];
            }
            _can_out.write(msg);
        }
    }
    return send_data_buffer.size();
    
}
void ModemCanbus::writeSlowly(uint8_t const *buffer, size_t buffer_size){
    for (int i=0; i < buffer_size; i++){
        send_data_buffer.push_back(buffer[i]);
    }
}

int ModemCanbus::getPacket(std::vector<uint8_t> &out){
    //std::cout << "getPacket is called" << std::endl;
    int ret = 0;
    do {
        ret = 0;
        if (!receive_data_buffer.empty()){
            std::vector<uint8_t> in;
            in.clear();
            for (int i = 0; i < receive_data_buffer.size(); i++){
                in.push_back(receive_data_buffer[i]);
            }
            ret = modemdriver::Parser::extractPacket(in,  out);
            std::cout << "Got a valid Packet!" << std::endl;
        }
        size_t to_skip;
        if (ret < 0){
            to_skip = ret * -1;
        } else {
            to_skip = ret;
        }
        for (int i = 0; i < to_skip; i++){
            receive_data_buffer.pop_front();
        } 
    } while (ret < 0);
    if (ret) {
        std::cout << "found a packet" << std::endl;
    }
    return ret; 
}
