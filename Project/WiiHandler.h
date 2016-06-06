//
// Created by Tim Schijvenaars on 16-05-16.
//

#ifndef SHIRO_BOUGYO_WIIHANDLER_H
#define SHIRO_BOUGYO_WIIHANDLER_H


#include "wiiuse/src/wiiuse.h"
#include "Camera.h"


class WiiHandler {

public:
    void handle_event(struct wiimote_t* wm);
    void handle_ctrl_status(struct wiimote_t* wm);
    void handle_disconnect(wiimote* wm);
    void test(struct wiimote_t* wm, byte* data, unsigned short len);
    short any_wiimote_connected(wiimote** wm, int wiimotes);
    void wiiMoteLoop();
    void setWM(struct wiimote_t* wm);
    wiimote_t * wiiMoteP1 = 0;
    wiimote_t * wiiMoteP2 = 0;
	bool is_A = false;
	bool Up_pressed = false;
	bool Down_pressed = false;
	int player1X = 0;
	int player1Y = 0;
	struct nunchuk_t* nc;
	float rot1X = 0;
	float rot1Y = 0;
	float rot2X = 0;
	float rot2Y = 0;


};


#endif //SHIRO_BOUGYO_WIIHANDLER_H
