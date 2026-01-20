#pragma once
#include <Windows.h>
#include <string_view>
#include <cstdint>
#include "../Client/Globals.h"

class Memory {
public:
    static uintptr_t getBase();
    static uintptr_t findSig(const std::string_view& sig);
    static void CreateHook(const char* name, uintptr_t address, void* func, void* OriginFunc);
};
