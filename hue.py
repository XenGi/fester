#!/usr/bin/env python

import requests
import json
import time
import random


hue = {}
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


def main():
    r = requests.put("http://10.0.0.247/api/newdeveloper/lights/1/state/", data=json.dumps({'on': True, 'hue': hue['happy'], 'sat': sat, 'bri': bri }))
    r = requests.put("http://10.0.0.247/api/newdeveloper/lights/2/state/", data=json.dumps({'on': True, 'hue': v, 'sat': sat, 'bri': bri }))
    r = requests.put("http://10.0.0.247/api/newdeveloper/lights/3/state/", data=json.dumps({'on': True, 'hue': v, 'sat': sat, 'bri': bri }))
    time.sleep(10)

if __name__ == '__main__':
    r = requests.put("http://10.0.0.247/api/newdeveloper/lights/1/state/", data=json.dumps({'on': False}))
    r = requests.put("http://10.0.0.247/api/newdeveloper/lights/2/state/", data=json.dumps({'on': False}))
    r = requests.put("http://10.0.0.247/api/newdeveloper/lights/3/state/", data=json.dumps({'on': False}))

    try:
        main()
    except KeyboardInterrupt:
        r = requests.put("http://10.0.0.247/api/newdeveloper/lights/1/state/", data=json.dumps({'on': False}))
        r = requests.put("http://10.0.0.247/api/newdeveloper/lights/2/state/", data=json.dumps({'on': False}))
        r = requests.put("http://10.0.0.247/api/newdeveloper/lights/3/state/", data=json.dumps({'on': False}))

