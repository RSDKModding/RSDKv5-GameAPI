#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#ifdef _MSC_VER
#define DLLExport __declspec(dllexport)
#else
#define DLLExport
#endif

// -------------------------
// OBJECTS
// -------------------------

extern "C" {
DLLExport void LinkGameLogicDLL(RSDK::EngineInfo *info);

// custom-added extra little bit of info to let the engine know what RSDK version it is
DLLExport extern int32 RSDKRevision;

#if RETRO_USE_MOD_LOADER
DLLExport extern RSDK::ModVersionInfo modInfo;

bool32 InitModLogic(RSDK::EngineInfo *info, const char *modID);
#endif
}

#endif //! GAMEOBJECTS_H
