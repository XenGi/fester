#!/usr/bin/env python2
# -*- coding: utf-8 -*-

import RPi.GPIO as GPIO

from fester.integrate import doit

if __name__ == '__main__':
	GPIO.setmode(GPIO.BCM)
	
	while True:
	  if (GPIO.input(17)):
	    print("Phone handle lifted")
		result = doit()
	
    print result
