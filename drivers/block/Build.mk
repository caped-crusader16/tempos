##
# Copyright (C) 2009 Renê de Souza Pinto
# TempOS - Tempos is an Educational and multi purposing Operating System
#
# Makefile
#

CDIR := drivers/block
objs := ide_generic.o

OBJFILES += $(patsubst %.o,$(CDIR)/%.o,$(objs))

