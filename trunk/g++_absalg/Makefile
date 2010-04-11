all:	test 
CFLAGS =-c -Wall -I /usr/include/boost 

test: absalg.o 
	g++  absalg.o -o absalg 

absalg.o: absalg.cpp
	g++ $(CFLAGS) absalg.cpp

clean:
	rm -rf *o absalg 

SRCS = *.cpp *.h
CTAGS=ctags -x >tags

tags:
		${CTAGS} $(SRCS)
lint:
		lint $(CFLAGS) $(SRCS)
