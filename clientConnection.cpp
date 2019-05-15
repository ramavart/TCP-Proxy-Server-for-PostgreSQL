#include "pch.h"
#include "clientConnection.h"
#include <time.h>

//добавить в запись IP
void clientConnection::logRequest() {
	std::ofstream log;
	char dateBuffer[70];
	log.open("C:/Users/euge/source/repos/ConsoleApplication10/log.txt", std::ios::app);
	asctime_s(dateBuffer, sizeof dateBuffer, gmtime(&lastRequestDate)); //GMT
	log << dateBuffer << "/" << data << std::endl;
		log.close();
	return;
}

void clientConnection::handleRequest(){

	std::cout << "handleRequest started" << std::endl;
	readRequest();
	std::thread logwriter(&clientConnection::logRequest, this);
	logwriter.join();
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