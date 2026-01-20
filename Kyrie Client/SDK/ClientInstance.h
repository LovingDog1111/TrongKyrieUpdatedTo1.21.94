#pragma once
#include "GuiData.h"
#include "../Utils/Utils.h"
#include "Player.h"
#include "LevelRenderer.h"
#include "../Memory/Hooks/KeyMouseHook/KeyMouseHook.h"

class ClientInstance {
private:
	uintptr_t** VTable;
public:
	//BUILD_ACCESS(this, LevelRenderer*, levelRenderer, 0x00E0);
	//BUILD_ACCESS(this, glmatrixf*, badrefdef, 0x330);
	BUILD_ACCESS(this, GuiData*, guiData, 0x5B8);
public:

	LevelRenderer* getlevelRenderer() {
		//return Y::callVirtualFunc<LevelRenderer*>(216, this);
		return Utils::CallVFunc2<LevelRenderer*>(216, this);
	}

	glmatrixf* getBadRefDef() {
		return reinterpret_cast<glmatrixf*>((uintptr_t)(this) + 0x330);
	};

	Vec2<float> getFov() {
		Vec2<float> fov = { 90.f, 90.f }; //unfinished im lazy af
		return fov;
	}

	Player* getLocalPlayer() {
		return Utils::CallVFunc<31, Player*>(this);
	}

	void grabMouse() {
		Utils::CallVFunc<347, void>(this);
	}

	void releasebMouse() {
		Utils::CallVFunc<348, void>(this);
	}
};