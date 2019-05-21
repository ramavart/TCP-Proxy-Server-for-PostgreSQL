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
#include "libpq-fe.h"//to emmulate postgres-like connection

using namespace boost::asio;

PGconn * conn = nullptr;

const char * pghost = "127.0.0.1";
const char * pgport = "5431";
const char *dbName = "postgres";
const char *login = "postgres";
const char *pwd = "postgres";
const char *pgoptions = NULL;
const char *pgtty = NULL;



//when I emulate postgres-like request to server it doesn't record anything from buffer #test1

//when I send simple text messages using class client it records as should #test2

int main()
{

	
	//server post
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 5431);

	//db endpoint
	ip::tcp::endpoint epDb(ip::address::from_string("127.0.0.1"), 65273);

	

	std::thread serverThread([]() {
		TCPproxy * serverNode = new TCPproxy(5431,65273);
		serverNode->listen();
	});
	std::this_thread::sleep_for(chrono::milliseconds(500));
	


	//to emulate postgres-like request on login
	//#TEST1
	std::thread clientRequest(PQsetdbLogin, pghost, pgport, pgoptions, pgtty, dbName, login, pwd);


	//simple text message via client
	//#TEST2
	/*std::thread clientThread([&ep]() {
		client * clientNode = new client();
		clientNode->connect(ep);
		clientNode->conversation();
	});*/

	
	//clientThread.join();
	clientRequest.join();
	serverThread.join();
	

		return 0;
}
