##
# Copyright (C) 2009 Renê de Souza Pinto
# TempOS - Tempos is an Educational and multi purpose Operating System
#
# Makefile
#

CDIR := kernel/mm
objs := init_mm.o kmalloc.o

OBJFILES += $(patsubst %.o,$(CDIR)/%.o,$(objs))

