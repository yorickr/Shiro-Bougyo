//
// Created by Yorick Rommers on 19/05/16.
//

#ifndef SHIRO_BOUGYO_STATIONARYOBJMODEL_H
#define SHIRO_BOUGYO_STATIONARYOBJMODEL_H


#include "ObjModel.h"

class StationaryObjModel : public ObjModel{

public:
    StationaryObjModel(const string &filename) : ObjModel(filename) { }

    virtual void update() override;
};


#endif //SHIRO_BOUGYO_STATIONARYOBJMODEL_H
