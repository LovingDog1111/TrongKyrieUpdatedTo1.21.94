#include "HookManager.h"
#include "../Memory.h"
#include <MinHook.h>

#include "ClientInstanceUpdateHook/ClientInstanceUpdate.h"
#include "KeyMapHook/KeyMapHook.h"
#include "KeyMouseHook/KeyMouseHook.h"
#include "GetGammaHook/GetGammaHook.h"
#include "MobGetCurrentSwingDurationHook/MobGetCurrentSwingDurationHook.h"
#include "GameModeGetPickRangeHook/GameModeGetPickRangeHook.h"
#include "SwapChainHook/SwapChainHook.h"

void HookManager::initAll() {
    ClientInstanceUpdateHook::init();
    KeyMapHook::init();
    KeyMouseHook::init();
    MobGetCurrentSwingDurationHook::init();

    uintptr_t gameModeAddr = Memory::findSig("48 8D 05 ? ? ? ? ? ? ? 48 89 51 ? 48 C7 41");
    if (gameModeAddr) {
        int offset = *reinterpret_cast<int*>(gameModeAddr + 3);
        uintptr_t** gameModeVtable = reinterpret_cast<uintptr_t**>(gameModeAddr + offset + 7);
        if (gameModeVtable) {
            GameModeGetPickRangeHook::init(gameModeVtable);
        }
    }

    uintptr_t gammaHookAddr = Memory::findSig("48 8D 05 ? ? ? ? ? ? ? 48 8B 89 ? ? ? ? BF");
    if (gammaHookAddr) {
        int offset = *reinterpret_cast<int*>(gammaHookAddr + 3);
        uintptr_t** gammaHookVtable = reinterpret_cast<uintptr_t**>(gammaHookAddr + offset + 7);
        if (gammaHookVtable) {
            GetGammaHook::init(gammaHookVtable);
        }
    }

    SwapChainHook::init();
}

void HookManager::RestoreAll() {
    SwapChainHook::unject();
    MH_DisableHook(MH_ALL_HOOKS);
    Sleep(10);
    MH_RemoveHook(MH_ALL_HOOKS);
    Sleep(10);
    MH_Uninitialize();
}
