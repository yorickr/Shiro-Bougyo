//
// Created by Tim Schijvenaars on 03-06-16.
//

#ifndef SHIRO_BOUGYO_GATEMODEL_H
#define SHIRO_BOUGYO_GATEMODEL_H


#include "CollisionModel.h"

class GateModel : public CollisionModel{
public:
    GateModel(string filename);
    ~GateModel();
    void InitBoundingSpheres() override;
private:

};


#endif //SHIRO_BOUGYO_GATEMODEL_H
