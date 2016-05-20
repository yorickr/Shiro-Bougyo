#pragma once
#include "ObjModel.h"
#include "Camera.h"
#include "WiiHandler.h"

class MenuModel :
	public ObjModel
{	
public:
	MenuModel(Camera * camera, WiiHandler * wiiHandler);
	~MenuModel();
	void draw() override;
	void update() override;
private: 
	Camera * camera;
	ObjModel * playButton;
	ObjModel * settingsButton;
	ObjModel * exitButton;
	WiiHandler * wiiHandler;
};