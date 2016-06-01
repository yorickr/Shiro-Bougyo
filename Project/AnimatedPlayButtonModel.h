#pragma once
#include "AnimatedModel.h"
#include "WiiHAndler.h"
#include "BowModel.h"

class AnimatedPlayButtonModel :
	public AnimatedModel
{
public:
	AnimatedPlayButtonModel(vector<ObjModel*> models, WiiHandler * wiihandler);
	~AnimatedPlayButtonModel();

};
