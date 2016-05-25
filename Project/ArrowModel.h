//
// Created by Yorick Rommers on 20/05/16.
//

#ifndef SHIRO_BOUGYO_ARROWMODEL_H
#define SHIRO_BOUGYO_ARROWMODEL_H


#include "ObjModel.h"
#include "BowModel.h"

class ArrowModel : public ObjModel {
public:
    ArrowModel( float x, float y, float z);

    void InitBoundingSpheres() override;
    void CalcBoundingSpheres() override;

    void update() override;

    float pointx, pointy, pointz;


};


#endif //SHIRO_BOUGYO_ARROWMODEL_H
