#!/bin/bash

# This script generates C++ files for any IDL files present in your project's Source/DDS/IDL/ directory. 
# This should be run from the SharedDDS/Scripts/ directory, unless you modify the paths below to better suit your needs. 
# Be sure to copy the IDL files you need from SharedDDS/IDL/ to Source/DDS/IDL/

for files in ../../Source/DDS/IDL/*.idl;
do
~/RTI/ndds.5.1.0/scripts/rtiddsgen -language C++ -replace -namespace -stringSize 255 -sequenceSize 100 -d ../../Source/DDS/Generated/ -inputIdl $files
done
