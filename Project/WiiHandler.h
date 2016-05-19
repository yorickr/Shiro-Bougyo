//
// Created by Tim Schijvenaars on 16-05-16.
//

#ifndef SHIRO_BOUGYO_WIIHANDLER_H
#define SHIRO_BOUGYO_WIIHANDLER_H


#include "wiiuse/src/wiiuse.h"
#include "Camera.h"


class WiiHandler {

public:
    void handle_event(struct wiimote_t* wm, Camera* camera);
    void handle_read(struct wiimote_t* wm, byte* data, unsigned short len);
    void handle_ctrl_status(struct wiimote_t* wm);
    void handle_disconnect(wiimote* wm);
    void test(struct wiimote_t* wm, byte* data, unsigned short len);
    short any_wiimote_connected(wiimote** wm, int wiimotes);
    void wiiMoteTest(Camera* cam);
    void setWM(struct wiimote_t* wm);
    wiimote_t * wiiMoteP1;
    wiimote_t * wiiMoteP2;

};


#endif //SHIRO_BOUGYO_WIIHANDLER_H
