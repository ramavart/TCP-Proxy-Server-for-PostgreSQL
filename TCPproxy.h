#pragma once
#include <mutex>
#include <thread>
#include <iostream>
#include <boost/asio.hpp>
//#include <boost/system/error_code.hpp>
#include "clientConnection.h"
#include <chrono>


using namespace boost::asio;

class TCPproxy {

	using clientPtr = std::shared_ptr<clientConnection>;
	using clientArray = std::vector <clientPtr>;
	clientArray Connections;
	unsigned short portToDB;
	io_service service;
	ip::tcp::acceptor clientAcceptor;
	std::recursive_mutex mx;
	
public:
	void listen();
	TCPproxy(unsigned short portToClient, unsigned short portToDB) :
		clientAcceptor(service, ip::tcp::endpoint(ip::tcp::v4(), portToClient)), portToDB(portToDB) {
			std::thread thRequestProcessor(&TCPproxy::clientRequestProcessor, this);
			std::cout << "server started" << std::endl;
			thRequestProcessor.detach();
	};
	~TCPproxy() {};
	void clientRequestProcessor(); //need to add conition to return

};
