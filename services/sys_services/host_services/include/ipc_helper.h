/*
 * Copyright (c) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/****** IPC helper definitions *****/

#ifndef __IPC_HELPER_H
#define __IPC_HELPER_H

#include "intel/hal_ipc.h"
#include "device.h"

#define MNG_CAP_SUPPORTED 1

#define IPC_PROTOCOL_BOOT 0
#define IPC_PROTOCOL_HECI 1
#define IPC_PROTOCOL_MCTP 2
#define IPC_PROTOCOL_MNG 3
#define IPC_PROTOCOL_INVAILD 0xF

#define IPC_DATA_LEN_MAX (128)

#define IPC_HEADER_LENGTH_MASK (0x03FF)
#define IPC_HEADER_PROTOCOL_MASK (0x0F)
#define IPC_HEADER_MNG_CMD_MASK (0x0F)

#define IPC_HEADER_LENGTH_OFFSET 0
#define IPC_HEADER_PROTOCOL_OFFSET 10
#define IPC_HEADER_MNG_CMD_OFFSET 16
#define IPC_DRBL_BUSY_OFFS 31

#define IPC_HEADER_GET_LENGTH(drbl_reg)	\
	(((drbl_reg) >> IPC_HEADER_LENGTH_OFFSET) & IPC_HEADER_LENGTH_MASK)
#define IPC_HEADER_GET_PROTOCOL(drbl_reg) \
	(((drbl_reg) >> IPC_HEADER_PROTOCOL_OFFSET) & IPC_HEADER_PROTOCOL_MASK)
#define IPC_HEADER_GET_MNG_CMD(drbl_reg) \
	(((drbl_reg) >> IPC_HEADER_MNG_CMD_OFFSET) & IPC_HEADER_MNG_CMD_MASK)

#define IPC_BUILD_DRBL(length, protocol)	      \
	((1 << IPC_DRBL_BUSY_OFFS) |		      \
	 ((protocol) << IPC_HEADER_PROTOCOL_OFFSET) | \
	 ((length) << IPC_HEADER_LENGTH_OFFSET))

#define IPC_BUILD_MNG_DRBL(cmd, length)			      \
	(((1) << IPC_DRBL_BUSY_OFFS) |			      \
	 ((IPC_PROTOCOL_MNG) << IPC_HEADER_PROTOCOL_OFFSET) | \
	 ((cmd) << IPC_HEADER_MNG_CMD_OFFSET) |		      \
	 ((length) << IPC_HEADER_LENGTH_OFFSET))

int send_rx_complete(const struct device *dev);

void heci_reset(void);

#endif /* __IPC_HELPER_H */
