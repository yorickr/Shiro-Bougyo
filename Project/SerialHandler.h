#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <string>
#include "rs232.h"


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
		bool isConnected();
};

#endif

