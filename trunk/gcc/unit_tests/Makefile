all: test_tree test_perm test_group_el test_symmetric test_std_ex test_cayley_grf test_group test_engine_main test_server_main test_results_db test_matrix
CFLAGS = -c -std=c++0x -g -Wall -I /usr/include/boost 
BFLAGS = -std=c++0x -g -Wall -I /usr/include/boost 
LFLAGS =-lboost_system -pthread -lboost_thread-mt -lboost_date_time -lboost_iostreams -lboost_filesystem -lboost_random
GCC = g++
VPATH = ../interface/http_server:../engine

test_poly: test_poly.cpp ../lib/univar_polynomial.h
	$(GCC) $(BFLAGS) test_poly.cpp -o test_poly

test_tree: test_tree.cpp
	$(GCC) $(BFLAGS) test_tree.cpp -o test_tree

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

test_matrix: test_matrix.cpp
	$(GCC) $(BFLAGS) test_matrix.cpp -o test_matrix

test_cayley_grf: test_cayley_grf.cpp
	$(GCC) $(BFLAGS) test_cayley_grf.cpp -o test_cayley_grf

test_lattice: test_lattice.cpp
	$(GCC) $(BFLAGS) test_lattice.cpp -o test_lattice

	########################
	#test_engine compilation
	########################

test_engine_main: test_engine.o estimate.o getelem_command.o getcenter_command.o getcgraph_command.o getrel_command.o getmatexpr_command.o getnorm_command.o getdeterminant_command.o getinverse_command.o session.o logger.o command_queue.o thread_pool.o
	$(GCC) $^ $(LFLAGS) -o test_engine_main

test_engine.o: test_engine.cpp
	$(GCC) $(CFLAGS) $<

estimate.o: ../engine/estimate.cpp
	$(GCC) $(CFLAGS) $<

getelem_command.o: ../engine/getelem_command.cpp
	$(GCC) $(CFLAGS) $<

getcenter_command.o: ../engine/getcenter_command.cpp
	$(GCC) $(CFLAGS) $<

getcgraph_command.o: ../engine/getcgraph_command.cpp
	$(GCC) $(CFLAGS) $<

getmatexpr_command.o: ../engine/getmatexpr_command.cpp
	$(GCC) $(CFLAGS) $<

getnorm_command.o: ../engine/getnorm_command.cpp
	$(GCC) $(CFLAGS) $<

getdeterminant_command.o: ../engine/getdeterminant_command.cpp
	$(GCC) $(CFLAGS) $<

getinverse_command.o: ../engine/getinverse_command.cpp
	$(GCC) $(CFLAGS) $<

getrel_command.o: ../engine/getrel_command.cpp
	$(GCC) $(CFLAGS) $<

session.o: ../engine/session.cpp
	$(GCC) $(CFLAGS) $<

logger.o: ../engine/logger.cpp
	$(GCC) $(CFLAGS) $<

command_queue.o: ../engine/command_queue.cpp
	$(GCC) $(CFLAGS) $<

thread_pool.o: ../engine/thread_pool.cpp
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


	########################
	#test internal database
	########################

test_results_db: test_db.o results_bucket.o results_db.o
	$(GCC) $^ $(LFLAGS) -o test_results_db

test_db.o: test_db.cpp
	$(GCC) $(CFLAGS) $<

results_bucket.o: ../engine/results_bucket.cpp
	$(GCC) $(CFLAGS) $<

results_db.o: ../engine/results_db.cpp
	$(GCC) $(CFLAGS) $<

	########################
	########################


clean:
	rm -rf *.o $(TESTS)
	cd ../engine; make clean
	cd ../interface/http_server; make clean
	
TESTS = test_tree test_perm test_group_el test_symmetric test_std_ex test_group test_cayley_grf test_engine_main test_server_main test_results_db test_matrix
#test_lattice 

#SRCS = *.cpp *.h /usr/include/boost/numeric/ublas/matrix.hpp
#CTAGS=etags -o tags

