/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "ModemSerial.hpp"

using namespace modemdriver;

ModemSerial::ModemSerial(std::string const& name)
    : ModemSerialBase(name)
{
}

ModemSerial::ModemSerial(std::string const& name, RTT::ExecutionEngine* engine)
    : ModemSerialBase(name, engine)
{
}

ModemSerial::~ModemSerial()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See ModemSerial.hpp for more detailed
// documentation about them.

bool ModemSerial::configureHook()
{
    if (! ModemSerialBase::configureHook())
        return false;
    return true;
}
bool ModemSerial::startHook()
{
    if (! ModemSerialBase::startHook())
        return false;
    return true;
}
void ModemSerial::updateHook()
{
    ModemSerialBase::updateHook();
}
void ModemSerial::errorHook()
{
    ModemSerialBase::errorHook();
}
void ModemSerial::stopHook()
{
    ModemSerialBase::stopHook();
}
void ModemSerial::cleanupHook()
{
    ModemSerialBase::cleanupHook();
}
