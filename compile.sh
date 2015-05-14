#!/bin/bash
#Raspberry Pi Nokia 5110 display system info build script
echo "Compiling..."
(g++ -Wall sysInfo.cpp nokia5110.cpp -lwiringPi -o sysInfo) || exit;
echo "Complilation complated"
if [ "$1" == "run" ]; then
	echo "Running..."
	sudo ./sysInfo
fi;