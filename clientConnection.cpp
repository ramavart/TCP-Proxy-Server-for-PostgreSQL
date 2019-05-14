#include "pch.h"
#include "clientConnection.h"

void clientConnection::logRequest() {
	std::ofstream log;
	log.open("log.txt", std::ios::app);
		for (char symbol : data) {
			log << symbol;
		}
		log.close();
	return;
}

void clientConnection::handleRequest(){

	std::cout << "handleRequest started" << std::endl;
	readRequest();
	//std::thread logwriter(&clientConnection::logRequest);
	//logwriter.join();
	std::cout << data << std::endl;
	//parseQuery();
	//makeCalltoDB();
	//processDBResponse();
	
}

void clientConnection::readRequest() {
	if (socket.available()) {
		std::cout << "reading request to buffer" << std::endl;
		already_read_ += socket.read_some(buffer(data + already_read_, maxLength_ - already_read_));
	}
}

void clientConnection::parseQuery() {

}

void clientConnection::makeCalltoDB() {

}

void clientConnection::processDBResponse() {

}