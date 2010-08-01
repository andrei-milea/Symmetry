all: test_group_el test_symmetric
CFLAGS = -std=c++0x -g -Wall -I /usr/include/boost 
GCC = /opt/usr/bin/g++

test_perm: test_permutation.cpp
	$(GCC) $(CFLAGS) test_permutation.cpp -o test_perm

test_group_el: test_group_elem.cpp
	$(GCC) $(CFLAGS) test_group_elem.cpp -o test_group_el



clean:
	rm -rf *.o $(TESTS)
TESTS = test_perm test_group_el test_symmetric
#SRCS = *.cpp *.h /usr/include/boost/numeric/ublas/matrix.hpp
#CTAGS=etags -o tags

