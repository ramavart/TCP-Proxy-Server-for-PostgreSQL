#include "pch.h"
#include "TCPproxy.h"
//#include <boost/system/error_code.hpp>

//���������� ���������������� ������
//������ ������� 

void TCPproxy::listen() {
	while (true) {
		clientPtr newConnection(new clientConnection);
		clientAcceptor.accept(newConnection->getSocket());
		newConnection->setDate();
		std::cout << "server starting listening" << std::endl;
		std::scoped_lock lockListener(mx); //c++ 17
		Connections.push_back(newConnection);
		
	}
}

//���������� �������� �������, ����� �������� ������ ����� �������� �� ���������� �/��� ������� ����� ����� ������ � ���
void TCPproxy::clientRequestProcessor() {
	while (true) {
		if (!Connections.empty()) {
			std::scoped_lock lockProcessor(mx); //c++ 17
			for (clientPtr & iterator : Connections) {
				printf("connections are not empty");
				iterator->handleRequest(); 
				//�������� ����� ��������� ������������ �� 
				//������� ��� ��������
			}
		}
	}
}



