#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <string>
#include <thread>
#include "rs232.h"
#include "Util.h"


class SerialHandler {
	private:
		bool connected;
		bool initializeCommPort();
		int commPortNumber;
	public:
		SerialHandler(int commPortNumber);
		~SerialHandler();
		void sendCommand(std::string);
		std::string receiveCommand();
		void receiveThread();
		void handleReceivedCommand(std::string command);
		bool isConnected();
};

#endif

