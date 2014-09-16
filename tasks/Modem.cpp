/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Modem.hpp"
#include <vector>

using namespace modemdriver;

Modem::Modem(std::string const& name)
    : ModemBase(name), current_message(10)
{
}

Modem::Modem(std::string const& name, RTT::ExecutionEngine* engine)
    : ModemBase(name, engine), current_message(10)
{
}

Modem::~Modem()
{
}

bool Modem::setDistance_request_interval(double value)
{
 distance_timeout = base::Timeout(base::Time::fromSeconds(value));
 return(modemdriver::ModemBase::setDistance_request_interval(value));
}


/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Modem.hpp for more detailed
// documentation about them.

bool Modem::configureHook()
{
    if (! ModemBase::configureHook())
        return false;
    return true;
}
bool Modem::startHook()
{
    if (! ModemBase::startHook())
        return false;
    updateDynamicProperties();
    return true;
}
void Modem::updateHook()
{
    ModemBase::updateHook();
    if(distance_timeout.elapsed())
    {
        distance_timeout.restart();
        ack_driver.requestRange(); 
    }    
    //If the ack driver has nothing to send
    if (!ack_driver.isSending()){
        //If the whole current message is send
        if (current_message.empty()){
            modemdriver::modem_message to_send;
            if (_data_in.readNewest(to_send) == RTT::NewData){
                for (int i=0; i < to_send.message.size(); i++){
                    current_message.push_back(to_send.message.c_str()[i]);
                }
            }
        //If there is something to send of the current_message
        } else {
            ack_driver.writePacket(current_message[0]);
            current_message.pop_front();
        }
    }
}
void Modem::errorHook()
{
    ModemBase::errorHook();
}
void Modem::stopHook()
{
    ModemBase::stopHook();
}
void Modem::cleanupHook()
{
    ModemBase::cleanupHook();
}
