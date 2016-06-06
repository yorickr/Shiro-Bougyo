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
#include "GameStateManager.h"
#include "PlayingState.h"


class SerialHandler {
private:
	bool connected;
	bool initializeCommPort();
	void connectThread();
	int commPortNumber;
	GameStateManager *gameManager;
public:
	SerialHandler(int commPortNumber, GameStateManager *gameManager);
	~SerialHandler();
	void sendCommand(std::string);
	std::string receiveCommand();
	void receiveThread();
	void handleReceivedCommand(std::string command);
	bool isConnected();
};

#endif
