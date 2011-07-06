all: test_perm test_group_el test_symmetric test_std_ex test_group test_engine_main
CFLAGS = -c -std=c++0x -g -Wall -I /usr/include/boost 
LFLAGS = -lboost_thread
GCC = /opt/usr/bin/g++

test_perm: test_permutation.cpp
	$(GCC) $(CFLAGS) test_permutation.cpp -o test_perm

test_group_el: test_group_elem.cpp
	$(GCC) $(CFLAGS) test_group_elem.cpp -o test_group_el

test_symmetric: test_symmetric_rep.cpp
	$(GCC) $(CFLAGS) test_symmetric_rep.cpp -o test_symmetric

test_std_ex: test_std_ex.cpp
	$(GCC) $(CFLAGS) test_std_ex.cpp -o test_std_ex

test_group: test_group.cpp
	$(GCC) $(CFLAGS) test_group.cpp -o test_group

test_lattice: test_lattice.cpp
	$(GCC) $(CFLAGS) test_lattice.cpp -o test_lattice

########################
#test_engine compilation
########################

test_engine_main: test_engine.o estimate.o getelem_command.o getsubgrp_command.o session.o 
	$(GCC) $(LFLAGS) test_engine.o getsubgrp_command.o getelem_command.o estimate.o session.o -o test_engine_main 


test_engine.o: test_engine.cpp
	$(GCC) $(CFLAGS) test_engine.cpp -o test_engine.o

estimate.o: ../engine/estimate.cpp
	$(GCC) $(CFLAGS) ../engine/estimate.cpp -o estimate.o 

getsubgrp_command.o: ../engine/getsubgrp_command.cpp
	$(GCC) $(CFLAGS) ../engine/getsubgrp_command.cpp -o getsubgrp_command.o

getelem_command.o: ../engine/getelem_command.cpp
	$(GCC) $(CFLAGS) ../engine/getelem_command.cpp -o getelem_command.o

session.o: ../engine/session.cpp
	$(GCC) $(CFLAGS) ../engine/session.cpp -o session.o


########################
########################


clean:
	rm -rf *.o $(TESTS)
TESTS = test_perm test_group_el test_symmetric test_std_ex test_group test_engine_main
#test_lattice

#SRCS = *.cpp *.h /usr/include/boost/numeric/ublas/matrix.hpp
#CTAGS=etags -o tags

