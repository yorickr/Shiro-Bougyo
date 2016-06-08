//
// Created by Tim Schijvenaars on 03-06-16.
//

#ifndef SHIRO_BOUGYO_GATEMODEL_H
#define SHIRO_BOUGYO_GATEMODEL_H


#include "CollisionModel.h"

class GateModel : public CollisionModel{
public:
    GateModel(ObjModel *model);
    ~GateModel();
    void InitBoundingSpheres() override;
	
	void setHealth(int health) {
		health_ = health;
	}

	int getHealth() {
		return health_;
	}
private:
	int health_ = 75;

};


#endif //SHIRO_BOUGYO_GATEMODEL_H
