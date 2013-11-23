#!/usr/bin/env python
# -*- coding: utf-8 -*-

import mpd
import time
from fester.integrate import QeoApi # setup, teardown, send_message
import random
from unidecode import unidecode

def bla(data):
    print ">>>", data

class Qeompd(object):

    def __init__(self):
        self.qeo_status = setup(bla)
        if self.qeo_status != 0:
            print "ERRRROOOOOORRRR"
        self.client = mpd.MPDClient() 
        self.client.timeout = 10
        self.client.connect("localhost",6600)
    

    def play(self, mood):
        self.client.clear()
        self.client.load(mood)
        self.client.play()

    def post_song(self):
        status = self.client.currentsong()
        text = 'u%s - %s' % (status['artist'], status['title'])
        print "Sende", text
        send_message('camerapi', unidecode(text))

    def teardown(self):
        teardown()
        

if __name__ == '__main__':
    #myqeompd = Qeompd()
  
    q = QeoApi()
    q.setup(bla) 
    while True:
        try: 
            time.sleep(5)
        except:
            break
        #sample = random.sample(["sad", "happy", "calm", "energy"], 1)[0]
        #print sample
        #myqeompd.play(sample)
        #myqeompd.post_song()

        #time.sleep(5)

    #myqeompd.teardown()
    q.teardown()
