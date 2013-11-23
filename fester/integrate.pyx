# -*- coding: utf-8 -*-

from threading import Thread

cdef extern from "main2.h":
    ctypedef void (*cheesefunc)(char *name, void *user_data)
    
    int do_setup()
    void do_start_receiving(cheesefunc user_func, void *user_data)
    void do_stop_receiving()

    int do_teardown()
    void do_send_message(char* origin, char* message)

cdef void callback(char *message, void *f):
    (<object>f)(message)

cdef class QeoApi:
    cdef object my_f
    cdef object thread
    
    def setup(self):
        return do_setup()

    def start_receiving(self, f):
        self.my_f = f
        def wait_for_messages(func):
            do_start_receiving(callback, <void*>func)
       
        self.thread = Thread(target=wait_for_messages, args=(f,)) 
        self.thread.start()

    def stop_receiving(self):
        do_stop_receiving()
        self.thread.join()

    def teardown(self):
        do_teardown()

    def send_message(self, origin, message):
        cdef bytes py_origin = origin.encode()
        cdef char* c_origin = py_origin
        cdef bytes py_message = message.encode()
        cdef char* c_message= py_message
         
        do_send_message(c_origin, c_message)
            
