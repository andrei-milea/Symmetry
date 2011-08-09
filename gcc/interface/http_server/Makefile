all:main	
VPATH = ../../engine
CFLAGS =-c -std=c++0x -g -Wall -I /usr/include/boost 
LFLAGS =-lboost_system -lboost_thread-mt -lboost_date_time
GCC = /opt/usr/bin/g++

main:	main.o http_server.o http_connection.o http_request.o http_response.o connection_manager.o estimate.o getsubgrp_command.o getelem_command.o session.o logger.o command_queue.o thread_pool.o result.o
	$(GCC) $^ $(LFLAGS) -o run 


main.o: main.cpp
	$(GCC) $(CFLAGS) $<

http_server.o: http_server.cpp
	$(GCC) $(CFLAGS) $<

http_connection.o: http_connection.cpp
	$(GCC) $(CFLAGS) $<

http_request.o: http_request.cpp
	$(GCC) $(CFLAGS) $<

http_response.o: http_response.cpp
	$(GCC) $(CFLAGS) $<

connection_manager.o: connection_manager.cpp
	$(GCC) $(CFLAGS) $<

estimate.o: estimate.cpp
	$(GCC) $(CFLAGS) $<

getsubgrp_command.o: getsubgrp_command.cpp command.h groupgen_command.h
	$(GCC) $(CFLAGS) $<

getelem_command.o: getelem_command.cpp command.h groupgen_command.h
	$(GCC) $(CFLAGS) $<

session.o: session.cpp
	$(GCC) $(CFLAGS) $<

logger.o: logger.cpp
	$(GCC) $(CFLAGS) $<

command_queue.o: command_queue.cpp
	$(GCC) $(CFLAGS) $<

thread_pool.o: thread_pool.cpp
	$(GCC) $(CFLAGS) $<

result.o: result.cpp
	$(GCC) $(CFLAGS) $<



clean:
	rm -rf *o run main.o 

SRCS = *.cpp *.h 
CTAGS=etags -o tags

tags:
		${CTAGS} $(SRCS)
lint:
		lint $(CFLAGS) $(SRCS)
