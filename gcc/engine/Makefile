all: engine_test
CFLAGS = -std=c++0x -c -g -Wall -I /usr/include/boost 
LFLAGS = -lboost_thread -lboost_date_time
GCC = g++

engine_test: engine_test.o estimate.o getcenter_command.o getelem_command.o getcgraph_command.o session.o logger.o command_queue.o thread_pool.o result.o
	$(GCC) $(LFLAGS) engine_test.o estimate.o getcenter_command.o getelem_command.o getcgraph_command.o session.o logger.o command_queue.o thread_pool.o result.o -o engine_test

engine_test.o: engine_test.cpp
	$(GCC) $(CFLAGS) engine_test.cpp -o engine_test.o

estimate.o: estimate.cpp
	$(GCC) $(CFLAGS) estimate.cpp -o estimate.o 

getcenter_command.o: command.h groupgen_command.h getcenter_command.cpp
	$(GCC) $(CFLAGS) getcenter_command.cpp -o getcenter_command.o

getelem_command.o: command.h groupgen_command.h getelem_command.cpp
	$(GCC) $(CFLAGS) getelem_command.cpp -o getelem_command.o

getcgraph_command.o: command.h groupgen_command.h getcgraph_command.cpp
	$(GCC) $(CFLAGS) getcgraph_command.cpp -o getcgraph_command.o

session.o: session.cpp
	$(GCC) $(CFLAGS) session.cpp -o session.o

logger.o: logger.cpp
	$(GCC) $(CFLAGS) logger.cpp -o logger.o

command_queue.o: command_queue.cpp
	$(GCC) $(CFLAGS) command_queue.cpp -o command_queue.o

thread_pool.o: thread_pool.cpp
	$(GCC) $(CFLAGS) thread_pool.cpp -o thread_pool.o

result.o: result.cpp
	$(GCC) $(CFLAGS) result.cpp -o result.o

clean:
	rm -rf *.o engine_test
