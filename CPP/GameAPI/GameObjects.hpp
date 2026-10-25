#ifndef GAMEOBJECTS_HPP
#define GAMEOBJECTS_HPP

#ifdef _MSC_VER
#define DLLExport __declspec(dllexport)
#else
#define DLLExport
#endif

// -------------------------
// OBJECTS
// -------------------------

extern "C" {
#if RETRO_REV02
DLLExport void LinkGameLogicDLL(RSDK::EngineInfo *info);
#else
DLLExport void LinkGameLogicDLL(RSDK::EngineInfo info);
#endif

// custom-added extra little bit of info to let the engine know what RSDK version it is
DLLExport extern int32 RSDKRevision;

#if RETRO_USE_MOD_LOADER
DLLExport extern RSDK::ModVersionInfo modInfo;

DLLExport bool32 LinkModLogic(RSDK::EngineInfo *info, const char *id);
#endif
}

#endif //! GAMEOBJECTS_HPP
