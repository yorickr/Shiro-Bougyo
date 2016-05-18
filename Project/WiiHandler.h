//
// Created by Tim Schijvenaars on 16-05-16.
//

#ifndef SHIRO_BOUGYO_WIIHANDLER_H
#define SHIRO_BOUGYO_WIIHANDLER_H


#include "wiiuse/src/wiiuse.h"

class WiiHandler {

public:
    void handle_event(struct wiimote_t* wm);
    void handle_read(struct wiimote_t* wm, byte* data, unsigned short len);
    void handle_ctrl_status(struct wiimote_t* wm);
    void handle_disconnect(wiimote* wm);
    void test(struct wiimote_t* wm, byte* data, unsigned short len);
    short any_wiimote_connected(wiimote** wm, int wiimotes);
    void wiiMoteTest();


};


#endif //SHIRO_BOUGYO_WIIHANDLER_H
