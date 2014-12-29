#!/bin/bash
#Raspberry Pi Nokia 5110 display system info build script

g++ -Wall sysInfo.cpp nokia5110.cpp -lwiringPi -o sysInfo