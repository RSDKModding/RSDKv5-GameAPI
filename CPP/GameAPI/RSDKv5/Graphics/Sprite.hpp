#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

namespace RSDK
{

struct SpriteSheet {
    uint16 id;

    inline void Init() { id = (uint16)-1; }

    inline void Load(const char *path, Scopes scope) { id = RSDKTable->LoadSpriteSheet(path, scope); }

    inline bool32 Loaded() { return id != (uint16)-1; }

    inline bool32 Matches(SpriteSheet &other) { return this->id == other.id; }
    inline bool32 Matches(SpriteSheet *other)
    {
        if (other)
            return this->id == other->id;
        else
            return this->id == (uint16)-1;
    }
};

struct SpriteFrame {
    int16 sprX;
    int16 sprY;
    int16 width;
    int16 height;
    int16 pivotX;
    int16 pivotY;
    uint16 duration;
    uint16 unicodeChar;
    uint8 sheetID;
};

struct SpriteAnimation {
    uint16 aniFrames;

    inline void Init() { aniFrames = -1; }

    inline void Load(const char *path, Scopes scope) { aniFrames = RSDKTable->LoadSpriteAnimation(path, scope); }
    inline void Create(const char *filename, uint32 frameCount, uint32 listCount, Scopes scope)
    {
        aniFrames = RSDKTable->CreateSpriteAnimation(filename, frameCount, listCount, scope);
    }

    inline void Edit(uint16 listID, const char *name, int32 frameOffset, uint16 frameCount, int16 speed, uint8 loopIndex, uint8 rotationStyle)
    {
        RSDKTable->EditSpriteAnimation(aniFrames, listID, name, frameOffset, frameCount, speed, loopIndex, rotationStyle);
    }

    inline uint16 FindAnimation(const char *name) { return RSDKTable->FindSpriteAnimation(aniFrames, name); }

    inline bool32 Loaded() { return aniFrames != (uint16)-1; }

    inline SpriteFrame *GetFrame(int32 animID, int32 frameID) { return RSDKTable->GetFrame(aniFrames, animID, frameID); }

    inline bool32 Matches(SpriteAnimation &other) { return this->aniFrames == other.aniFrames; }
    inline bool32 Matches(SpriteAnimation *other)
    {
        if (other)
            return this->aniFrames == other->aniFrames;
        else
            return this->aniFrames == (uint16)-1;
    }
};

} // namespace RSDK