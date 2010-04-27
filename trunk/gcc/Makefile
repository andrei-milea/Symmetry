all:	tst_group
CFLAGS =-c  -g -Wall -I /usr/include/boost 

tst_group: tst_group.o
	g++ tst_group.o -o tst_group

#test configuration for group class
tst_group.o: tst_group.cpp
	g++ $(CFLAGS) tst_group.cpp -o tst_group.o


clean:
	rm -rf *o tst_group

SRCS = *.cpp *.h
CTAGS=ctags -x >tags

tags:
		${CTAGS} $(SRCS)
lint:
		lint $(CFLAGS) $(SRCS)
