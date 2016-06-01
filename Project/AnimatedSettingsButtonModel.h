#pragma once
#include "AnimatedModel.h"
#include "WiiHAndler.h"
#include "BowModel.h"

class AnimatedSettingsButtonModel :
	public AnimatedModel
{
public:
	AnimatedSettingsButtonModel(vector<ObjModel*> models, WiiHandler * wiihandler);
	~AnimatedSettingsButtonModel();

};
