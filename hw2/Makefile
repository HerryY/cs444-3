CC = gcc
CFLAGS = -Wall -lpthread -lrt -lm -g

TARGET = con2

INCLUDES =

SOURCE = con2.c

default: compile

compile: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} ${SOURCE} -o ${TARGET}

clean-c:
	rm -f *.o
	rm -f *.out
	rm con2

clean: clean-c
