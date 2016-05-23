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
	void update() override;
private: 
	Camera * camera;
	void SetPositionMenu(float x, float y, float rotx, float roty);
	ObjModel * playButton;
	ObjModel * settingsButton;
	ObjModel * exitButton;
	WiiHandler * wiiHandler;
};
