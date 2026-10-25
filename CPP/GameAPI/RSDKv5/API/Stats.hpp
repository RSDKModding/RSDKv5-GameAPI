#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

namespace GameAPI::RSDK
{
#if RETRO_REV02
struct StatInfo {
    uint8 statID;
    const char *name;
    void *data[64];
};

namespace API
{
namespace Stats
{

RSDK_FORCE_INLINE void TryTrackStat(StatInfo *stat) { APITable->TryTrackStat(stat); }
RSDK_FORCE_INLINE bool32 GetEnabled() { return APITable->GetStatsEnabled(); }
RSDK_FORCE_INLINE void SetEnabled(bool32 enabled) { APITable->SetStatsEnabled(enabled); }

} // namespace Stats
} // namespace API
#endif
} // namespace GameAPI::RSDK
