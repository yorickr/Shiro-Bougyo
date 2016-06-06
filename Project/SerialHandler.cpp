#include "SerialHandler.h"

SerialHandler::SerialHandler(int commPortNumber, GameStateManager gameManager)
{
	connected = false;
	this->commPortNumber = commPortNumber;
	this->gameManager = gameManager;
	if (initializeCommPort())
		connected = true;
	else {
		std::thread connectThread(&SerialHandler::connectThread, this); //Serialthread
		connectThread.detach();
	}
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
		//printf("Failed to connect to COMM%i\n" + commPortNumber);
		return 0;
	}
	else {
		printf("Succesfully connected to COMM%i\n" + commPortNumber);
		return 1;
	}
}

void SerialHandler::connectThread()
{
	while (!isConnected()) {
		if (initializeCommPort())
			connected = true;
		Util::USleep(1000);
	}
}

void SerialHandler::sendCommand(std::string strCommand)
{
	if (isConnected())
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

void SerialHandler::receiveThread()
{
	while (true) {
		if (isConnected()) {
			try {
				std::string received = receiveCommand();
				printf("Received following command: %s\n", received.c_str());
				handleReceivedCommand(received);
			}
			catch (int e) {
				connected = false;
				RS232_CloseComport(commPortNumber);
				printf("Serial device disconnected");
			}
		}
		else{ 
			//printf("not connected\n"); 
		}
		Util::USleep(1000);
	}
}

void SerialHandler::handleReceivedCommand(std::string command)
{
	if (command == "PP1" || command == "PP2") { //Check if the action needs to be executed from playingstate.
		PlayingState *playState = dynamic_cast<PlayingState*>(gameManager.getCurrentState());
		if (playState) {
			if (command == "PP1")
				playState->ScalePowerUp();
			else if (command == "PP2")
				printf("smthing");
		}			
	}
}

bool SerialHandler::isConnected()
{
	return connected;
}