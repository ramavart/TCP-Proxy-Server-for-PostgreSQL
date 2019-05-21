#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <thread>

using namespace boost::asio;

class client
{
	io_service service;
	ip::tcp::socket sock;
	enum {max_msg = 1024};
	int already_read;
	char buff[max_msg];
	bool started;
	

	std::string msgconnect = "30199608userpostgresdatabasepostgres";
	std::string request = "select color from polygons";

	
public:
	client() : sock(service), started(true) {};

	void connect(ip::tcp::endpoint ep) {
		std::cout << "client connecting" << std::endl;
		sock.connect(ep);
	}

	void conversation();
	void write();
	void read_answer();
	~client();
};

