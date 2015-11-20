CC = gcc
CFLAGS = -Wall -lpthread -lrt -lm -g

TARGET = problem1
TARGET1 = problem2



INCLUDES =

p1 = problem1.c
p2 = problem2.c

default: problem1 problem2

problem1: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} ${p1} -o ${TARGET}
	
problem2: ${SOURCE2} ${INCLUDES}
	${CC} ${CFLAGS} ${p2} -o ${TARGET1}

clean-c:
	rm -f *.o
	rm -f *.out
	rm problem1
	rm problem2

clean: clean-c
