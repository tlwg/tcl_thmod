# $Id: Makefile,v 1.3 2001-09-26 03:00:30 poonlap Exp $
# Should use autoconf and automake in the future
OBJS = tcl_thwords.o tcl_thmod.o tcl_thchar.o
CC = gcc
CFLAGS = -fPIC

all:	${OBJS} thmod.h
	${CC} ${CFLAGS} -o tcl_thmod.so -shared ${OBJS} -ltcl8.3 -lthai
clean:	
	rm *.o *.so 
