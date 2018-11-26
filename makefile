ARGS = -Wall -std=c++11

all: client addUser receiveMessage printUsers





client: client.o helperFunctions.o
	#The client uses curl so don't forget the -l
	g++ client.o helperFunctions.o $(ARGS) -o client -l curl

addUser: addUser.o helperFunctions.o
	g++ addUser.o helperFunctions.o $(ARGS) -o addUser.cgi
	chmod +x addUser.cgi

receiveMessage: receiveMessage.o helperFunctions.o
	g++ receiveMessage.o helperFunctions.o $(ARGS) -o receiveMessage.cgi
	chmod +x receiveMessage.cgi
	
printUsers: printUsers.o
	g++ printUsers.o $(ARGS) -o printUsers.cgi
	chmod +x printUsers.cgi





client.o: client.cpp
	g++ -c client.cpp $(ARGS)

addUser.o: addUser.cpp
	g++ -c addUser.cpp $(ARGS)
	
receiveMessage.o: receiveMessage.cpp
	g++ -c receiveMessage.cpp $(ARGS)
	
helperFunctions.o: helperFunctions.cpp
	g++ -c helperFunctions.cpp $(ARGS)
	
printUsers.o: printUsers.cpp
	g++ -c printUsers.cpp $(ARGS)






clean:
	rm client.o client helperFunctions.o receiveMessage.o receiveMessage.cgi addUser.o addUser.cgi printUsers.cgi printUsers.o
	
	