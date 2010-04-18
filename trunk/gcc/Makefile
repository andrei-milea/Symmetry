all:	tst_sqmatrix tst_group
CFLAGS =-c -Wall -I /usr/include/boost 

#test configuration for squared matrix class
tst_sqmatrix: tst_sqmatrix.cpp
	g++ $(CFLAGS) tst_sqmatrix.cpp -o tst_sqmatrix

#test configuration for group class
tst_group: tst_group.cpp
	g++ $(CFLAGS) tst_group.cpp -o tst_group


clean:
	rm -rf *o tst_sqmatrix tst_group

SRCS = *.cpp *.h
CTAGS=ctags -x >tags

tags:
		${CTAGS} $(SRCS)
lint:
		lint $(CFLAGS) $(SRCS)
