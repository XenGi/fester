/************* COPYRIGHT AND CONFIDENTIALITY INFORMATION *********************
 **                                                                          **
 ** Copyright (c) 2013 Technicolor                                           **
 ** All Rights Reserved                                                      **
 **                                                                          **
 ** This program contains proprietary information which is a trade           **
 ** secret of TECHNICOLOR and/or its affiliates and also is protected as     **
 ** an unpublished work under applicable Copyright laws. Recipient is        **
 ** to retain this program in confidence and is not permitted to use or      **
 ** make copies thereof other than as permitted in a written agreement       **
 ** with TECHNICOLOR, UNLESS OTHERWISE EXPRESSLY ALLOWED BY APPLICABLE LAWS. **
 **                                                                          **
 ******************************************************************************/

#include <assert.h>
#include <semaphore.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <inttypes.h>
#include <qeo/api.h>
#include <qeo/device.h>
#include <Python.h>

#include "main2.h"
#include "QSimpleChat_ChatMessage.h"
// #include "integrate.h"

static volatile bool _quit = false;
static qeo_platform_device_id _id;

static cheesefunc* my_callback;
void *my_user_data; 

/* ===[ Chat message listeners ]============================================= */

static void on_chat_message(const qeo_event_reader_t *reader,
                            const void *data,
                            uintptr_t userdata)
{
    org_qeo_sample_simplechat_ChatMessage_t *msg = (org_qeo_sample_simplechat_ChatMessage_t *)data;

    /* Whenever a new data sample arrives, print it to stdout */
    printf("%s : %s\n", msg->from, msg->message);
    *my_callback(msg->message, my_user_data);

}

static qeo_event_reader_listener_t _listener = { .on_data = on_chat_message };

qeo_factory_t *qeo;
qeo_event_writer_t *msg_writer;
qeo_event_reader_t *msg_reader;

void do_setup(cheesefunc user_func, void *user_data) {
    qeo = qeo_factory_create();
    msg_writer = qeo_factory_create_event_writer(qeo, org_qeo_sample_simplechat_ChatMessage_type, NULL, 0);
    msg_reader = qeo_factory_create_event_reader(qeo, org_qeo_sample_simplechat_ChatMessage_type, &_listener, 0);
   
    sleep(1);

    printf("go!\n");
    my_callback = &user_func;
    my_user_data = user_data;
    
    //while(1);I
    //if (qeo != NULL) {
    //    return 0;
    //}
}

void do_send_message(char* origin, char* message) {
    org_qeo_sample_simplechat_ChatMessage_t chat_msg = { .message = message, .from = origin };
    sleep(1);
    qeo_event_writer_write(msg_writer, &chat_msg);
    sleep(1);
}

//void do_read_message(char* message) {
    //qeo_event_writer_write(msg_writer, &chat_msg);
// }

void do_teardown() {
    qeo_event_writer_close(msg_writer);
    qeo_factory_close(qeo);
}
