all:main	
VPATH = ../../engine : ../../lib
CFLAGS =-c -std=c++0x -g -Wall -I /usr/include/boost 
LFLAGS =-lboost_system -pthread -lboost_thread -lboost_date_time -lboost_filesystem
GCC = g++

main:	main.o http_server.o http_connection.o http_request.o http_response.o connection_manager.o estimate.o getcenter_command.o getelem_command.o getcgraph_command.o getrel_command.o getmatexpr_command.o getnorm_command.o getdeterminant_command.o getinverse_command.o getrref_command.o getlinsyssol_command.o univar_polynomial.o getpolyzeros_command.o getpolyplot_command.o getfuncplot_command.o session.o logger.o command_queue.o thread_pool.o pagebuilder.o
	$(GCC) $^ $(LFLAGS) -o run 


main.o: main.cpp
	$(GCC) $(CFLAGS) $<

http_server.o: http_server.cpp
	$(GCC) $(CFLAGS) $<

http_connection.o: http_connection.cpp http_connection.h command_creator.h poly_parser.h func_parser.h linalg_parser.h
	$(GCC) $(CFLAGS) $<

http_request.o: http_request.cpp http_request.h
	$(GCC) $(CFLAGS) $<

http_response.o: http_response.cpp http_response.h
	$(GCC) $(CFLAGS) $<

connection_manager.o: connection_manager.cpp connection_manager.h
	$(GCC) $(CFLAGS) $<

estimate.o: estimate.cpp estimate.h
	$(GCC) $(CFLAGS) $<

getcenter_command.o: getcenter_command.cpp command.h groupgen_command.h
	$(GCC) $(CFLAGS) $<

getelem_command.o: getelem_command.cpp command.h groupgen_command.h
	$(GCC) $(CFLAGS) $<

getcgraph_command.o: getcgraph_command.cpp command.h groupgen_command.h 
	$(GCC) $(CFLAGS) $<

getrel_command.o: getrel_command.cpp command.h groupgen_command.h 
	$(GCC) $(CFLAGS) $<

getmatexpr_command.o: getmatexpr_command.cpp command.h
	$(GCC) $(CFLAGS) $<

getnorm_command.o: getnorm_command.cpp command.h 
	$(GCC) $(CFLAGS) $<

getdeterminant_command.o: getdeterminant_command.cpp command.h 
	$(GCC) $(CFLAGS) $<

getinverse_command.o: getinverse_command.cpp command.h 
	$(GCC) $(CFLAGS) $<

getrref_command.o: getrref_command.cpp command.h
	$(GCC) $(CFLAGS) $<

getlinsyssol_command.o: getlinsyssol_command.cpp command.h
	$(GCC) $(CFLAGS) $<

getpolyzeros_command.o: getpolyzeros_command.cpp command.h
	$(GCC) $(CFLAGS) $<

getpolyplot_command.o: getpolyplot_command.cpp command.h
	$(GCC) $(CFLAGS) $<

getfuncplot_command.o: getfuncplot_command.cpp command.h
	$(GCC) $(CFLAGS) $<

univar_polynomial.o: univar_polynomial.cpp univar_polynomial.h
	$(GCC) $(CFLAGS) $<

session.o: session.cpp session.h
	$(GCC) $(CFLAGS) $<

logger.o: logger.cpp logger.h
	$(GCC) $(CFLAGS) $<

command_queue.o: command_queue.cpp command_queue.h
	$(GCC) $(CFLAGS) $<

thread_pool.o: thread_pool.cpp thread_pool.h
	$(GCC) $(CFLAGS) $<

pagebuilder.o: pagebuilder.cpp pagebuilder.h
	$(GCC) $(CFLAGS) $<

clean:
	rm -rf *o run main.o 
	cd ../../engine; make clean
	cd ../../lib; make clean	

SRCS = *.cpp *.h 
CTAGS=etags -o tags

tags:
		${CTAGS} $(SRCS)
lint:
		lint $(CFLAGS) $(SRCS)
