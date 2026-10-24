#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

#define TILE_SIZE   (16)
#define TILE_COUNT  (0x400)
#define CPATH_COUNT (2)

namespace RSDK
{

enum CollisionModes { CMODE_FLOOR, CMODE_LWALL, CMODE_ROOF, CMODE_RWALL };

enum CollisionSides { C_NONE, C_TOP, C_LEFT, C_RIGHT, C_BOTTOM };

struct Hitbox {
    RSDK_FORCE_INLINE Hitbox() : left(0), top(0), right(0), bottom(0) {};
    RSDK_FORCE_INLINE Hitbox(int16 Left, int16 Top, int16 Right, int16 Bottom) : left(Left), top(Top), right(Right), bottom(Bottom) {};

    int16 left;
    int16 top;
    int16 right;
    int16 bottom;
};

#if RETRO_REV0U || RETRO_USE_MOD_LOADER && RETRO_MOD_LOADER_VER >= 2
struct CollisionSensor {
    Vector2 position;
    bool32 collided;
    uint8 angle;

#if RETRO_REV0U
    // expects an array of 5 sensors
    static RSDK_FORCE_INLINE void SetPathGripSensors(CollisionSensor *sensors) { RSDKTable->SetPathGripSensors(sensors); };

    RSDK_FORCE_INLINE void FindFloorPosition() { RSDKTable->FindFloorPosition(this); }
    RSDK_FORCE_INLINE void FindLWallPosition() { RSDKTable->FindLWallPosition(this); }
    RSDK_FORCE_INLINE void FindRoofPosition() { RSDKTable->FindRoofPosition(this); }
    RSDK_FORCE_INLINE void FindRWallPosition() { RSDKTable->FindRWallPosition(this); }
    RSDK_FORCE_INLINE void FloorCollision() { RSDKTable->FloorCollision(this); }
    RSDK_FORCE_INLINE void LWallCollision() { RSDKTable->LWallCollision(this); }
    RSDK_FORCE_INLINE void RoofCollision() { RSDKTable->RoofCollision(this); }
    RSDK_FORCE_INLINE void RWallCollision() { RSDKTable->RWallCollision(this); }
#elif RETRO_USE_MOD_LOADER && RETRO_MOD_LOADER_VER >= 2
    // expects an array of 5 sensors
    static RSDK_FORCE_INLINE void SetPathGripSensors(CollisionSensor *sensors) { modTable->SetPathGripSensors(sensors); };

    RSDK_FORCE_INLINE void FindFloorPosition() { modTable->FindFloorPosition(this); }
    RSDK_FORCE_INLINE void FindLWallPosition() { modTable->FindLWallPosition(this); }
    RSDK_FORCE_INLINE void FindRoofPosition() { modTable->FindRoofPosition(this); }
    RSDK_FORCE_INLINE void FindRWallPosition() { modTable->FindRWallPosition(this); }
    RSDK_FORCE_INLINE void FloorCollision() { modTable->FloorCollision(this); }
    RSDK_FORCE_INLINE void LWallCollision() { modTable->LWallCollision(this); }
    RSDK_FORCE_INLINE void RoofCollision() { modTable->RoofCollision(this); }
    RSDK_FORCE_INLINE void RWallCollision() { modTable->RWallCollision(this); }
#endif
};

struct CollisionMask {
    uint8 floorMasks[TILE_SIZE];
    uint8 lWallMasks[TILE_SIZE];
    uint8 rWallMasks[TILE_SIZE];
    uint8 roofMasks[TILE_SIZE];
};

struct TileInfo {
    uint8 floorAngle;
    uint8 lWallAngle;
    uint8 rWallAngle;
    uint8 roofAngle;
    uint8 flag;
    uint8 unused1;
    uint8 unused2;
    uint8 unused3;
};
#endif

namespace Collision
{
#if RETRO_REV0U
RSDK_FORCE_INLINE void SetupCollisionConfig(uint8 minDistance, uint8 lowTolerance, uint8 highTolerance, uint8 floorAngleTolerance, uint8 wallAngleTolerance,
                                 uint8 roofAngleTolerance)
{
    RSDKTable->SetupCollisionConfig(minDistance, lowTolerance, highTolerance, floorAngleTolerance, wallAngleTolerance, roofAngleTolerance);
}
#endif

#if RETRO_REV0U
RSDK_FORCE_INLINE void CopyCollisionMask(uint16 dst, uint16 src, uint8 cPlane, uint8 cMode) { RSDKTable->CopyCollisionMask(dst, src, cPlane, cMode); }
RSDK_FORCE_INLINE void GetCollisionInfo(CollisionMask **masks, TileInfo **tileInfo) { RSDKTable->GetCollisionInfo(masks, tileInfo); }
#elif RETRO_USE_MOD_LOADER && RETRO_MOD_LOADER_VER >= 2
RSDK_FORCE_INLINE void CopyCollisionMask(uint16 dst, uint16 src, uint8 cPlane, uint8 cMode) { modTable->CopyCollisionMask(dst, src, cPlane, cMode); }
RSDK_FORCE_INLINE void GetCollisionInfo(CollisionMask **masks, TileInfo **tileInfo) { modTable->GetCollisionInfo(masks, tileInfo); }
#endif

} // namespace Collision

} // namespace RSDK
