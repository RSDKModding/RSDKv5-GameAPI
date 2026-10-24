#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

#if RETRO_REV02
namespace RSDK
{

struct AchievementID {
    uint8 idPS4;     // achievement ID (PS4)
    int32 idUnknown; // achievement ID (unknown platform)
    const char *id;  // achievement ID (as a string, used for most platforms)
};

namespace API
{
namespace Achievements
{

RSDK_FORCE_INLINE void TryUnlockAchievement(AchievementID *id) { APITable->TryUnlockAchievement(id); }
RSDK_FORCE_INLINE bool32 GetEnabled() { return APITable->GetAchievementsEnabled(); }
RSDK_FORCE_INLINE void SetEnabled(bool32 enabled) { APITable->SetAchievementsEnabled(enabled); }
#if RETRO_USE_EGS
RSDK_FORCE_INLINE bool32 CheckEnabled() { return APITable->CheckAchievementsEnabled(); }
RSDK_FORCE_INLINE void SetNames(String **names, int32 count) { APITable->SetAchievementNames(names, count); }
#endif

} // namespace Achievements

} // namespace API
} // namespace RSDK
#endif
