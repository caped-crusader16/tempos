/**
 * Copyright (C) 2009 Rene de Souza Pinto
 * Tempos - Tempos is an Educational and multi purposing Operating System
 *
 * File: kernel.h
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef KERNEL_H

	#define KERNEL_H

	#include <stdarg.h>
	#include <stdlib.h>
	#include <ctype.h>

	#include "../arch/x86/boot/video.h" /* temporary */

	#define CHECK_BIT(a, b)		((a >> b) & 0x01)
	#define SET_BIT(a, b)		a |= (0x01 << b)

	int vsprintf(char *str, const char *format, va_list ap);
	int sprintf(char *str, const char *format, ...);
	int kprintf(const char *format, ...);

	void tempos_main(void);

#endif /* KERNEL_H */

