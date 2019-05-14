#include "pch.h"
#include "TCPproxy.h"
//#include <boost/system/error_code.hpp>

//необходимо инициализировать сокеты
//начать слушать 

void TCPproxy::listen() {
	std::cout << "server starting listening" << std::endl;
	while (true) {
		std::cout << "server starting listening" << std::endl;
		clientPtr newConnection(new clientConnection);
		clientAcceptor.accept(newConnection->getSocket()); //после этой функции выолнение не идёт
		std::cout << "server starting listening" << std::endl;
		
		//std::unique_lock <std::recursive_mutex> lock(mx);
		//std::lock_guard<std::recursive_mutex> lock(mx);
		std::scoped_lock lockListener(mx); //c++ 17
		Connections.push_back(newConnection);
		std::this_thread::sleep_for(chrono::seconds(5));//temporary
		clientRequestProcessor();//temporary
		break;//tmp
	}
	printf("end of listen");
	std::cout << "end of listen" << std::endl;
	return;//tmp
}


void TCPproxy::clientRequestProcessor() {
	printf("connections are not empty");
	while (true) {
		if (!Connections.empty()) {
			printf("connections are not empty");
			//std::lock_guard<std::recursive_mutex> lock(mx);
			std::scoped_lock lockProcessor(mx); //c++ 17
			for (clientPtr & iterator : Connections) {
				printf("connections are not empty");
				iterator->handleRequest(); 
				//возможно будет измененно взависимости от 
				//условие для удаления
			}
			
		}
		std::this_thread::sleep_for(chrono::seconds(5));//temporary
		return;
	}
}



