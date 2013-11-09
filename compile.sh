#!/bin/bash

QEO_HOME="/home/xengi/MyDocs/projects/qeo_hack/QeoSDK-0.15.0"

cd fester
make

./test_fester.py
