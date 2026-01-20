#pragma once
#include "../Utils/Math.h"

class Unkownn
{
public:
	char sb[0x120];
};

class GuiData {
private:
	char pad_0x0[0x40];
public:
	Vec2<float> windowSizeReal;
	Vec2<float> windowSizeReal2;
	Vec2<float> windowSizeScaled;
	double guiScale1;
	float guiScale2;
};