#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <boost/asio.hpp>

using namespace boost::asio;

class clientConnection : public std::enable_shared_from_this<clientConnection> {
	io_service service;
	ip::tcp::socket socket;
	
	enum { maxLength_ = 1024, maxLengthDataDB = 10000 }; 
	char data[maxLength_];
	char dataFromDB[maxLengthDataDB];
	int already_read;
	bool started_;
	time_t lastRequestDate;
public:
	clientConnection() : already_read(0), started_(false), socket(service) { std::cout << "client connection record created on the server side" << std::endl; }// будет ли заблокирован, если акцептор ипользует другой объект io_service
	ip::tcp::socket & getSocket() { return socket; }; 
	void logRequest();
	void handleRequest();
	void readRequest();
	void parseQuery();
	void makeCalltoDB();
	void processDBResponse();
	void setDate() { lastRequestDate = time(NULL); };
	void sendResponseToClient();

};

