#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

#define CHANNEL_COUNT (0x10)

namespace RSDK
{
struct Channel {

    Channel() : id(0) {}
    Channel(uint8 channelID) : id(channelID) {}

    inline void SetAttributes(float volume, float pan, float speed) { RSDKTable->SetChannelAttributes(id, volume, pan, speed); }

    inline void Stop() { RSDKTable->StopChannel(id); }
    inline void Pause() { RSDKTable->PauseChannel(id); }
    inline void Resume() { RSDKTable->ResumeChannel(id); }
    inline bool32 IsActive() { return RSDKTable->ChannelActive(id); }

    inline uint32 AudioPos() { return RSDKTable->GetChannelPos(id); }

    inline int32 PlayStream(const char *filename, uint32 startPos, uint32 loopPoint, bool32 loadASync)
    {
        return RSDKTable->PlayStream(filename, id, startPos, loopPoint, loadASync);
    }

    uint8 id;
};

extern RSDK::Channel channels[CHANNEL_COUNT];

struct SoundFX {
    uint16 id;

    inline void Init() { id = (uint16)-1; }

    inline void Get(const char *path) { id = RSDKTable->GetSfx(path); }

    inline bool32 Loaded() { return id != (uint16)-1; }

    inline int32 Play(int32 loopPoint = 0, int32 priority = 0xFF) { return RSDKTable->PlaySfx(id, loopPoint, priority); }

    inline void Stop() { RSDKTable->StopSfx(id); }

    inline bool32 IsPlaying() { return RSDKTable->IsSfxPlaying(id); }

#if RETRO_REV0U
    static inline void StopAll() { RSDKTable->StopAllSfx(); }
#endif

    inline bool32 Matches(SoundFX &other) { return this->id == other.id; }
    inline bool32 Matches(SoundFX *other)
    {
        if (other)
            return this->id == other->id;
        else
            return this->id == (uint16)-1;
    }
};

} // namespace RSDK