/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Modem.hpp"

using namespace modemdriver;

Modem::Modem(std::string const& name)
    : ModemBase(name)
{
}

Modem::Modem(std::string const& name, RTT::ExecutionEngine* engine)
    : ModemBase(name, engine)
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
    std::vector<char> to_send;
    if(distance_timeout.elapsed())
    {
        distance_timeout.restart();
        ack_driver.requestRange(); 
    }
//    if (_data_in.read(to_send) == RTT::NewData){
//        for (int i=0; i < to_send.size(); i++){
//            //ack_driver send
//        }
//    }
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
