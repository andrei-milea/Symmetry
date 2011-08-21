all: test_perm test_group_el test_symmetric test_std_ex test_group test_engine_main test_server_main
CFLAGS = -c -std=c++0x -g -Wall -I /usr/include/boost 
BFLAGS = -std=c++0x -g -Wall -I /usr/include/boost 
LFLAGS =-lboost_system -lboost_thread-mt -lboost_date_time
GCC = /opt/usr/bin/g++
VPATH = ../interface/http_server:../engine


test_perm: test_permutation.cpp
	$(GCC) $(BFLAGS) test_permutation.cpp -o test_perm

test_group_el: test_group_elem.cpp
	$(GCC) $(BFLAGS) test_group_elem.cpp -o test_group_el

test_symmetric: test_symmetric_rep.cpp
	$(GCC) $(BFLAGS) test_symmetric_rep.cpp -o test_symmetric

test_std_ex: test_std_ex.cpp
	$(GCC) $(BFLAGS) test_std_ex.cpp -o test_std_ex

test_group: test_group.cpp
	$(GCC) $(BFLAGS) test_group.cpp -o test_group

test_lattice: test_lattice.cpp
	$(GCC) $(BFLAGS) test_lattice.cpp -o test_lattice

	########################
	#test_engine compilation
	########################

test_engine_main: test_engine.o estimate.o getelem_command.o getsubgrp_command.o session.o logger.o command_queue.o thread_pool.o result.o
	$(GCC) $^ $(LFLAGS) -o test_engine_main


test_engine.o: test_engine.cpp
	$(GCC) $(CFLAGS) $<

estimate.o: ../engine/estimate.cpp
	$(GCC) $(CFLAGS) $<

getsubgrp_command.o: ../engine/getsubgrp_command.cpp
	$(GCC) $(CFLAGS) $<

getelem_command.o: ../engine/getelem_command.cpp
	$(GCC) $(CFLAGS) $<

session.o: ../engine/session.cpp
	$(GCC) $(CFLAGS) $<

logger.o: ../engine/logger.cpp
	$(GCC) $(CFLAGS) $<

command_queue.o: ../engine/command_queue.cpp
	$(GCC) $(CFLAGS) $<

thread_pool.o: ../engine/thread_pool.cpp
	$(GCC) $(CFLAGS) $<

result.o: ../engine/result.cpp
	$(GCC) $(CFLAGS) $<

	########################
	########################


	########################
	#test server compilation
	########################

test_server_main: test_server.o http_request.o
	$(GCC) $^ $(LFLAGS) -o test_server_main

test_server.o: test_server.cpp
	$(GCC) $(CFLAGS) $<

http_request.o: http_request.cpp
	$(GCC) $(CFLAGS) $<

	########################
	########################



clean:
	rm -rf *.o $(TESTS)
	cd ../engine; make clean
	cd ../interface/http_server; make clean
	
TESTS = test_perm test_group_el test_symmetric test_std_ex test_group test_engine_main test_server_main
#test_lattice

#SRCS = *.cpp *.h /usr/include/boost/numeric/ublas/matrix.hpp
#CTAGS=etags -o tags

