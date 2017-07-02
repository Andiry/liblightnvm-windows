/*
 * Copyright (C) 2015 CNEX Labs.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139,
 * USA.
 */

#ifndef _UAPI_LINUX_LIGHTNVM_H
#define _UAPI_LINUX_LIGHTNVM_H

#include <stdio.h>
#include <stdint.h>
#define DISK_NAME_LEN 32


#define NVM_TTYPE_NAME_MAX 48
#define NVM_TTYPE_MAX 63
#define NVM_MMTYPE_LEN 8

#define NVM_CTRL_FILE "/dev/lightnvm/control"

struct nvm_ioctl_info_tgt {
	uint32_t version[3];
	uint32_t reserved;
	char tgtname[NVM_TTYPE_NAME_MAX];
};

struct nvm_ioctl_info {
	uint32_t version[3];	/* in/out - major, minor, patch */
	uint16_t tgtsize;		/* number of targets */
	uint16_t reserved16;	/* pad to 4K page */
	uint32_t reserved[12];
	struct nvm_ioctl_info_tgt tgts[NVM_TTYPE_MAX];
};

enum {
	NVM_DEVICE_ACTIVE = 1 << 0,
};

struct nvm_ioctl_device_info {
	char devname[DISK_NAME_LEN];
	char bmname[NVM_TTYPE_NAME_MAX];
	uint32_t bmversion[3];
	uint32_t flags;
	uint32_t reserved[8];
};

struct nvm_ioctl_get_devices {
	uint32_t nr_devices;
	uint32_t reserved[31];
	struct nvm_ioctl_device_info info[31];
};

struct nvm_ioctl_create_simple {
	uint32_t lun_begin;
	uint32_t lun_end;
};

enum {
	NVM_CONFIG_TYPE_SIMPLE = 0,
};

struct nvm_ioctl_create_conf {
	uint32_t type;
	union {
		struct nvm_ioctl_create_simple s;
	};
};

struct nvm_ioctl_create {
	char dev[DISK_NAME_LEN];		/* open-channel SSD device */
	char tgttype[NVM_TTYPE_NAME_MAX];	/* target type name */
	char tgtname[DISK_NAME_LEN];		/* dev to expose target as */

	uint32_t flags;

	struct nvm_ioctl_create_conf conf;
};

struct nvm_ioctl_remove {
	char tgtname[DISK_NAME_LEN];

	uint32_t flags;
};

struct nvm_ioctl_dev_init {
	char dev[DISK_NAME_LEN];		/* open-channel SSD device */
	char mmtype[NVM_MMTYPE_LEN];		/* register to media manager */

	uint32_t flags;
};

enum {
	NVM_FACTORY_ERASE_ONLY_USER	= 1 << 0, /* erase only blocks used as
						   * host blks or grown blks */
	NVM_FACTORY_RESET_HOST_BLKS	= 1 << 1, /* remove host blk marks */
	NVM_FACTORY_RESET_GRWN_BBLKS	= 1 << 2, /* remove grown blk marks */
	NVM_FACTORY_NR_BITS		= 1 << 3, /* stops here */
};

struct nvm_ioctl_dev_factory {
	char dev[DISK_NAME_LEN];

	uint32_t flags;
};

struct nvm_user_vio {
	uint8_t opcode;
	uint8_t flags;
	uint16_t control;
	uint16_t nppas;
	uint16_t rsvd;
	uint64_t metadata;
	uint64_t addr;
	uint64_t ppa_list;
	uint32_t metadata_len;
	uint32_t data_len;
	uint64_t status;
	uint32_t result;
	uint32_t rsvd3[3];
};

struct nvm_passthru_vio {
	uint8_t opcode;
	uint8_t flags;
	uint8_t rsvd[2];
	uint32_t nsid;
	uint32_t cdw2;
	uint32_t cdw3;
	uint64_t metadata;
	uint64_t addr;
	uint32_t metadata_len;
	uint32_t data_len;
	uint64_t ppa_list;
	uint16_t nppas;
	uint16_t control;
	uint32_t cdw13;
	uint32_t cdw14;
	uint32_t cdw15;
	uint64_t status;
	uint32_t result;
	uint32_t timeout_ms;
};

/* The ioctl type, 'L', 0x20 - 0x2F documented in ioctl-number.txt */
enum {
	/* top level cmds */
	NVM_INFO_CMD = 0x20,
	NVM_GET_DEVICES_CMD,

	/* device level cmds */
	NVM_DEV_CREATE_CMD,
	NVM_DEV_REMOVE_CMD,

	/* Init a device to support LightNVM media managers */
	NVM_DEV_INIT_CMD,

	/* Factory reset device */
	NVM_DEV_FACTORY_CMD,

	/* Vector user I/O */
	NVM_DEV_VIO_ADMIN_CMD = 0x41,
	NVM_DEV_VIO_CMD = 0x42,
	NVM_DEV_VIO_USER_CMD = 0x43,
};

#define NVM_IOCTL 'L' /* 0x4c */

#define NVM_INFO		__IOWR(NVM_IOCTL, NVM_INFO_CMD, \
						struct nvm_ioctl_info)
#define NVM_GET_DEVICES		__IOR(NVM_IOCTL, NVM_GET_DEVICES_CMD, \
						struct nvm_ioctl_get_devices)
#define NVM_DEV_CREATE		__IOW(NVM_IOCTL, NVM_DEV_CREATE_CMD, \
						struct nvm_ioctl_create)
#define NVM_DEV_REMOVE		__IOW(NVM_IOCTL, NVM_DEV_REMOVE_CMD, \
						struct nvm_ioctl_remove)
#define NVM_DEV_INIT		__IOW(NVM_IOCTL, NVM_DEV_INIT_CMD, \
						struct nvm_ioctl_dev_init)
#define NVM_DEV_FACTORY		__IOW(NVM_IOCTL, NVM_DEV_FACTORY_CMD, \
						struct nvm_ioctl_dev_factory)

#define NVME_NVM_IOCTL_IO_VIO		__IOWR(NVM_IOCTL, NVM_DEV_VIO_USER_CMD, \
						struct nvm_passthru_vio)
#define NVME_NVM_IOCTL_ADMIN_VIO	__IOWR(NVM_IOCTL, NVM_DEV_VIO_ADMIN_CMD,\
						struct nvm_passthru_vio)
#define NVME_NVM_IOCTL_SUBMIT_VIO	__IOWR(NVM_IOCTL, NVM_DEV_VIO_CMD,\
						struct nvm_user_vio)

#define NVM_VERSION_MAJOR	1
#define NVM_VERSION_MINOR	0
#define NVM_VERSION_PATCHLEVEL	0

#endif
