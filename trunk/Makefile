# $Id: Makefile,v 1.2 2001-09-25 15:55:43 poonlap Exp $
# Should use autoconf and automake in the future
OBJS = tcl_thwords.o tcl_thmod.o tcl_thchar.o
CC = gcc

all:	${OBJS} thmod.h
	${CC} -o tcl_thmod.so -shared ${OBJS} -ltcl -lthai
clean:	
	rm *.o *.so 
