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
static void publish_netstat_messages(const qeo_state_writer_t *writer)
{
    org_qeo_sample_gauge_NetStatMessage_t msg = {};
    FILE *fp = NULL;
    char buf[256], *saveptr, *token;
    int cnt = 0;
    struct timespec time = {};
    int i = 0;

    msg.deviceId.lower = _id.lowerId;
    msg.deviceId.upper = _id.upperId;
    /* now parse /proc/net/dev and publish a message for each interface. */
    fp = fopen("/proc/net/dev", "r");
    assert(NULL != fp);
    while (NULL != fgets(buf, sizeof(buf), fp)) {
        cnt++;
        if (cnt <= 2) {
            continue; /* skip first two header lines */
        }
        /* parse and fill interface name */
        token = strtok_r(buf, ":", &saveptr);
        msg.ifName = strdup(token);
        /* parse and fill received byte count */
        token = strtok_r(NULL, " ", &saveptr);
        msg.bytesIn = atoi(token);
        /* parse and fill received packet count */
        token = strtok_r(NULL, " ", &saveptr);
        msg.packetsIn = atoi(token);
        /* skip some unused fields */
        for (i = 0; i < 6; i++) {
            token = strtok_r(NULL, " ", &saveptr); /* skip */
        }
        /* parse and fill sent byte count */
        token = strtok_r(NULL, " ", &saveptr);
        msg.bytesOut = atoi(token);
        /* parse and fill sent packet count */
        token = strtok_r(NULL, " ", &saveptr);
        msg.packetsOut = atoi(token);
        /* calculate and fill timestamp */
        clock_gettime(CLOCK_MONOTONIC, &time);
        msg.timestamp = ((int64_t) time.tv_nsec) + (((int64_t) time.tv_sec) * 1000000000);
        /* publish sample */
        qeo_state_writer_write(writer, &msg);
        /* clear sample */
        free(msg.ifName);
    }
    fclose(fp);
}

int dosomething(char *buf, char *from)
{
    qeo_factory_t *qeo;
    qeo_event_writer_t *msg_writer;
    // qeo_event_reader_t *msg_reader;

    /* local variables for storing the message before sending */
    org_qeo_sample_simplechat_ChatMessage_t chat_msg = { .message = buf, .from = from };

    /* initialize */
    qeo = qeo_factory_create();
    if (qeo != NULL) {
        msg_writer = qeo_factory_create_event_writer(qeo, org_qeo_sample_simplechat_ChatMessage_type, NULL, 0);
        // msg_reader = qeo_factory_create_event_reader(qeo, org_qeo_sample_simplechat_ChatMessage_type, &_listener, 0);

        /* send message out */
        qeo_event_writer_write(msg_writer, &chat_msg);

        /* clean up */
        qeo_event_reader_close(msg_reader);
        qeo_event_writer_close(msg_writer);
        qeo_factory_close(qeo);
    }
    return 0;
}

