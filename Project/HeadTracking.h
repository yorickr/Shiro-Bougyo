//
// Created by Yorick Rommers on 2016/06/08.
//


#ifndef SHIRO_BOUGYO_HEADTRACKING_H
#define SHIRO_BOUGYO_HEADTRACKING_H

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
//#include <unistd.h>

#include "Player.h"

class HeadTracking {
public:
    HeadTracking(std::vector<Player*> players);
	bool running = false;
    ~HeadTracking();
    std::vector<Player*> players;
    void cameraThreadFunc();
    void initThread();
};


#endif //SHIRO_BOUGYO_HEADTRACKING_H
