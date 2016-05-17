#include "SerialHandler.h"

SerialHandler::SerialHandler(int commPortNumber)
{
	connected = false;
	this->commPortNumber = commPortNumber;
	if (initializeCommPort()) 
		connected = true;
}

SerialHandler::~SerialHandler()
{
	RS232_CloseComport(commPortNumber);
}

bool SerialHandler::initializeCommPort()
{
	int cPortNr = commPortNumber;
	int baudrate = 9600;

	if (RS232_OpenComport(cPortNr, baudrate, "8N1")) {
		printf("Failed to connect to COMM%i\n" + commPortNumber);
		return 0;
	}
	else {
		printf("Succesfully connected to COMM%i\n" + commPortNumber);
		return 1;
	}
}

void SerialHandler::sendCommand(std::string strCommand)
{
	if(connected)
		RS232_cputs(commPortNumber, strCommand.c_str());
}

std::string SerialHandler::receiveCommand()
{
	unsigned char buf[128];
	std::string command;
	
	int received = RS232_PollComport(commPortNumber, buf, 127);
	if (received > 0) {
		char actualReceivedCommand[128];
		buf[received] = 0; //Null terminator
		for (int x = 0; x < received; x++) {
			if (buf[x] == '\n') {
				actualReceivedCommand[x] = 0;
				break;
			}
			actualReceivedCommand[x] = buf[x];
		}
		command = actualReceivedCommand;
	}
	return command;
}

void * SerialHandler::receiveThread(void * threadID)
{
	while (connected) {
		try {
			std::string received = receiveCommand();
			printf("Received following command: %s\n", received.c_str());
			handleReceivedCommand(received);
		}
		catch (int e) {
			connected = false;
			RS232_CloseComport(commPortNumber);
			printf("Arduino disconnected");
		}
	}
	pthread_exit(NULL);
	return NULL;
}

void SerialHandler::handleReceivedCommand(std::string command)
{
}

bool SerialHandler::isConnected()
{
	return connected;
}
