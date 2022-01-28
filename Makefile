all: server client

server: objects/server.o
	g++ objects/server.o -o build/server

objects/server.o: server/server.cpp
	g++ -c server/server.cpp -o objects/server.o

client: objects/client.o
	g++ objects/client.o -o build/client

objects/client.o: client/client.cpp
	g++ -c client/client.cpp -o objects/client.o

clean:
	rm ./build/* ./objects/*

init:
	mkdir build objects
