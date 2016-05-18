#pragma once
#include "ObjModel.h"
class BowModel :
	public ObjModel
{
public:
	BowModel();
	~BowModel();
	void draw() override;
	void update() override;

};

