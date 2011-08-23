/*
 * Copyright (C) 2011 Renê de Souza Pinto
 * Tempos - Tempos is an Educational and multi purpose Operating System
 *
 * File: partition.h
 *
 * This file is part of TempOS.
 *
 * TempOS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * TempOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef VFS_PARTITION_H

	#define VFS_PARTITION_H

	#include <unistd.h>

	/**
	 * Partition MBR entry structure
	 */
	struct _partition_st {
		uchar8_t  bootable;
		uchar8_t  starting_head;
		uint16_t  starting_sector:6;
		uint16_t  starting_cylinder:10;
		uchar8_t  sysid;
		uchar8_t  ending_head;
		uint16_t  ending_sector:6;
		uint16_t  ending_cylinder:10;
		uint32_t  LBA_first_sector;
		uint32_t  total_sectors;
	} __attribute__((packed));

	/**
	 * MBR (Master Boot Record) structure
	 */
	struct _mbr_st {
		uchar8_t bootcode[440];
		uint32_t diskid_low;
		uint16_t diskid_high;
		struct _partition_st partition[4];
		uchar8_t boot_signature[2];
	} __attribute__((packed));

	/**
	 * EBR (Extended Boot Record) structure
	 */
	struct _ebr_st {
		uchar8_t bootcode[446];
		struct _partition_st partition;
		struct _partition_st next_ebr;
		uchar8_t reserved[32];
		uchar8_t boot_signature[2];
	} __attribute__((packed));


	typedef struct _mbr_st       mbr_st;
	typedef struct _partition_st partition_st;
	typedef struct _ebr_st		 ebr_st;

#endif /* VFS_PARTITION_H */

