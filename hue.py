#!/usr/bin/env python

import requests
import json
import time
import random

from fester.integrate import QeoApi

hue = {}

CALM_COLORS = [(13122, 211, 144), ]
ENERGY_COLORS = [(13122, 211, 253), (13122, 211, 253), (47175, 211, 253)]
HAPPY_COLORS = [(16352, 45, 237), (60234, 253, 230), (47124, 253, 177)]
SAD_COLORS = [(51632, 253, 228), (49054, 226, 228), (51934, 253, 288)]

COLORS = {
    'calm': CALM_COLORS,
    'energy': ENERGY_COLORS,
    'happy': HAPPY_COLORS,
    'sad': SAD_COLORS
}

hue['calm']   = (13122,13122,13122)
hue['energy'] = (13122,13122,47175)
hue['happy']  = (16352,60234,47124)
hue['sad']    = (51632,49054,51934)

bri = {}
bri['calm']   = (144,144,144)
bri['energy'] = (253,253,253)
bri['happy']  = (237,230,177)
bri['sad']    = (228,228,288)

sat = {}
sat['calm']   = (211,211,211)
sat['energy'] = (211,211,211)
sat['happy']  = (45,253,253)
sat['sad']    = (253,226,253)

class Light(object):

    def __init__(self, light_id):
        self.light_id = light_id

    def make_request(self, data):
        url = "http://10.0.0.247/api/newdeveloper/lights/%d/state/" % self.light_id
        r = requests.put(url, data=json.dumps(data))

    def turn_on(self):
        data = {'on': True}
        self.make_request(data)

    def turn_off(self):
        data = {'on': False}
        self.make_request(data)
    
    def change_hsb(self, h, s, b):
        data = {
            'hue': h, 
            'sat': s, 
            'bri': b
        }
        self.make_request(data)

def set_mood(mood):
    colors = COLORS[mood]
    lights = [Light(1), Light(2), Light(3)]
    for idx, light in enumerate(lights):
        light.turn_on()
        color_idx = idx % len(colors)
        light.change_hsb(*colors[color_idx])
        
def my_callback(message):
    if message in COLORS.keys():
        set_mood(message)
    else:
        print "Ignored unknown mood", message

qeo = QeoApi()

if __name__ == '__main__':
    r = qeo.setup()
    if r == 0:
        qeo.start_receiving(my_callback)
        try:
            while True: time.sleep(1)
        except KeyboardInterrupt:
            qeo.stop_receiving()
            qeo.teardown()
             
        
