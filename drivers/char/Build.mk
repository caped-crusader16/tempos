##
# Copyright (C) 2009 Renê de Souza Pinto
# TempOS - Tempos is an Educational and multi purposing Operating System
#
# Makefile
#

CDIR := drivers/char
OBJS := i8042.o


#--- DO NOT CHANGE HERE ---#

OBJDIRS += $(CDIR)

OBJS := $(patsubst %.o,$(CDIR)/%.o,$(OBJS))
SRC  := $(OBJS:.o=.c)
DEPS := $(OBJS:.o=.d)

OBJFILES += $(OBJS)

all: $(OBJS)

$(CDIR)/%.o: $(CDIR)/%.c
	@echo + CC $<
	@$(CC) $(CFLAGS) -c $< -o $@

%.d: %.c 
	@$(CC) -MM $(CFLAGS) $< \
		| sed 's#\(.*\)\.o[ :]*#\1.o $@ : #g' > $@; \
		[ -s $@ ] || rm -f $@

include $(DEPS)

#--------------------------#


