#pragma once
#include "AnimatedModel.h"
#include "WiiHAndler.h"
#include "BowModel.h"

class AnimatedExitButtonModel :
	public AnimatedModel
{
public:
	AnimatedExitButtonModel(vector<ObjModel*> models, WiiHandler * wiihandler);
	~AnimatedExitButtonModel();

};
