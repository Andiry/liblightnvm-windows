/*
 * Definitions for the NVM Express ioctl interface
 * Copyright (c) 2011-2014, Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */

#ifndef _UAPI_LINUX_NVME_IOCTL_H
#define _UAPI_LINUX_NVME_IOCTL_H

struct nvme_user_io {
	uint8_t	opcode;
	uint8_t	flags;
	uint16_t	control;
	uint16_t	nblocks;
	uint16_t	rsvd;
	uint64_t	metadata;
	uint64_t	addr;
	uint64_t	slba;
	uint32_t	dsmgmt;
	uint32_t	reftag;
	uint16_t	apptag;
	uint16_t	appmask;
};

struct nvme_passthru_cmd {
	uint8_t	opcode;
	uint8_t	flags;
	uint16_t	rsvd1;
	uint32_t	nsid;
	uint32_t	cdw2;
	uint32_t	cdw3;
	uint64_t	metadata;
	uint64_t	addr;
	uint32_t	metadata_len;
	uint32_t	data_len;
	uint32_t	cdw10;
	uint32_t	cdw11;
	uint32_t	cdw12;
	uint32_t	cdw13;
	uint32_t	cdw14;
	uint32_t	cdw15;
	uint32_t	timeout_ms;
	uint32_t	result;
};

#define nvme_admin_cmd nvme_passthru_cmd

#define NVME_IOCTL_ID		__IO('N', 0x40)
#define NVME_IOCTL_ADMIN_CMD	__IOWR('N', 0x41, struct nvme_admin_cmd)
#define NVME_IOCTL_SUBMIT_IO	__IOW('N', 0x42, struct nvme_user_io)
#define NVME_IOCTL_IO_CMD	__IOWR('N', 0x43, struct nvme_passthru_cmd)
#define NVME_IOCTL_RESET	__IO('N', 0x44)
#define NVME_IOCTL_SUBSYS_RESET	__IO('N', 0x45)
#define NVME_IOCTL_RESCAN	__IO('N', 0x46)

#endif /* _UAPI_LINUX_NVME_IOCTL_H */
