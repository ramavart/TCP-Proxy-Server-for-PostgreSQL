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
io_service service;
ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 5431);

void sync_echo(std::string str)
{

	std::cout << "client started" << std::endl;
	auto msg = str.c_str();
	ip::tcp::socket sock(service);
	sock.connect(ep);
	sock.write_some(buffer(str));
	//char buf[1024];
	/*int bytes = read(sock, buffer(buf));
	std::string copy(buf, bytes - 1);
	msg = str.substr(0, str.size() - 1);
	std::cout << "server echoed our " << msg << ": " << (copy == msg ? "OK" : "FAIL") << std::endl;
	sock.close();*/
}

/*

class queueNode {
	queueNode * prev;
	queueNode * next;
public:
	void setPrev(queueNode * obj) { prev = obj; };
	void setNext(queueNode * obj) { next = obj; };
	queueNode * getPrev() { return prev; };
	queueNode *getNext() { return next; };
};

//возможно нужны другие конструкторы разобраться позже
class queue {
	queueNode * first;
	queueNode *last;
public:
	queue() : first(nullptr), last(nullptr) {};
	~queue();
	void setLast(queueNode * obj) { last = obj; };
	void setFirst(queueNode * obj) { first = obj; };
	queueNode * getFirst() { return first; };
	queueNode * getLast() { return last; };
	void pushToQueue(queueNode * obj);
	void popFromQueue();
	void clear(queueNode * nodePtr);
};

void queue::pushToQueue(queueNode * obj) {
	if (getLast() == nullptr && getFirst() == nullptr) {
		setLast(obj);
		setFirst(obj);
	}
	else {
		obj->setPrev(getLast());
		setLast(obj);
	}
}

void queue::popFromQueue() {
	first = first->getPrev();
	delete first->getNext();
}

queue::~queue() {
	clear(last);
}

void queue::clear(queueNode * lastNodePointer) {

	while (lastNodePointer->getPrev()!=nullptr) {
		queueNode * current = lastNodePointer->getPrev();
		delete lastNodePointer;
		clear(current);
	}
}

class client {
	io_service service;
};
*/


size_t read_complete(char * buff,/*const error_code & err, */size_t bytes)
{
	//if (err) return 0;
	bool found = std::find(buff, buff + bytes, '\n') < buff + bytes;
	// we read one-by-one until we get to enter, no buffering
	return found ? 0 : 1;
}

void handle_connections()
{
	
	ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 5431));
	char buff[1024];
	while (true)
	{
		std::cout << "enter the loop" << std::endl;
		ip::tcp::socket sock(service);
		acceptor.accept(sock);
		//int bytes = read(sock, buffer(buff));
		//std::string msg(buff, bytes);
		sock.read_some(buffer(buff, 1000));
		std::cout << "well done" << std::endl;
		std::cout << buff << std::endl;
		std::ofstream log;
		log.open("C:/Users/euge/source/repos/ConsoleApplication10/log.txt", std::ios::app);
		/*for (char symbol : buff) {
			log << symbol;
		}*/
		log << "fuck off";
		log.close();

		sock.close();
		//std::cout << msg << std::endl;
		//sock.write_some(buffer(msg));
		//sock.close();
	}
}


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
	

	/*
	std::thread clientThread([&ep]() {
		client * inst = new client();
		inst->connect(ep);
		inst->conversation();
		
	});*/
	
	clientThread.join();
	serverThread.join();

		return 0;
}
