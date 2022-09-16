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
#define VER_105 (5) // 1.04/1.05
#define VER_106 (6) // 1.06 (steam denuvo removal update)
#define VER_107 (7) // 1.07 (EGS/Origin releases)

#ifdef MANIA_PREPLUS

#ifdef MANIA_FIRST_RELEASE
#define GAME_VERSION VER_100
#else
#ifndef GAME_VERSION
#define GAME_VERSION VER_103
#endif
#endif

#undef RETRO_REV02
#define RETRO_REV02 (0)
#else
#ifndef GAME_VERSION
#define GAME_VERSION VER_106
#endif
#endif

#define MANIA_USE_PLUS (GAME_VERSION >= VER_105)
#define MANIA_USE_EGS  (GAME_VERSION == VER_107)

#elif GAME_IS_S3
#define VER_100 (0) // 1.00 (initial origins release)
#define VER_104 (4) // 1.04 (origins' first patch)

#ifndef GAME_VERSION
#define GAME_VERSION VER_104
#endif
#else
#define VER_100 (0)

#ifndef GAME_VERSION
#define GAME_VERSION VER_100
#endif
#endif

// -------------------------
// GAME LOGIC
// -------------------------

#include "RSDKv5/RSDKv5.hpp"
#include "GameVariables.hpp"
#include "GameObjects.hpp"

#endif //! GAME_H
