#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

namespace RSDK
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

inline void TryTrackStat(StatInfo *stat) { APITable->TryTrackStat(stat); }
inline bool32 GetEnabled() { return APITable->GetStatsEnabled(); }
inline void SetEnabled(bool32 enabled) { APITable->SetStatsEnabled(enabled); }

} // namespace Stats
} // namespace API
#endif
} // namespace RSDK
