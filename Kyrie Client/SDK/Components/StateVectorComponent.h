#pragma once
#include "../../Utils/Math.h"

struct StateVectorComponent {
    Vec3<float> mPos;
    Vec3<float> mPosOld;
    Vec3<float> mVelocity;
};