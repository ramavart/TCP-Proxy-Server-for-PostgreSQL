// ConsoleApplication10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <boost/asio.hpp>
#include "client.h"
#include "TCPproxy.h"

using namespace boost::asio;

int main()
{

	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 5431);

	std::thread serverThread([]() {
		TCPproxy * serverNode = new TCPproxy(5431);
		serverNode->listen();
	});
	std::this_thread::sleep_for(chrono::milliseconds(500));
	
	std::thread clientThread([&ep]() {
		client * clientNode = new client();
		clientNode->connect(ep);
		clientNode->conversation();
	});
	
	
	clientThread.join();
	serverThread.join();

		return 0;
}
