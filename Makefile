CC = gcc
CFLAGS = -Wall -pthread -lrt -lm -g


TARGET = con1
tex = proj1

INCLUDES =

SOURCE = con1.c

default: compile

compile: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} ${SOURCE} -o ${TARGET}

debug: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} ${SOURCE} -o ${TARGET} ${LDFLAGS} -DDEBUG

clean-c:
	
	rm -f *.o
	rm -f *.out
	


dvi: ${tex}.tex
	latex ${tex}.tex


ps: dvi
	dvips -R -Poutline -t letter ${tex}.dvi -o ${tex}.ps

pdf: ps
	ps2pdf ${tex}.ps

clean-dvi:
	rm -f ${tex}.aux
	rm -f ${tex}.log
	rm -f ${tex}.dvi
	rm -f ${tex}.out
	rm -f ${tex}.ps

clean-ps: clean-dvi
	rm -f ${TARGET}.ps

clean-pdf: clean-ps
	rm -f ${tex}.pdf

clean: clean-pdf clean-c