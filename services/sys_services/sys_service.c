/*
 * Copyright (c) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <kernel_structs.h>
#include <string.h>
#include <user_app_framework/uapp_framework.h>
#include <user_app_framework/uapp_config.h>

#include "sys_service.h"
#include "host_services/host_service_common.h"

static void sys_config(void)
{
#if defined(CONFIG_HOST_IA_SERVICE)
	host_config();
#endif
}

static void sys_service_main(void *p1, void *p2, void *p3)
{
#if defined(CONFIG_HOST_IA_SERVICE)
	host_service_init();
#endif
}

/* Add the required sys service local kernel object pointer into list. */
static const void *obj_list[] = {
#if defined(CONFIG_HOST_IA_SERVICE)
	HOST_K_OBJ_LIST
#endif
};
/* Define system service. */
DEFINE_USER_MODE_APP(0, USER_MODE_SERVICE | K_PART_GLOBAL, sys_service_main,
		     1024, (void **)obj_list, SYS_K_OBJ_LIST_SIZE, sys_config);
