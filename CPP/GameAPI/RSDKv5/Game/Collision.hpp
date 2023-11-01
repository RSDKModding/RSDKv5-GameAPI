#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

#define TILE_SIZE (16)

namespace RSDK
{

enum CollisionModes { CMODE_FLOOR, CMODE_LWALL, CMODE_ROOF, CMODE_RWALL };

enum CollisionSides { C_NONE, C_TOP, C_LEFT, C_RIGHT, C_BOTTOM };

struct Hitbox {
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
    static inline void SetPathGripSensors(CollisionSensor *sensors) { RSDKTable->SetPathGripSensors(sensors); };

    inline void FindFloorPosition() { RSDKTable->FindFloorPosition(this); }
    inline void FindLWallPosition() { RSDKTable->FindLWallPosition(this); }
    inline void FindRoofPosition() { RSDKTable->FindRoofPosition(this); }
    inline void FindRWallPosition() { RSDKTable->FindRWallPosition(this); }
    inline void FloorCollision() { RSDKTable->FloorCollision(this); }
    inline void LWallCollision() { RSDKTable->LWallCollision(this); }
    inline void RoofCollision() { RSDKTable->RoofCollision(this); }
    inline void RWallCollision() { RSDKTable->RWallCollision(this); }
#elif RETRO_USE_MOD_LOADER && RETRO_MOD_LOADER_VER >= 2
    // expects an array of 5 sensors
    static inline void SetPathGripSensors(CollisionSensor *sensors) { modTable->SetPathGripSensors(sensors); };

    inline void FindFloorPosition() { modTable->FindFloorPosition(this); }
    inline void FindLWallPosition() { modTable->FindLWallPosition(this); }
    inline void FindRoofPosition() { modTable->FindRoofPosition(this); }
    inline void FindRWallPosition() { modTable->FindRWallPosition(this); }
    inline void FloorCollision() { modTable->FloorCollision(this); }
    inline void LWallCollision() { modTable->LWallCollision(this); }
    inline void RoofCollision() { modTable->RoofCollision(this); }
    inline void RWallCollision() { modTable->RWallCollision(this); }
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
};
#endif

namespace Collision
{
#if RETRO_REV0U
inline void SetupCollisionConfig(int32 minDistance, uint8 lowTolerance, uint8 highTolerance, uint8 floorAngleTolerance, uint8 wallAngleTolerance,
                                 uint8 roofAngleTolerance)
{
    RSDKTable->SetupCollisionConfig(minDistance, lowTolerance, highTolerance, floorAngleTolerance, wallAngleTolerance, roofAngleTolerance);
}
#endif

#if RETRO_REV0U
inline void CopyCollisionMask(uint16 dst, uint16 src, uint8 cPlane, uint8 cMode) { RSDKTable->CopyCollisionMask(dst, src, cPlane, cMode); }
inline void GetCollisionInfo(CollisionMask **masks, TileInfo **tileInfo) { RSDKTable->GetCollisionInfo(masks, tileInfo); }
#elif RETRO_USE_MOD_LOADER && RETRO_MOD_LOADER_VER >= 2
inline void CopyCollisionMask(uint16 dst, uint16 src, uint8 cPlane, uint8 cMode) { modTable->CopyCollisionMask(dst, src, cPlane, cMode); }
inline void GetCollisionInfo(CollisionMask **masks, TileInfo **tileInfo) { modTable->GetCollisionInfo(masks, tileInfo); }
#endif

} // namespace Collision

} // namespace RSDK
