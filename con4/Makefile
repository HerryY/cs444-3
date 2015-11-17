CC = gcc
CFLAGS = -Wall -lpthread -lrt -lm -g

TARGET = con3

INCLUDES =

SOURCE = con3.c

default: compile

compile: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} ${SOURCE} -o ${TARGET}

clean-c:
	rm -f *.o
	rm -f *.out
	rm con3

clean: clean-c
