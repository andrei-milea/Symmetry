all:	tst_group
CFLAGS =-c  -std=c++0x -g -Wall -I /usr/include/boost 
GCC = /opt/usr/bin/g++

tst_group: tst_group.o
	$(GCC) tst_group.o -o tst_group

#test configuration for group class
tst_group.o: tst_group.cpp
	$(GCC) $(CFLAGS) tst_group.cpp -o tst_group.o


clean:
	rm -rf *o tst_group

SRCS = *.cpp *.h
CTAGS=ctags -x >tags

tags:
		${CTAGS} $(SRCS)
lint:
		lint $(CFLAGS) $(SRCS)
