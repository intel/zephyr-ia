/**
 * @file
 *
 * @brief Public APIs for the heci.
 */

/*
 * Copyright (c) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HECI_H_
#define _HECI_H_
/**
 * @brief HECI Interface
 * @defgroup heci_interface HECI Interface
 * @{
 */
#include "kernel.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief memory resource descriptor
 *
 * This structure defines descriptor indicating the HECI client message to send.
 */
struct mrd_t {
	struct mrd_t *next;
	void const *buf;
	uint32_t len;
};

/* HECI received message types*/
typedef uint8_t heci_rx_msg_type;

enum MSG_TYPE {
	HECI_MSG_BASE,
	HECI_REQUEST = HECI_MSG_BASE,
	HECI_CONNECT,
	HECI_DISCONNECT,
	HECI_RX_DMA_MSG,
	HECI_SYNC_RESP,
	HECI_MSG_LAST,
};

#define MSG_LOCKED 1
#define MSG_UNLOCKED 0

/* HECI received message format and bit map */
struct heci_rx_msg_t {
	/* message type of this message */
	heci_rx_msg_type type;
	/* connection id bewteen HOST and PSE clients*/
	uint8_t connection_id : 7;
	/* if HOST client has enough buffer*/
	uint8_t msg_lock : 1;
	/* HECI message buffer length */
	uint16_t length;
	/* buffer pointer */
	uint8_t *buffer;
};

/* HECI GUID format, protocol id*/
struct heci_guid_t {
	uint32_t data1;
	uint16_t data2;
	uint16_t data3;
	uint8_t data4[8];
};

/* HECI event indicating there is a new message */
#define HECI_EVENT_NEW_MSG BIT(0)
/* HECI event indicating HOST wants to disonnect client */
#define HECI_EVENT_DISCONN BIT(1)

/**
 * @brief
 * callback to handle certain events
 */
typedef void (*heci_event_cb_t)(uint32_t event, void *param);

struct heci_client_t {
	/* A 16-byte identifier for the protocol supported by the client.*/
	struct heci_guid_t protocol_id;
	uint32_t max_msg_size;
	uint8_t protocol_ver;
	uint8_t max_n_of_connections; /* only support single connection */
	uint8_t dma_header_length : 7;
	uint8_t dma_enabled : 1;
	/* allocated buffer len of rx_msg->buffer */
	uint32_t rx_buffer_len;
	struct heci_rx_msg_t *rx_msg;
	heci_event_cb_t event_cb;
	void *param;
	/*
	 * the threads array, please put all threads using HECI here, it is ok
	 * not config it in kernel mode
	 */
	struct k_thread **thread_handle_list;
	uint8_t num_of_threads;
};

/**
 * @brief
 * register a new HECI client
 * @param client Pointer to the client structure for the instance.
 * @retval 0 If successful.
 */
int heci_register(struct heci_client_t *client);

/**
 * @brief
 * send HECI message to HOST client with certain connection
 * @param conn_id connection id for sending.
 * @param msg message content pointer to send.
 * @retval true If successful.
 */
bool heci_send(uint32_t conn_id, struct mrd_t *msg);

/**
 * @brief
 * send HECI flow control message to HOST client, indicating that PSE client is
 * ready for receiving a new HECI message
 * @param conn_id connection id for sending.
 * @retval true If successful.
 */
bool heci_send_flow_control(uint32_t conn_id);

/**
 * @brief
 * complete disconnection between PSE client and HOST client, run after
 * receiving a disconnection request from HOST client
 * @param conn_id connection id to disconnect.
 * @retval 0 If successful.
 */
int heci_complete_disconnect(uint32_t conn_id);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* _HECI_H_ */
