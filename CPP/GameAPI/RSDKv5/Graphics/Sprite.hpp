#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"
#include "../Game/Collision.hpp"

#define FRAMEHITBOX_COUNT (0x8)

namespace RSDK
{

struct SpriteSheet {
    uint16 id;

    SpriteSheet() : id(0xFFFF) {}

    RSDK_FORCE_INLINE void Init() { id = (uint16)-1; }

    RSDK_FORCE_INLINE void Load(const char *path, Scopes scope) { id = RSDKTable->LoadSpriteSheet(path, scope); }

    RSDK_FORCE_INLINE bool32 Loaded() { return id != (uint16)-1; }

    RSDK_FORCE_INLINE bool32 Matches(SpriteSheet &other) { return this->id == other.id; }
    RSDK_FORCE_INLINE bool32 Matches(SpriteSheet *other)
    {
        if (other)
            return this->id == other->id;
        else
            return this->id == (uint16)-1;
    }
};

typedef struct {
    int16 sprX;
    int16 sprY;
    int16 width;
    int16 height;
    int16 pivotX;
    int16 pivotY;
    uint16 duration;
    uint16 unicodeChar;
    uint8 sheetID;
} GameSpriteFrame;

struct SpriteFrame : public GameSpriteFrame {
    Hitbox hitboxes[FRAMEHITBOX_COUNT];
};

struct SpriteAnimation {
    uint16 aniFrames;

    SpriteAnimation() : aniFrames(0xFFFF) {}

    RSDK_FORCE_INLINE void Init() { aniFrames = (uint16)-1; }

    RSDK_FORCE_INLINE void Load(const char *path, Scopes scope) { aniFrames = RSDKTable->LoadSpriteAnimation(path, scope); }
    RSDK_FORCE_INLINE void Create(const char *filename, uint32 frameCount, uint32 listCount, Scopes scope)
    {
        aniFrames = RSDKTable->CreateSpriteAnimation(filename, frameCount, listCount, scope);
    }

    RSDK_FORCE_INLINE void Edit(uint16 listID, const char *name, int32 frameOffset, uint16 frameCount, int16 speed, uint8 loopIndex, uint8 rotationStyle)
    {
        RSDKTable->EditSpriteAnimation(aniFrames, listID, name, frameOffset, frameCount, speed, loopIndex, rotationStyle);
    }

    RSDK_FORCE_INLINE uint16 FindAnimation(const char *name) { return RSDKTable->FindSpriteAnimation(aniFrames, name); }

    RSDK_FORCE_INLINE bool32 Loaded() { return aniFrames != (uint16)-1; }

    RSDK_FORCE_INLINE SpriteFrame *GetFrame(int32 animID, int32 frameID) { return RSDKTable->GetFrame(aniFrames, animID, frameID); }

    RSDK_FORCE_INLINE bool32 Matches(SpriteAnimation &other) { return this->aniFrames == other.aniFrames; }
    RSDK_FORCE_INLINE bool32 Matches(SpriteAnimation *other)
    {
        if (other)
            return this->aniFrames == other->aniFrames;
        else
            return this->aniFrames == (uint16)-1;
    }
};

} // namespace RSDK