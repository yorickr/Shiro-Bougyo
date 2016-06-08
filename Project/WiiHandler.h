//
// Created by Tim Schijvenaars on 16-05-16.
//

#ifndef SHIRO_BOUGYO_WIIHANDLER_H
#define SHIRO_BOUGYO_WIIHANDLER_H


#include "wiiuse/src/wiiuse.h"
#include "Camera.h"


class WiiHandler {

public:
    void handle_event(struct wiimote_t* wm, int i);
    void handle_ctrl_status(struct wiimote_t* wm);
    void handle_disconnect(wiimote* wm);
    void test(struct wiimote_t* wm, byte* data, unsigned short len);
    short any_wiimote_connected(wiimote** wm, int wiimotes);
    void wiiMoteLoop();
    void setWM(struct wiimote_t* wm);
    wiimote_t * wiiMoteP1 = 0;
    wiimote_t * wiiMoteP2 = 0;
	bool is_A1 = false;
	bool Up1_pressed = false;
	bool Down1_pressed = false;
	bool is_A2 = false;
	bool Up2_pressed = false;
	bool Down2_pressed = false;

	int player1X = 0;
	int player1Y = 0;

	float rot1X = 0;
	float rot1Y = -40;
	float rot2X = 0;
	float rot2Y = 0;

};


#endif //SHIRO_BOUGYO_WIIHANDLER_H
