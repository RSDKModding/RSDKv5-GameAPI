#define RSDK_IMPL
#include "Game.hpp"

// -------------------------
// ENGINE VARIABLES
// -------------------------

// -------------------------
// OBJECT REGISTRATION
// -------------------------

// -------------------------
// GAME VARIABLES
// -------------------------

// GlobalVariables::Constructor c;

// GlobalVariables *globals = nullptr;

void **registerGlobals    = nullptr;
int32 registerGlobalsSize = 0;

#if RETRO_REV0U
void (*registerGlobalsInitCB)(void *globalVars) = nullptr;

void RegisterGlobals(void **globals, int32 size, void (*initCB)(void *globals))
{
    registerGlobals       = globals;
    registerGlobalsSize   = size;
    registerGlobalsInitCB = initCB;
}
#else
void RegisterGlobals(void **globals, int32 size)
{
    registerGlobals     = globals;
    registerGlobalsSize = size;
}
#endif

#if RETRO_REV0U
/*
void GlobalVariables::Init(void *g)
{
    GlobalVariables *globals = (GlobalVariables *)g;

    memset(globals, 0, sizeof(GlobalVariables));

    // Global Variable Initialization Goes Here!
}
*/
#endif

// -------------------------
// LINK GAME/MOD LOGIC
// -------------------------

// Don't touch any of the stuff below, it should work automatically

extern "C" {

int32 RSDKRevision = RETRO_REVISION;

#if RETRO_REV02
void LinkGameLogicDLL(RSDK::EngineInfo *info)
{
    InitEngineInfo(info);
#else
void LinkGameLogicDLL(RSDK::EngineInfo info)
{
    InitEngineInfo(&info);
#endif

    using namespace RSDK;

    if (registerGlobals) {
#if RETRO_REV0U
        RSDKTable->RegisterGlobalVariables(registerGlobals, registerGlobalsSize, registerGlobalsInitCB);
#else
        RSDKTable->RegisterGlobalVariables(registerGlobals, registerGlobalsSize);
#endif
    }

    for (int32 r = 0; r < registerObjectListCount; ++r) {
        ObjectRegistration *registration = &registerObjectList[r];

        if (registration->name) {
#if RETRO_USE_MOD_LOADER
            if (registration->isModded) {
#if RETRO_REV0U
                modTable->RegisterObject(registration->staticVars, registration->modStaticVars, registration->name, registration->entityClassSize,
                                         registration->staticClassSize, registration->modStaticClassSize, registration->update,
                                         registration->lateUpdate, registration->staticUpdate, registration->draw, registration->create,
                                         registration->stageLoad, registration->editorLoad, registration->editorDraw, registration->serialize,
                                         registration->staticLoad, registration->inherit);
#else
                modTable->RegisterObject(registration->staticVars, registration->modStaticVars, registration->name, registration->entityClassSize,
                                         registration->staticClassSize, registration->modStaticClassSize, registration->update,
                                         registration->lateUpdate, registration->staticUpdate, registration->draw, registration->create,
                                         registration->stageLoad, registration->editorLoad, registration->editorDraw, registration->serialize,
                                         registration->inherit);
#endif

                continue;
            }
#endif

#if RETRO_REV0U
            RSDKTable->RegisterObject(registration->staticVars, registration->name, registration->entityClassSize, registration->staticClassSize,
                                      registration->update, registration->lateUpdate, registration->staticUpdate, registration->draw,
                                      registration->create, registration->stageLoad, registration->editorLoad, registration->editorDraw,
                                      registration->serialize, registration->staticLoad);
#else
            RSDKTable->RegisterObject(registration->staticVars, registration->name, registration->entityClassSize, registration->staticClassSize,
                                      registration->update, registration->lateUpdate, registration->staticUpdate, registration->draw,
                                      registration->create, registration->stageLoad, registration->editorLoad, registration->editorDraw,
                                      registration->serialize);
#endif
        }
    }

#if RETRO_REV02
    for (int32 r = 0; r < registerStaticListCount; ++r) {
        ObjectRegistration *registration = &registerStaticList[r];

        if (registration->name) {
            RSDKTable->RegisterStaticVariables((void **)registration->staticVars, registration->name, registration->staticClassSize);
        }
    }
#endif

#if GAME_CUSTOMLINKLOGIC
#if RETRO_REV02
    LinkGameLogic(info);
#else
    LinkGameLogic(&info);
#endif
#endif
}

#if RETRO_USE_MOD_LOADER
DLLExport RSDK::ModVersionInfo modInfo = { RETRO_REVISION, GAME_VERSION, RETRO_MOD_LOADER_VER };

bool32 LinkModLogic(RSDK::EngineInfo *info, const char *modID)
{
#if RETRO_REV02
    LinkGameLogicDLL(info);
#else
    LinkGameLogicDLL(*info);
#endif

    RSDK::Mod::modID = modID;

    return true;
}
#endif
};