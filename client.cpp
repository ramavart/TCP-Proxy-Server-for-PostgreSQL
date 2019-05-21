#include "pch.h"
#include "client.h"

void client::write() {
	sock.write_some(boost::asio::buffer(msgconnect));
	std::cout << "writing request to server" << std::endl;
}

void client::read_answer() {
	std::cout << "statring reading answer" << std::endl;
	already_read = 0;
	if (sock.available()) {
		already_read += sock.read_some(buffer(buff + already_read, max_msg - already_read));
	}
	std::cout << "client readed the message" << buff << std::endl;
}

void client::conversation() {
	write();
	//std::this_thread::sleep_for(chrono::seconds(5));
	read_answer();
	//std::this_thread::sleep_for(chrono::seconds(120));
}
