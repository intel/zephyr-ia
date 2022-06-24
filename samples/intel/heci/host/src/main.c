/*
 * Copyright (c) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Local Includes*/
#include "heci.h"
#include "sys/reboot.h"
/*#include "sedi.h"*/
#include "smpl_client.h"
#include <device.h>
#include <init.h>
#include <string.h>
#include <sys/sys_io.h>

/* GUID of test client */
#define HECI_CLIENT_SMPL_GUID					       \
	{							       \
		0xbb579a2e, 0xcc54, 0x4450,			       \
		{						       \
			0xb1, 0xd0, 0x5e, 0x75, 0x20, 0xdc, 0xad, 0x25 \
		}						       \
	}

#define SMPL_MAX_RX_SIZE 256
#define SMPL_STACK_SIZE 1600

/* rx msg and rx/tx buffer definitions */
static struct heci_rx_msg_t smpl_rx_msg;
static uint8_t smpl_rx_buffer[SMPL_MAX_RX_SIZE];
static uint8_t smpl_tx_buffer[SMPL_MAX_RX_SIZE];

static K_THREAD_STACK_DEFINE(smpl_stack, SMPL_STACK_SIZE);
static struct k_thread smpl_thread;
static K_SEM_DEFINE(smpl_event_sem, 0, 1);

/* event id for the heci communication */
static uint32_t smpl_event;
/* connection id for every communication */
static uint32_t smpl_conn_id;

/* function to handle the user defined heci command */
static void smpl_process_msg(uint8_t *buf)
{
	struct smpl_msg_hdr_t *rxhdr = (struct smpl_msg_hdr_t *)buf;
	struct smpl_msg_hdr_t *txhdr = (struct smpl_msg_hdr_t *)smpl_tx_buffer;

	/* fill common field in response msg header */
	txhdr->is_response = 1;
	txhdr->has_next = 0;
	txhdr->reserved = 0;
	txhdr->status = 0;

	printk("smpl cmd =  %u\n", rxhdr->command);
	switch (rxhdr->command) {
	case SMPL_GET_VERSION: {
		struct smpl_get_version_resp *resp =
			(struct smpl_get_version_resp *)(rxhdr + 1);
		printk("SMPL_GET_VERSION %d %d %d %d\n", resp->major,
		       resp->minor, resp->hotfix, resp->build);
		break;
	}
	default:
		printk("get unsupported SMPL command\n");
	}
}

/*
 * callback that will be called in heci service when any event happens for the
 * heci client
 */
static void smpl_event_callback(uint32_t event, void *arg)
{
	ARG_UNUSED(arg);
	/* record the event id to local variable */
	smpl_event = event;
	/* notify the local task to handle the event*/
	k_sem_give(&smpl_event_sem);
}

static void smpl_task(void *p1, void *p2, void *p3)
{
	ARG_UNUSED(p1);
	ARG_UNUSED(p2);
	ARG_UNUSED(p3);

	printk("enter\n");

	while (true) {
		/* wait for any heci event*/
		k_sem_take(&smpl_event_sem, K_FOREVER);

		printk("smpl new heci event %u\n", smpl_event);

		switch (smpl_event) {
		/*
		 * HECI_EVENT_NEW_MSG happens will the heci connection is setup
		 * or new message from host
		 */
		case HECI_EVENT_NEW_MSG:
			if (smpl_rx_msg.msg_lock != MSG_LOCKED) {
				printk("invalid heci message\n");
				break;
			}

			if (smpl_rx_msg.type == HECI_CONNECT) {
				smpl_conn_id = smpl_rx_msg.connection_id;
				printk("new conn: %u\n", smpl_conn_id);
			} else if (smpl_rx_msg.type == HECI_REQUEST) {
				smpl_process_msg(smpl_rx_msg.buffer);
			}

			/*
			 * send flow control after finishing one message,
			 * allow host to send new request
			 */
			heci_send_flow_control(smpl_conn_id);
			break;
		/*
		 * HECI_EVENT_DISCONN happens will the heci connection is
		 * released
		 */
		case HECI_EVENT_DISCONN:
			printk("disconnect request conn %d\n", smpl_conn_id);
			heci_complete_disconnect(smpl_conn_id);
			break;

		default:
			printk("wrong heci event %u\n", smpl_event);
			break;
		}
	}
}

void send_get_ver(void)
{
	printk("Send get SMPL_GET_VERSION command\n");
	struct mrd_t m = { 0 };
	struct smpl_msg_hdr_t txhdr;

	memset(&txhdr, 0, sizeof(txhdr));
	txhdr.command = SMPL_GET_VERSION;

	/* send response */
	m.buf = (void *)&txhdr;
	m.len = sizeof(struct smpl_msg_hdr_t);
	heci_send(smpl_conn_id, &m);
}

void send_connection_req(void)
{
	printk("Send get SMPL_GET_VERSION command\n");
	struct mrd_t m = { 0 };
	struct smpl_msg_hdr_t txhdr;

	memset(&txhdr, 0, sizeof(txhdr));
	txhdr.command = SMPL_GET_VERSION;

	/* send response */
	m.buf = (void *)&txhdr;
	m.len = sizeof(struct smpl_msg_hdr_t);
	heci_send(smpl_conn_id, &m);
}

/* the main entry of the heci demo */
void main(void)
{
	int ret;

	printk("test app ++++++++++++++++++++++++++++++\n");

	/* prepare client parametets for heci register */
	struct heci_client_t smpl_client = { .protocol_id = HECI_CLIENT_SMPL_GUID,
				      .max_msg_size = SMPL_MAX_RX_SIZE,
				      .protocol_ver = 1,
				      .max_n_of_connections = 1,
				      .dma_header_length = 0,
				      .dma_enabled = 0,
				      .rx_buffer_len = SMPL_MAX_RX_SIZE,
				      .event_cb = smpl_event_callback,
				      .param = NULL };

	smpl_client.rx_msg = &smpl_rx_msg;
	smpl_client.rx_msg->buffer = smpl_rx_buffer;

	/* register sample heci client */
	ret = heci_register(&smpl_client);

	if (ret) {
		printk("failed to register smpl client %d\n", ret);
		return;
	}

	/* create task that handles the heci message */
	k_thread_create(&smpl_thread, smpl_stack, SMPL_STACK_SIZE, smpl_task,
			NULL, NULL, NULL, K_PRIO_PREEMPT(11), 0, K_NO_WAIT);
	int cnt = 0;

	while (1) {
		k_sleep(K_MSEC(1000));

		if (cnt++ > 1) {
			send_get_ver();
			cnt = 0;
		} else {
			printk("HECI cmd will send in %d secounds\n", cnt);
		}
	}
}
