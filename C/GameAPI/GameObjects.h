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

// #include "All.h"

#if RETRO_REV02
DLLExport void LinkGameLogicDLL(EngineInfo *info);
#else
DLLExport void LinkGameLogicDLL(EngineInfo info);
#endif

#endif //! GAMEOBJECTS_H
