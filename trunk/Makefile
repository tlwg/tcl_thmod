# $Id: Makefile,v 1.5 2001-10-02 13:32:03 poonlap Exp $
# Should use autoconf and automake in the future
OBJS = tcl_thwords.o tcl_thmod.o tcl_thchar.o tcl_thstr.o
CC = gcc
CFLAGS = -fPIC

all:	${OBJS} thmod.h
	${CC} ${CFLAGS} -o tcl_thmod.so -shared ${OBJS} -ltcl -lthai
clean:	
	rm *.o *.so 
