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

#include "QSimpleChat_ChatMessage.h"

static volatile bool _quit = false;
static qeo_platform_device_id _id;

/* ===[ NetStatMessage publication ]========================================= */

/**
 * Publish messages based on the interface statistics from /proc/net/dev.
 *
 * Syntax of /prov/net/dev:
 *
 * Inter-|   Receive                                                |  Transmit
 *  face |bytes    packets errs drop fifo frame compressed multicast|bytes    packets errs drop fifo colls carrier compressed
 *   eth0:  412867    3706    0    0    0     0          0         0     2218      11    0    0    0     0       0          0
 */

int dosomething(void)
{
    qeo_factory_t *qeo;
    qeo_event_writer_t *msg_writer;
    // qeo_event_reader_t *msg_reader;

    /* local variables for storing the message before sending */
    char buf[] = "up";
    char from[] = "phone";
    org_qeo_sample_simplechat_ChatMessage_t chat_msg = { .message = buf, .from = from };

    /* initialize */
    qeo = qeo_factory_create();
    if (qeo != NULL) {
        msg_writer = qeo_factory_create_event_writer(qeo, org_qeo_sample_simplechat_ChatMessage_type, NULL, 0);
        // msg_reader = qeo_factory_create_event_reader(qeo, org_qeo_sample_simplechat_ChatMessage_type, &_listener, 0);

        sleep(2);
        /* send message out */
        qeo_event_writer_write(msg_writer, &chat_msg);
        sleep(2);
        /* clean up */
        qeo_event_writer_close(msg_writer);
        qeo_factory_close(qeo);
    }
    else {
        return 1;
    }
    return 0;
}

