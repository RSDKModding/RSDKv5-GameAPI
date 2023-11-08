#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

namespace RSDK
{

#if RETRO_REV02

struct AchievementID {
    uint8 idPS4;     // achievement ID (PS4)
    int32 idUnknown; // achievement ID (unknown platform)
    const char *id;  // achievement ID (as a string, used for most platforms)
};

namespace API
{
namespace Achievements
{

inline void TryUnlockAchievement(AchievementID *id) { APITable->TryUnlockAchievement(id); }
inline bool32 GetEnabled() { return APITable->GetAchievementsEnabled(); }
inline void SetEnabled(bool32 enabled) { APITable->SetAchievementsEnabled(enabled); }
#if RETRO_USE_EGS
inline bool32 CheckEnabled() { return APITable->CheckAchievementsEnabled(); }
inline void SetNames(String **names, int32 count) { APITable->SetAchievementNames(names, count); }
#endif

} // namespace Achievements

#endif

} // namespace API
} // namespace RSDK
