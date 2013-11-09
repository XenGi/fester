#!/bin/bash

rm -f fester/*.so
QEO_HOME="/home/pi/sdk//QeoSDK-0.15.0" ./setup.py build_ext -i
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/pi/sdk/QeoSDK-0.15.0/c/lib/arm-linux-gnueabihf ./test_fester
