#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <string>

class SerialHandler {
	private:

	public:
		SerialHandler(std::string commPort);
		void sendCommand(std::string);
		std::string receiveCommand();
};

#endif

