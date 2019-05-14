#include "pch.h"
#include "client.h"

void client::write() {
	sock.write_some(boost::asio::buffer(msg));
	std::cout << "writing request to server" << std::endl;
}

void client::read_answer() {
	std::cout << "statring reading answer" << std::endl;
	already_read = 0;
	read(sock, boost::asio::buffer(buff));
	std::cout << buff << std::endl;
}

void client::conversation() {
	write();
	read_answer();
}
