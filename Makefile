# $Id: Makefile,v 1.1 2001-09-24 15:19:42 poonlap Exp $
# Should use autoconf and automake in the future
OBJS = tcl_thbrk.o tcl_thmod.o tcl_thctype.o
CC = gcc

all:	${OBJS} thmod.h
	${CC} -o tcl_thmod.so -shared ${OBJS} -ltcl -lthai
clean:	
	rm *.o *.so 
