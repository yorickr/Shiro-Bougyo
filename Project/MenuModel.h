#pragma once
#include "ObjModel.h"
#include "Camera.h"
#include "WiiHandler.h"

class MenuModel :
	public ObjModel
{	
public:
	MenuModel(Camera * camera, WiiHandler * wiiHandler,string filename);
	~MenuModel();
    void draw() override;
	void update(float deltatime) override;
	//void update(float deltatime, bool *keys) override;
	ObjModel * playButton;
	ObjModel * playButtonPressed;
	ObjModel * settingsButton;
	ObjModel * settingsButtonPressed;
	ObjModel * exitButton;
	ObjModel * exitButtonPressed;
private: 
	Camera * camera;
	int counter = 0;
	void SetPositionMenu(float x, float y, float rotx, float roty);
	WiiHandler * wiiHandler;
};
