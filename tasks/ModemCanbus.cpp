/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "ModemCanbus.hpp"

using namespace modemdriver;

ModemCanbus::ModemCanbus(std::string const& name)
    : ModemCanbusBase(name)
{
}

ModemCanbus::ModemCanbus(std::string const& name, RTT::ExecutionEngine* engine)
    : ModemCanbusBase(name, engine)
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
    return true;
}
bool ModemCanbus::startHook()
{
    if (! ModemCanbusBase::startHook())
        return false;
    return true;
}
void ModemCanbus::updateHook()
{
    ModemCanbusBase::updateHook();
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
