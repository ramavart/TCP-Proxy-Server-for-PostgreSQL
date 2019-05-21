#include "pch.h"
#include "clientConnection.h"
#include <time.h>

//добавить в запись IP
void clientConnection::logRequest() {
	std::ofstream log;
	char dateBuffer[70];
	log.open("C:/Users/euge/source/repos/ConsoleApplication10/log.txt", std::ios::app);
	asctime_s(dateBuffer, sizeof dateBuffer, gmtime(&lastRequestDate)); 
	log << dateBuffer << "/" << data << std::endl;
		log.close();
	return;
}

void clientConnection::handleRequest(){

	//std::cout << "handleRequest started" << std::endl;
	readRequest();
	if (*data == 0) return;
	std::thread logwriter(&clientConnection::logRequest, this);
	logwriter.join();
	std::cout << data << std::endl;
	std::copy(data, data + already_read, dataFromDB);
	std::cout << dataFromDB << std::endl;

	//std::memset(data, 0,maxLength_);
	//already_read_ = 0;
	//parseQuery();
	//makeCalltoDB();
	//processDBResponse();
	//sendResponseToClient();
}

void clientConnection::readRequest() {
	if (socket.available()) {
		std::cout << "reading request to buffer" << std::endl;
		already_read += socket.read_some(buffer(data + already_read, maxLength_ - already_read));
		std::cout << data << std::endl;
	}
}

void clientConnection::sendResponseToClient() {
	socket.write_some(buffer(dataFromDB));
}

void clientConnection::parseQuery() {

}

void clientConnection::makeCalltoDB() {

}

void clientConnection::processDBResponse() {

}