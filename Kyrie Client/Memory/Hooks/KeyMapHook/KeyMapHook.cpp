#include "KeyMapHook.h"
#include "../../Memory.h"
#include "../../../Client/Client.h"

typedef __int64(__fastcall* Key)(unsigned char, bool);
Key _Key;

__int64 KeyMapHook::KeyMapCallBack(unsigned char key, bool isDown) {
    if (!client->moduleMgr->isInitialized()) return 0;
    static ClickGui* clickGuiMod = client->moduleMgr->getModule<ClickGui>();
    if (clickGuiMod->isEnabled()) {
        clickGuiMod->onKeyUpdate(key, isDown);
        return 0;
    }
    client->moduleMgr->onKeyUpdate(key, isDown);
    return _Key(key, isDown);
}

void KeyMapHook::init() {
    uintptr_t address = Memory::findSig("48 ? ? 48 ? ? ? 4C 8D 05 ? ? ? ? 89");
    if (!address) {
        Utils::DebugF("KeyMapHook signature not found!");
        return;
    }

    Memory::CreateHook("KeyMapHook", address, &KeyMapHook::KeyMapCallBack, &_Key);
}
