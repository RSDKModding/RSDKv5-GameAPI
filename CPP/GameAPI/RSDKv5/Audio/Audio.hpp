#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

#define CHANNEL_COUNT (0x10)

namespace GameAPI::RSDK
{
struct Channel {

    Channel() : id(0) {}
    Channel(int32 channelID) : id(channelID) {}

    RSDK_FORCE_INLINE void SetAttributes(float volume, float pan, float speed) { RSDKTable->SetChannelAttributes(id, volume, pan, speed); }

#if RETRO_USE_MOD_LOADER && RETRO_MOD_LOADER_VER >= 3
    RSDK_FORCE_INLINE void GetAttributes(float *volume, float *pan, float *speed) { modTable->GetChannelAttributes(id, volume, pan, speed); }
#endif

    RSDK_FORCE_INLINE void Stop() { RSDKTable->StopChannel(id); }
    RSDK_FORCE_INLINE void Pause() { RSDKTable->PauseChannel(id); }
    RSDK_FORCE_INLINE void Resume() { RSDKTable->ResumeChannel(id); }
    RSDK_FORCE_INLINE bool32 IsActive() { return RSDKTable->ChannelActive(id); }

    RSDK_FORCE_INLINE uint32 AudioPos() { return RSDKTable->GetChannelPos(id); }

    RSDK_FORCE_INLINE int32 PlayStream(const char *filename, uint32 startPos, uint32 loopPoint, bool32 loadASync)
    {
        return RSDKTable->PlayStream(filename, id, startPos, loopPoint, loadASync);
    }

    int32 id;
};

extern RSDK::Channel channels[CHANNEL_COUNT];

struct SoundFX {
    uint16 id;

    SoundFX() : id(0xFFFF) {}

    RSDK_FORCE_INLINE void Init() { id = (uint16)-1; }

    RSDK_FORCE_INLINE void Get(const char *path) { id = RSDKTable->GetSfx(path); }

    RSDK_FORCE_INLINE bool32 Loaded() { return id != (uint16)-1; }

    RSDK_FORCE_INLINE int32 Play(int32 loopPoint = 0, int32 priority = 0xFF) { return RSDKTable->PlaySfx(id, loopPoint, priority); }

    RSDK_FORCE_INLINE void Stop() { RSDKTable->StopSfx(id); }

    RSDK_FORCE_INLINE bool32 IsPlaying() { return RSDKTable->IsSfxPlaying(id); }

#if RETRO_REV0U
    static RSDK_FORCE_INLINE void StopAll() { RSDKTable->StopAllSfx(); }
#endif

    RSDK_FORCE_INLINE bool32 Matches(SoundFX &other) { return this->id == other.id; }
    RSDK_FORCE_INLINE bool32 Matches(SoundFX *other)
    {
        if (other)
            return this->id == other->id;
        else
            return this->id == (uint16)-1;
    }
};

} // namespace GameAPI::RSDK