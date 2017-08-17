#
#    Makefile for libbenly
#

PREFIX	   := /usr/local
LIBDIR	   := $(PREFIX)/lib
INCLUDEDIR := $(PREFIX)/include
MAKE	   := make
CC	   := cc
RM	   := rm
CFLAGS	   := -O2 -g
LDFLAGS    :=
CMDLINE    := 0

all install-lib install-header clean:
	@$(MAKE) -C ./src	$@

install: install-lib	\
	 install-header

.PHONY:	all		\
	install		\
	install-libs	\
	install-header	\
	clean
