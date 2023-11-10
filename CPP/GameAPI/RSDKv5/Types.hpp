#pragma once

typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed int int32;
typedef unsigned int uint32;
typedef signed long long int64;
typedef unsigned long long uint64;

typedef uint32 bool32;
typedef uint32 color;

// -------------------------
// ENGINE VERSIONS
// -------------------------

#ifndef RETRO_REVISION
#define RETRO_REVISION (3)
#endif

#define RETRO_REV01 (RETRO_REVISION == 1)

// RSDKv5 was revised & updated for plus onwards
// this is basically the same functionality as "MANIA_USE_PLUS"
// but I split this one to be more specific about engine changes vs game changes
#define RETRO_REV02 (RETRO_REVISION >= 2)

// RSDKv5 was revised & updated to v5U for sonic origins
// enabling this will add the RSDKv5U funcs and allow this to run properly on that engine ver
#define RETRO_REV0U (RETRO_REVISION >= 3)

#ifndef RETRO_USE_EGS
#define RETRO_USE_EGS (RETRO_REV02 && 0)
#endif

// Controls whether EditorLoad & EditorDraw should be included in the final product or not
// This is a copy of what the original game likely had, as the original game does not include EditorLoad or EditorDraw funcs for any objects
#ifndef GAME_INCLUDE_EDITOR
#ifdef RETRO_INCLUDE_EDITOR
#define GAME_INCLUDE_EDITOR RETRO_INCLUDE_EDITOR
#else
#define GAME_INCLUDE_EDITOR (1)
#endif
#endif

#ifndef RETRO_USE_MOD_LOADER
#define RETRO_USE_MOD_LOADER (1)
#endif

#ifndef RETRO_MOD_LOADER_VER
#define RETRO_MOD_LOADER_VER (2)
#endif

// used to manage standalone (RSDKv5.exe & Game.dll) and combined (Game.exe) modes
#ifndef RETRO_STANDALONE
#define RETRO_STANDALONE (1)
#endif
