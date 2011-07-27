/*
 * Copyright (C) 2009 Renê de Souza Pinto
 * Tempos - Tempos is an Educational and multi purpose Operating System
 *
 * File: timer.c
 * Desc: Time system of TempOS
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

#include <tempos/timer.h>
#include <tempos/jiffies.h>
#include <linkedl.h>
#include <unistd.h>
#include <arch/irq.h>


/** Queue of alarms */
llist *alarm_queue;


static void timer_handler(void);
static void update_alarms(void);


/**
 * Contains the number of system clock ticks
 *
 * \note System frequency is expressed in hertz by HZ defined at compilation.
 * \see tempos/timer.h
 */
volatile uint32_t jiffies;


/**
 * Initialize time system
 */
void init_timer(void)
{
	jiffies = 0;

	kprintf(KERN_INFO "Initializing timer...\n");

	if( request_irq(TIMER_IRQ, (void(*)(int, pt_regs *))timer_handler, 0, "PIT") < 0 ) {
		kprintf(KERN_ERROR "Error on initialize PIT\n");
	} else {
		llist_create(&alarm_queue);
	}
}


/**
 * Interrupt handler
 */
static void timer_handler(void)
{
	jiffies++;
	update_alarms();
}


/**
 * Check and execute handlers of expired alarms
 */
static void update_alarms(void)
{
	llist *tmp;
	alarm_t *alarm;
	uint32_t pos;

	tmp = alarm_queue;
	pos = 0;
	foreach(alarm_queue, tmp) {
		alarm = (alarm_t*)tmp->element;

		if( time_after(jiffies, alarm->expires) ) {
			/* Execute handler and remove from list */
			alarm->handler(alarm->arg);
			llist_remove_nth(&alarm_queue, pos);
		}

		pos++;
	}
}


/**
 * Create a new alarm
 *
 * \param expires When alarm will expire (expressed in jiffies)
 * \param handler The function to be executed when alarm expires.
 * \param arg Argument to be passed to handler function.
 */
int new_alarm(uint32_t expires, void (*handler)(int), uint32_t arg)
{
	alarm_t *nalarm;

	if(expires < jiffies) {
		return(0);
	} else {
		nalarm = (alarm_t*)kmalloc(sizeof(alarm_t), GFP_NORMAL_Z);
		if(nalarm == NULL) {
			return(0);
		} else {
			nalarm->expires = expires;
			nalarm->handler = handler;
			nalarm->arg     = arg;
			llist_add(&alarm_queue, nalarm);
		}
	}

	return(1);
}


