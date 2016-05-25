//
// Created by Yorick Rommers on 20/05/16.
//

#ifndef SHIRO_BOUGYO_ARROWMODEL_H
#define SHIRO_BOUGYO_ARROWMODEL_H


#include "CollisionModel.h"

class ArrowModel : public CollisionModel {
public:
    ArrowModel( float x, float y, float z);


	~ArrowModel(void);

	void InitBoundingSpheres() override;
    void CalcBoundingSpheres() override;

	void draw() override;
    void update(float deltatime) override;
	void fire(float, float, float, float targetx, float targety, float targetz);

    float pointx, pointy, pointz;
private:
	bool isFired = false;
};


#endif //SHIRO_BOUGYO_ARROWMODEL_H
