#include "Memory.h"
#include "../Utils/Utils.h"
#include <MinHook.h>

static uintptr_t cachedBase = 0;

uintptr_t Memory::getBase() {
    if (!cachedBase)
        cachedBase = (uintptr_t)GetModuleHandleA("Minecraft.Windows.exe");
    return cachedBase;
}

uintptr_t Memory::findSig(const std::string_view& sig) {
    return Utils().findSignature(sig);
}

void Memory::CreateHook(const char* name, uintptr_t address, void* func, void* OriginFunc) {
    if (!address) {
        Utils::DebugF("%s Address not work!", name);
        return;
    }
    if (MH_CreateHook((void*)address, func, reinterpret_cast<LPVOID*>(OriginFunc)) != MH_OK) {
        Utils::DebugF("%s Failed to create hook!", name);
        return;
    }
    if (MH_EnableHook((void*)address) != MH_OK) {
        Utils::DebugF("%s Failed to enable hook!", name);
    }
    Utils::DebugF("Successfully hooked %s!", name);
}
