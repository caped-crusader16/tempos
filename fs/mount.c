/*
 * Copyright (C) 2009-2011 Renê de Souza Pinto
 * Tempos - Tempos is an Educational and multi purpose Operating System
 *
 * File: mount.c
 * Desc: Implements mount related functions.
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

#include <tempos/kernel.h>
#include <tempos/wait.h>
#include <fs/vfs.h>
#include <fs/device.h>

/**
 * Mount root file system
 *
 * \param device Root device.
 * \return 0 on success, -1 otherwise.
 */
int vfs_mount_root(dev_t device)
{
	int i;
	char found;
	vfs_fs_type *fs;

	/* Try to find which file system device is formated */
	found = 0;
	for (i = 0; i < VFS_SUPPORTED_FS; i++) {
		fs = vfs_filesystems[i];
		if (fs != NULL) {
			if ( fs->check_fs_type(device) ) {
				kprintf("VFS: Found %s file system.", fs->name);
				found = 1;
				break;
			}
		}
	}
	if (!found) {
		panic("VFS: Cannot mount root. Unknown file system type.");
	}

	return -1;
}

