CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lm

ga : ga_classic.o ga_test.o
	${CC} ${CFLAGS} ga_classic.o ga_test.o -o ga

ga_classic.o : ga_classic.cpp ga_classic.h
	${CC} ${CFLAGS} -c ga_classic.cpp

ga_test.o : ga_test.cpp ga_classic.h
	${CC} ${CFLAGS} -c ga_test.cpp

clean:
	rm -rf *o ga
