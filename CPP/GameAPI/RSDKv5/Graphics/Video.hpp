#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

namespace RSDK
{

namespace Video
{

RSDK_FORCE_INLINE bool32 LoadVideo(const char *filename, double startDelay, bool32 (*skipCallback)())
{
    return RSDKTable->LoadVideo(filename, startDelay, skipCallback);
}
RSDK_FORCE_INLINE bool32 LoadImage(const char *filename, double displayLength, double speed, bool32 (*skipCallback)())
{
    return RSDKTable->LoadImage(filename, displayLength, speed, skipCallback);
}

} // namespace Video

} // namespace RSDK