/**
 * Copyright (C) 2009 Renê de Souza Pinto
 * Tempos - Tempos is an Educational and multi purposing Operating System
 *
 * File: gdt.h
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

#ifndef ARCH_X86_GDT_H

	#define ARCH_X86_GDT_H

	#include <x86/x86.h>

	#define GDT_TABLE_SIZE	0x05

	#define GDT_SET_BASE(a, base)      a->base_low         = (base & 0xFFFF);        \
									   a->high.base_middle = ((base >> 16) & 0xFF);  \
									   a->high.base_high   = ((base >> 24) & 0xFF);

	#define GDT_SET_LIMIT(b, limit)    b->limit_low        = (limit & 0xFFFF);       \
									   b->high.limit_high  = ((limit >> 16) & 0xF);

	#define CODE_SEG	0x0A	/* Execute / Read 					 */
	#define DATA_SEG	0x02	/* Read / Write						 */

	#define STYPE_SYS	0  		/* System segment descriptor type    */
	#define STYPE_DC	1  		/* Data/Code segment descriptor type */

	#define GDT_GR_BYTE 0
	#define GDT_GR_4KB  1


	/**
	 * gdt_entry
	 *
	 * Each entry of GDT stores a Segment Descriptor. A segment descriptor in GDT
	 * should describe any of follow segments below:
	 *
	 * 		CD_SEG    - Code/Data segment
	 * 		TSS_SEG   - Task-state segment
	 * 		CGATE_SEG - Call gate segment
	 * 		LDT_SEG   - Local decriptor-table (LDT) segment
	 * 		  ^              ^
	 *        |              |
	 * 		  |              |
	 * 		  |              [---- Intel terminology
	 * 		  |
	 * 		  [---- TempOS terminology
	 *
	 */
	struct _gdt_entry {
		uint32_t lower;
		uint32_t high;
	} __attribute__ ((packed));


	/**
	 * gdt_cd_seg
	 *
	 * The GDT table entry format for Code/Data segments. This is not the better way
	 * to express a GDT entry, but it's clear and more easy to understand.
	 *
	 * For more information, see Intel Manual vol.3, chapter 3, page 3-11.
	 */
	struct _gdt_cd_seg {
		uint16_t  limit_low;
		uint16_t  base_low;
		struct _gdt_high {
			uint32_t base_middle : 8;
			uint32_t type        : 4;
			uint32_t desc_type   : 1;
			uint32_t DPL         : 2;
			uint32_t present     : 1;
			uint32_t limit_high  : 4;
			uint32_t avaliable   : 1;
			uint32_t reserved    : 1;
			uint32_t DB          : 1;
			uint32_t granularity : 1;
			uint32_t base_high   : 8;
		} __attribute__ ((packed)) high;
	} __attribute__ ((packed));

	/**
	 * gdtr_t
	 *
	 * GDTR store GDT table size (limit) and the pointer to the table
	 */
	struct _gdt_gdtr {
		uint16_t table_limit;
		uint32_t gdt_ptr;
	} __attribute__ ((packed)) GDTR;

	typedef struct _gdt_entry  gdt_t;
	typedef struct _gdt_cd_seg gdt_cdseg_t;

	/* GDT table */
	gdt_t gdt_table[GDT_TABLE_SIZE];

	void setup_GDT(void);
	inline void load_gdt(void);

#endif /* ARCH_X86_GDT_H */

