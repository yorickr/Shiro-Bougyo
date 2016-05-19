#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <string>
#include <thread>
#include "rs232.h"
#include "Util.h"


class SerialHandler {
	private:
		bool connected;
		bool initializeCommPort();
		void connectThread();
		int commPortNumber;

	public:
		SerialHandler(std::string commPort);
		void sendCommand(std::string);
		std::string receiveCommand();
		void receiveThread();
		void handleReceivedCommand(std::string command);
		bool isConnected();

};

#endif

