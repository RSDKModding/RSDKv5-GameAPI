#pragma once

namespace RSDK
{

namespace Video
{

inline void LoadVideo(const char *filename, double startDelay, bool32 (*skipCallback)()) { RSDKTable->LoadVideo(filename, startDelay, skipCallback); }
inline bool32 LoadImage(const char *filename, double displayLength, double speed, bool32 (*skipCallback)())
{
    return RSDKTable->LoadImage(filename, displayLength, speed, skipCallback);
}

} // namespace Video

} // namespace RSDK