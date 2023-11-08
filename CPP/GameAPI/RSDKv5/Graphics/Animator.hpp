#pragma once

#include "../Types.hpp"
#include "Sprite.hpp"
#include "Mesh.hpp"

namespace RSDK
{
struct Animator {

    enum RotationSyles { RotateNone, RotateFull, Rotate45Deg, Rotate90Deg, Rotate180Deg, RotateStaticFrames };

    SpriteFrame *frames;
    int32 frameID;
    int16 animationID;
    int16 prevAnimationID;
    int16 speed;
    int16 timer;
    int16 frameDuration;
    int16 frameCount;
    uint8 loopIndex;
    uint8 rotationStyle;

#if RETRO_MOD_LOADER_VER >= 2
    void inline SetAnimation(SpriteAnimation &spriteAni, uint16 listID, bool32 forceApply, int32 frameID)
#else
    void inline SetAnimation(SpriteAnimation &spriteAni, uint16 listID, bool32 forceApply, int16 frameID)
#endif
    {
        RSDKTable->SetSpriteAnimation(spriteAni.aniFrames, listID, this, forceApply, frameID);
    }

#if RETRO_MOD_LOADER_VER >= 2
    void inline SetAnimation(SpriteAnimation *spriteAni, uint16 listID, bool32 forceApply, int32 frameID)
#else
    void inline SetAnimation(SpriteAnimation *spriteAni, uint16 listID, bool32 forceApply, int16 frameID)
#endif
    {
        RSDKTable->SetSpriteAnimation(spriteAni ? spriteAni->aniFrames : -1, listID, this, forceApply, frameID);
    }

    void inline SetAnimation(Graphics::Mesh &mesh, int16 speed, uint8 loopIndex, bool32 forceApply, int16 frameID)
    {
        RSDKTable->SetModelAnimation(mesh.id, this, speed, loopIndex, forceApply, frameID);
    }

    void inline SetAnimation(Graphics::Mesh *mesh, int16 speed, uint8 loopIndex, bool32 forceApply, int16 frameID)
    {
        RSDKTable->SetModelAnimation(mesh ? mesh->id : -1, this, speed, loopIndex, forceApply, frameID);
    }

    inline void Process() { RSDKTable->ProcessAnimation(this); }

    inline int32 GetFrameID() { return RSDKTable->GetFrameID(this); }
    inline Hitbox *GetHitbox(uint8 id) { return RSDKTable->GetHitbox(this, id); }
    inline SpriteFrame *GetFrame(RSDK::SpriteAnimation aniFrames) { return aniFrames.GetFrame(animationID, frameID); }

    inline void DrawSprite(Vector2 *position, bool32 screenRelative) { RSDKTable->DrawSprite(this, position, screenRelative); }
    inline void DrawString(Vector2 *position, String *string, int32 endFrame, int32 textLength, int32 align, int32 spacing, Vector2 *charOffsets,
                           bool32 screenRelative)
    {
        RSDKTable->DrawText(this, position, string, endFrame, textLength, align, spacing, NULL, charOffsets, screenRelative);
    }

#if RETRO_REV0U
    inline void DrawAniTiles(uint16 tileID) { RSDKTable->DrawDynamicAniTiles(this, tileID); }
#elif RETRO_USE_MOD_LOADER && RETRO_MOD_LOADER_VER >= 2
    inline void DrawAniTiles(uint16 tileID) { modTable->DrawDynamicAniTiles(this, tileID); }
#endif
};
} // namespace RSDK
