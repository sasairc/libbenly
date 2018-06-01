MAKE	:= make
CC	:= cc
RM	:= rm

INCLUDE	= -I../../src
SRCS	= $(wildcard *.c)
PROGS	= $(SRCS:.c=.out)

all: $(PROGS)

.c.out:
	$(CC) $(INCLUDE) ../../src/typestring.o $< -o $@

clean:
	-$(RM) -f $(PROGS)

.PHONY: all clean
