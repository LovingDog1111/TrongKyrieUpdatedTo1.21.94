#pragma once
#include "../Utils/Math.h"
#include "../Utils/Utils.h"

class LevelRendererPlayer {
public:
    CLASS_MEMBER(Vec3<float>, cameraPos, 0x664);
    CLASS_MEMBER(Vec3<float>, origin, 0x670);
    CLASS_MEMBER(Vec3<float>, mOrigin, 0x670);
    CLASS_MEMBER(Vec3<float>, Origin, 0x670);
};