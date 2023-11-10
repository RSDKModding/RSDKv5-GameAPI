#ifndef GAME_H
#define GAME_H

// =====================================================================
// Project: RSDKv5 Modding API (C++)
// By: Rubberduckycooly & RMGRich
// =====================================================================

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

#include "RSDKv5/RSDKv5.hpp"
#ifndef GAME_NO_VARIABLES
#include "GameVariables.hpp"
#endif
#include "GameObjects.hpp"

#endif //! GAME_H
