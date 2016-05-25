//
//
//

#ifndef SHIRO_BOUGYO_ARROWMODEL_H
#define SHIRO_BOUGYO_ARROWMODEL_H


#include "ObjModel.h"

class ArrowModel : public ObjModel {
public:
    ArrowModel( float x, float y, float z);


	~ArrowModel(void);

	void InitBoundingSpheres() override;
    void CalcBoundingSpheres() override;

	void draw() override;
    void update() override;
	void fire(float, float, float, float targetx, float targety, float targetz);

    float pointx, pointy, pointz;
private:
	bool isFired = false;
};


#endif //SHIRO_BOUGYO_ARROWMODEL_H
