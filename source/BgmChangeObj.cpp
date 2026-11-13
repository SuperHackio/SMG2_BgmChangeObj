#include "BgmChangeObj.h"

#include "Game/AudioLib/AudWrap.h"
#include "Game/Util/ActorSwitchUtil.h"
#include "Game/Util/BgmUtil.h"
#include "Game/Util/DemoUtil.h"
#include "Game/Util/ObjUtil.h"
#include "Game/Util/PlayerUtil.h"
#include "Game/Util/JMapUtil.h"
#include "Game/Util/SceneUtil.h"
#include "Game/Util/SequenceUtil.h"

#include "Game/GameAudio/AudTalkSoundData.h"

extern "C" {
	JAISoundID __kAutoMap_8008A150(const char*, s32, s32);
}

namespace {
	void doAudioChange(s32 mode, s32 a, s32 b) {
		s32 FadeTime;
		s32 ColumnID;
		switch (mode)
		{
		case 1: // Fade-out and Change Song
			FadeTime = a;
			ColumnID = b;

			if (FadeTime < 0)
				FadeTime = 90;

			if (b >= 0) {
				JAISoundID id = __kAutoMap_8008A150(MR::getCurrentStageName(), MR::getCurrentScenarioNo(), b);
				if (!(id.mID == -1)) { // Should be isAnnon or whatever
					register AudBgmMgr* mgr = AudWrap::getBgmMgr();
					register u32 v;
					__asm {
						lwz v, 0x10(mgr)
					}
					if (v == id.mID) {
						if (MR::isPlayingStageBgm())
							break;
					}
					AudWrap::setNextIdStageBgm(id.mID);
				}
			}
			MR::stopStageBGM(FadeTime);
			break;
		case 2: // Change State
			ColumnID = a;
			FadeTime = b;
			// Not implemented at this time...
			break;
		default: // Do nothing lol
			break;
		}
	}
}

BgmChangeObj::BgmChangeObj(const char* pName) : NameObj(pName), mStageSwitch(nullptr), mSwitchState(false) {
	mObjArg0 = -1;
	mObjArg1 = -1;
	mObjArg2 = -1;

	mObjArg3 = -1;
	mObjArg4 = -1;
	mObjArg5 = -1;
}

void BgmChangeObj::init(const JMapInfoIter& rIter) {
	MR::connectToSceneMapObjMovement(this);
	MR::registerDemoSimpleCastAll(this);

	MR::getJMapInfoArg0NoInit(rIter, &mObjArg0);
	MR::getJMapInfoArg1NoInit(rIter, &mObjArg1);
	MR::getJMapInfoArg2NoInit(rIter, &mObjArg2);

	MR::getJMapInfoArg3NoInit(rIter, &mObjArg3);
	MR::getJMapInfoArg4NoInit(rIter, &mObjArg4);
	MR::getJMapInfoArg5NoInit(rIter, &mObjArg5);

	mStageSwitch = MR::createStageSwitchCtrl(this, rIter);
}

void BgmChangeObj::movement() {
	if (MR::isStageStateScenarioOpeningCamera())
		return;

	if (MR::isPowerStarGetDemoActive()) {
		return;
	}

	if (MR::isPlayingStageBgmID(0x02000000)) { // STM_STAR_CHANCE
		return;
	}

	if (MR::isPlayingStageBgmID(0x02000001)) { // STM_STAR_CHANCE_2
		return;
	}

	if (MR::isPlayerDead()) {
		return;
	}

	if (mStageSwitch->isOnSwitchA()) {
		if (!mSwitchState) {
			mSwitchState = true;
			doAudioChange(mObjArg0, mObjArg1, mObjArg2);
		}
	}
	else {
		if (mSwitchState) {
			mSwitchState = false;
			doAudioChange(mObjArg3, mObjArg4, mObjArg5);
		}
	}
}