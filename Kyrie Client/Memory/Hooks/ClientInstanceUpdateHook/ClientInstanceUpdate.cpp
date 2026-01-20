#include "ClientInstanceUpdate.h"
#include "../../Memory.h"
#include "../../GameData/GameData.h"

typedef __int64(__thiscall* ClientInstanceUpdate_t)(ClientInstance*, bool);
ClientInstanceUpdate_t _ClientInstanceUpdate;

__int64 ClientInstanceUpdateHook::ClientInstanceUpdateCallBack(ClientInstance* _this, bool a2) {
    if (mc.getClientInstance() == nullptr) {
        mc.setClientInstance(_this);
        //Utils::DebugF("%llx", (*((uintptr_t**)renderCtx))[7]);
    }
    return _ClientInstanceUpdate(_this, a2);
}

void ClientInstanceUpdateHook::init() {
    uintptr_t address = Memory::findSig(
        "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 44 0F B6 FA"
    );

    Memory::CreateHook("ClientInstanceUpdateHook", address, &ClientInstanceUpdateHook::ClientInstanceUpdateCallBack, &_ClientInstanceUpdate);
}
