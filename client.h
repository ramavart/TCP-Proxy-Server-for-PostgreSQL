#pragma once
#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;

class client
{
	io_service service;
	ip::tcp::socket sock;
	enum {max_msg = 1024};
	int already_read;
	char buff[max_msg];
	bool started;
	
	std::string msg = "CONNECT TO tcp : postgresql://localhost:20/connectdb USER connectuser IDENTIFIED BY connectpw;";
	const char * queryToConnect = "CONNECT TO tcp: postgresql://localhost:20/connectdb USER connectuser IDENTIFIED BY connectpw;";
public:
	client() : sock(service), started(true) {};

	void connect(ip::tcp::endpoint ep) {
		std::cout << "client connecting" << std::endl;
		sock.connect(ep);
	}

	void conversation();
	void write();
	void read_answer();
	//~client();
};

