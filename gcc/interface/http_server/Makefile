all:main	
VPATH = ../../engine
CFLAGS =-c -std=c++0x -g -Wall -I /usr/include/boost 
LFLAGS =-lboost_system -lboost_thread-mt -lboost_date_time
GCC = /opt/usr/bin/g++

main:	main.o http_server.o http_connection.o http_request.o http_response.o connection_manager.o estimate.o getsubgrp_command.o getelem_command.o session.o logger.o command_queue.o thread_pool.o result.o pagebuilder.o
	$(GCC) $^ $(LFLAGS) -o run 


main.o: main.cpp
	$(GCC) $(CFLAGS) $<

http_server.o: http_server.cpp
	$(GCC) $(CFLAGS) $<

http_connection.o: http_connection.cpp http_connection.h
	$(GCC) $(CFLAGS) $<

http_request.o: http_request.cpp http_request.h
	$(GCC) $(CFLAGS) $<

http_response.o: http_response.cpp http_response.h
	$(GCC) $(CFLAGS) $<

connection_manager.o: connection_manager.cpp connection_manager.h
	$(GCC) $(CFLAGS) $<

estimate.o: estimate.cpp estimate.h
	$(GCC) $(CFLAGS) $<

getsubgrp_command.o: getsubgrp_command.cpp command.h groupgen_command.h
	$(GCC) $(CFLAGS) $<

getelem_command.o: getelem_command.cpp command.h groupgen_command.h
	$(GCC) $(CFLAGS) $<

session.o: session.cpp session.h
	$(GCC) $(CFLAGS) $<

logger.o: logger.cpp logger.h
	$(GCC) $(CFLAGS) $<

command_queue.o: command_queue.cpp command_queue.h
	$(GCC) $(CFLAGS) $<

thread_pool.o: thread_pool.cpp thread_pool.h
	$(GCC) $(CFLAGS) $<

result.o: result.cpp result.h
	$(GCC) $(CFLAGS) $<

pagebuilder.o: pagebuilder.cpp pagebuilder.h
	$(GCC) $(CFLAGS) $<




clean:
	rm -rf *o run main.o 

SRCS = *.cpp *.h 
CTAGS=etags -o tags

tags:
		${CTAGS} $(SRCS)
lint:
		lint $(CFLAGS) $(SRCS)
