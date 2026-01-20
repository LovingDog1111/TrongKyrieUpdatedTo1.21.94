#pragma once
#include "../../../SDK/ClientInstance.h"

class ClientInstanceUpdateHook {
private:
    static __int64 ClientInstanceUpdateCallBack(ClientInstance* _this, bool a2);

public:
    static void init();
};
