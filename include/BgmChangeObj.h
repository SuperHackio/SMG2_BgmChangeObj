#pragma once

#include "Game/NameObj/NameObj.h"
#include "Game/Map/StageSwitch.h"

class BgmChangeObj : public NameObj {
public:
	BgmChangeObj(const char*);

    virtual void init(const JMapInfoIter& rIter);
    virtual void movement();

    StageSwitchCtrl* mStageSwitch;
    bool mSwitchState;

    s32 mObjArg0;
    s32 mObjArg1;
    s32 mObjArg2;

    s32 mObjArg3;
    s32 mObjArg4;
    s32 mObjArg5;
};