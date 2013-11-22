#!/usr/bin/env python

import requests
import json
import time
import random

def main():
	hue = 0
	step = 1820
	while True:
		hue = (hue + step) % 65564
		hue = random.randint(0, 65564)
		print "on"
		r = requests.put("http://10.0.0.247/api/newdeveloper/lights/1/state/", data=json.dumps({'on': True, 'hue': hue}))
		r = requests.put("http://10.0.0.247/api/newdeveloper/lights/2/state/", data=json.dumps({'on': True, 'hue': hue}))
		r = requests.put("http://10.0.0.247/api/newdeveloper/lights/3/state/", data=json.dumps({'on': True, 'hue': hue}))
		print r.json()
		time.sleep(2)
		#print "off"
		#r = requests.put("http://10.0.0.247/api/newdeveloper/lights/2/state/", data=json.dumps({'on': False}))
		print r.json()
		time.sleep(2)

if __name__ == '__main__':
	r = requests.put("http://10.0.0.247/api/newdeveloper/lights/1/state/", data=json.dumps({'on': False}))
	r = requests.put("http://10.0.0.247/api/newdeveloper/lights/2/state/", data=json.dumps({'on': False}))
	r = requests.put("http://10.0.0.247/api/newdeveloper/lights/3/state/", data=json.dumps({'on': False}))
	time.sleep(3)

	try:
		main()
	except KeyboardInterrupt:
		r = requests.put("http://10.0.0.247/api/newdeveloper/lights/1/state/", data=json.dumps({'on': False}))
        	r = requests.put("http://10.0.0.247/api/newdeveloper/lights/2/state/", data=json.dumps({'on': False}))
        	r = requests.put("http://10.0.0.247/api/newdeveloper/lights/3/state/", data=json.dumps({'on': False}))
	
