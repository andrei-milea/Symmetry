all: engine_test
CFLAGS = -std=c++0x -c -g -Wall -I /usr/include/boost 
LFLAGS = -lboost_thread
GCC = /opt/usr/bin/g++

engine_test: engine_test.o estimate.o getsubgrp_command.o getelem_command.o session.o
	$(GCC) $(LFLAGS) engine_test.o estimate.o getsubgrp_command.o getelem_command.o session.o -o engine_test

engine_test.o: engine_test.cpp
	$(GCC) $(CFLAGS) engine_test.cpp -o engine_test.o

estimate.o: estimate.cpp
	$(GCC) $(CFLAGS) estimate.cpp -o estimate.o 

getsubgrp_command.o: getsubgrp_command.cpp
	$(GCC) $(CFLAGS) getsubgrp_command.cpp -o getsubgrp_command.o

getelem_command.o: getelem_command.cpp
	$(GCC) $(CFLAGS) getelem_command.cpp -o getelem_command.o

session.o: session.cpp
	$(GCC) $(CFLAGS) session.cpp -o session.o
clean:
	rm -rf *.o engine_test
