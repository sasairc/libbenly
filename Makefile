#
#    Makefile for libbenly
#

PREFIX	   := /usr/local
LIBDIR	   := $(PREFIX)/lib
INCLUDEDIR := $(PREFIX)/include
MAKE	   := make
CC	   := cc
RM	   := rm
CFLAGS	   := -O2 -g -Wall -Wextra
LDFLAGS    :=
CMDLINE    := 0
export

all install-lib install-header clean:
	@$(MAKE) -C ./src	$@

install: install-lib	\
	 install-header

.PHONY:	all		\
	install		\
	install-libs	\
	install-header	\
	clean
