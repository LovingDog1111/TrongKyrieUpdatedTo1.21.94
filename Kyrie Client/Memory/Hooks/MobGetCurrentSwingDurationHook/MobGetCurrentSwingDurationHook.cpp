#include "MobGetCurrentSwingDurationHook.h"
#include "../../../Client/Client.h"
#include "../../Memory.h"

typedef int(__fastcall* getSwingDuration)(Mob*);
getSwingDuration _getSwingDuration;

int MobGetCurrentSwingDurationHook::MobGetCurrentSwingDuration(Mob* a1) {
	static Swing* swingMod = client->moduleMgr->getModule<Swing>();
	if (swingMod->isEnabled() && a1 == (Mob*)mc.getLocalPlayer()) return swingMod->speed;
	return _getSwingDuration(a1);
}

void MobGetCurrentSwingDurationHook::init() {
	uintptr_t address = Memory::findSig("48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 83 EC ? 8B 41 ? 48 8D 54 24 ? 48 8B 35");
	if (!address) return;
	Memory::CreateHook("MobGetCurrentSwingDurationHook", address, &MobGetCurrentSwingDurationHook::MobGetCurrentSwingDuration, &_getSwingDuration);
}