#! /usr/bin/env ruby
require 'orocos'
include Orocos
Orocos.initialize

Orocos::run 'modemdriver_cantest' do 
    can = Orocos::TaskContext.get("cantest")
    modemdriver = Orocos::TaskContext.get("modemdriver")
    can.device = "can0"
    can.configure
    can.watch("modem", 0x504, 0x7FF)
    can.modem.connect_to modemdriver.can_in 
    modemdriver.can_out.connect_to can.in
    modemdriver.configure
    #modemdriver.distance_request_interval = 4
    can.start
    modemdriver.start
    loop do
        sleep 0.1
    end
end

