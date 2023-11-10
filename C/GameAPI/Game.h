#ifndef GAME_H
#define GAME_H

// =====================================================================
// Project: RSDKv5 Modding API (C)
// By: Rubberduckycooly & RMGRich
// =====================================================================

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

// -------------------------
// GAME TYPE
// -------------------------
#define GAMETYPE_NONE  (0)
#define GAMETYPE_MANIA (1)
#define GAMETYPE_S3    (2)

#ifndef GAME_TYPE
#define GAME_TYPE (GAMETYPE_MANIA)
#endif

#define GAME_IS_MANIA (GAME_TYPE == GAMETYPE_MANIA)
#define GAME_IS_S3    (GAME_TYPE == GAMETYPE_S3)

// -------------------------
// GAME VERSIONS
// -------------------------

#if GAME_IS_MANIA
#define VER_100 (0) // 1.00 (initial console release)
#define VER_103 (3) // 1.03 (PC release/console patch)
#define VER_105 (5) // 1.04/1.05 (mania plus release)
#define VER_106 (6) // 1.06 (steam denuvo removal update)
#define VER_107 (7) // 1.07 (EGS/Origin releases)

#if MANIA_PREPLUS

#if MANIA_FIRST_RELEASE

#undef GAME_VERSION
#define GAME_VERSION VER_100
#undef RETRO_REVISION
#define RETRO_REVISION (1)

#else
	
#undef GAME_VERSION
#define GAME_VERSION VER_103
#undef RETRO_REVISION
#define RETRO_REVISION (1)

#endif

#else

#ifndef GAME_VERSION
#define GAME_VERSION VER_106
#endif

#endif

#define MANIA_USE_PLUS (GAME_VERSION >= VER_105)
#define MANIA_USE_EGS  (GAME_VERSION == VER_107)

#elif GAME_IS_S3
#define VER_100 (0) // 1.0.0 (initial origins release)
#define VER_104 (1) // 1.0.4 (august 2022 patch)
#define VER_200 (2) // 2.0.0 (origins plus release)
#define VER_202 (3) // 2.0.1/2.0.2 (august/october 2023 patch)

#if ORIGINS_PREPLUS

#if ORIGINS_FIRST_RELEASE

#undef GAME_VERSION
#define GAME_VERSION VER_100

#else

#undef GAME_VERSION
#define GAME_VERSION VER_104

#endif

#else

#ifndef GAME_VERSION
#define GAME_VERSION VER_202
#endif

#endif

#define ORIGINS_USE_PLUS (GAME_VERSION >= VER_200)

#undef RETRO_REVISION
#define RETRO_REVISION (3)
#else
// None Gametype
#define VER_100 (0)

#ifndef GAME_VERSION
#define GAME_VERSION VER_100
#endif
#endif

// -------------------------
// GAME LOGIC
// -------------------------

#include "GameLink.h"
#ifndef GAME_NO_VARIABLES
#include "GameVariables.h"
#endif
#include "GameObjects.h"

#endif //! GAME_H
