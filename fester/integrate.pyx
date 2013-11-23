# -*- coding: utf-8 -*-
cdef extern from "main2.h":
    ctypedef void (*cheesefunc)(char *name, void *user_data)
    int do_setup(cheesefunc user_func, void *user_data)
    int do_teardown()
    void do_send_message(char* origin, char* message)

cdef void callback(char *message, void *f):
    (<object>f)(message)

cdef class QeoApi:
    cdef object my_f

    def setup(self, f):
        do_setup(callback, <void*>f)
        self.my_f = f

    def teardown(self):
        do_teardown()

    def send_message(self, origin, message):
        cdef bytes py_origin = origin.encode()
        cdef char* c_origin = py_origin
        cdef bytes py_message = message.encode()
        cdef char* c_message= py_message
         
        do_send_message(c_origin, c_message)
            
