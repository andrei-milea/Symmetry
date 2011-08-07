all:main	
CFLAGS =-c -std=c++0x -g -Wall -I /usr/include/boost 
LFLAGS =-lboost_system
GCC = /opt/usr/bin/g++

main:	main.o http_server.o http_connection.o http_request.o http_response.o connection_manager.o 
	$(GCC) $(LFLAGS) http_connection.o http_request.o http_response.o http_server.o connection_manager.o main.o -o run 

main.o: main.cpp
	$(GCC) $(CFLAGS) main.cpp -o main.o 

http_server.o: http_server.cpp
	$(GCC) $(CFLAGS) http_server.cpp -o http_server.o

http_connection.o: http_connection.cpp
	$(GCC) $(CFLAGS) http_connection.cpp -o http_connection.o

http_request.o: http_request.cpp
	$(GCC) $(CFLAGS) http_request.cpp -o http_request.o

http_response.o: http_response.cpp
	$(GCC) $(CFLAGS) http_response.cpp -o http_response.o

connection_manager.o: connection_manager.cpp
	$(GCC) $(CFLAGS) connection_manager.cpp -o connection_manager.o


clean:
	rm -rf *o run main.o 

SRCS = *.cpp *.h 
CTAGS=etags -o tags

tags:
		${CTAGS} $(SRCS)
lint:
		lint $(CFLAGS) $(SRCS)
