#! /usr/bin/env ruby
require 'orocos'
include Orocos
Orocos.initialize

Orocos::run 'modemdriver_cantest' do 
#    Orocos::TaskContext.get("can")
#    Orocos::TaskContext.get("modemdriver")
    
end
