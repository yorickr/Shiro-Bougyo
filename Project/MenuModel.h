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
	//void update(float deltatime, bool keys) override;
private: 
	Camera * camera;
	void SetPositionMenu(float x, float y, float rotx, float roty);
	void SetButtonPosition(float xpos, float ypos,float zpos, float xrot,float yrot, ObjModel *model);
	void SetPositionMouse(int x, int y,ObjModel *model);
	ObjModel * playButton;
	ObjModel * playButtonPressed;
	ObjModel * settingsButton;
	ObjModel * settingsButtonPressed;
	ObjModel * exitButton;
	ObjModel * exitButtonPressed;
	ObjModel * mouseCursor;
	WiiHandler * wiiHandler;
};
