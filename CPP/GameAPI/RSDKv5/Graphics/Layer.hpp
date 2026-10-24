#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"
#include "../Graphics/Graphics.hpp"

namespace RSDK
{

enum LayerTypes {
    LAYER_HSCROLL,
    LAYER_VSCROLL,
    LAYER_ROTOZOOM,
    LAYER_BASIC,
};

struct ScanlineInfo {
    Vector2 position;
    Vector2 deform;
};

struct ScrollInfo {
    int32 tilePos;
    int32 parallaxFactor;
    int32 scrollSpeed;
    int32 scrollPos;
    uint8 deform;
    uint8 unknown;
};

struct Tile {
    uint16 id;

    Tile() { id = 0xFFFF; }
    Tile(uint16 id) { this->id = id; }

    RSDK_FORCE_INLINE uint16 Index() { return id & 0x3FF; }
    RSDK_FORCE_INLINE uint8 Direction() { return (id >> 10) & 3; }
    RSDK_FORCE_INLINE uint8 SolidA() { return (id >> 12) & 3; }
    RSDK_FORCE_INLINE uint8 SolidB() { return (id >> 14) & 3; }

    RSDK_FORCE_INLINE void SetIndex(uint16 index)
    {
        id &= ~0x3FF;
        id |= (index & 0x3FF);
    }
    RSDK_FORCE_INLINE void SetDirection(uint8 dir)
    {
        id &= ~(3 << 10);
        id |= (dir & 3) << 10;
    }
    RSDK_FORCE_INLINE void SetSolidA(uint8 solid)
    {
        id &= ~(3 << 12);
        id |= (solid & 3) << 12;
    }
    RSDK_FORCE_INLINE void SetSolidB(uint8 solid)
    {
        id &= ~(3 << 14);
        id |= (solid & 3) << 14;
    }

    static RSDK_FORCE_INLINE void Copy(uint16 dst, uint16 src, uint16 count = 1) { RSDKTable->CopyTile(dst, src, count); }

    RSDK_FORCE_INLINE int32 GetAngle(uint8 cPlane, uint8 cMode) { return RSDKTable->GetTileAngle(id, cPlane, cMode); }
    RSDK_FORCE_INLINE void SetAngle(uint8 cPlane, uint8 cMode, uint8 angle) { return RSDKTable->SetTileAngle(id, cPlane, cMode, angle); }
    RSDK_FORCE_INLINE uint8 GetFlags(uint8 cPlane) { return RSDKTable->GetTileFlags(id, cPlane); }
    RSDK_FORCE_INLINE void SetFlags(uint8 cPlane, uint8 flag) { RSDKTable->SetTileFlags(id, cPlane, flag); }
};

struct TileLayer {
    uint8 type;
    uint8 drawGroup[CAMERA_COUNT];
    uint8 widthShift;
    uint8 heightShift;
    uint16 width;
    uint16 height;
    Vector2 position;
    int32 parallaxFactor;
    int32 scrollSpeed;
    int32 scrollPos;
    int32 deformationOffset;
    int32 deformationOffsetW;
    int32 deformationData[0x400];
    int32 deformationDataW[0x400];
    void (*scanlineCallback)(ScanlineInfo *);
    uint16 scrollInfoCount;
    ScrollInfo scrollInfo[0x100];
    uint32 name[4];
    Tile *layout;
    uint8 *lineScroll;

    RSDK_FORCE_INLINE void ProcessParallax() { RSDKTable->ProcessParallax(this); }
};

struct SceneLayer {
    uint16 id;

    RSDK_FORCE_INLINE void Init() { id = (uint16)-1; }

    RSDK_FORCE_INLINE void Get(const char *name) { id = RSDKTable->GetTileLayerID(name); }
    RSDK_FORCE_INLINE void Set(uint16 id) { this->id = id; }

    RSDK_FORCE_INLINE bool32 Loaded() { return id != (uint16)-1; }

    RSDK_FORCE_INLINE bool32 Matches(SceneLayer &other) { return this->id == other.id; }
    RSDK_FORCE_INLINE bool32 Matches(SceneLayer *other)
    {
        if (other)
            return this->id == other->id;
        else
            return this->id == (uint16)-1;
    }

    RSDK_FORCE_INLINE TileLayer *GetTileLayer() { return RSDKTable->GetTileLayer(id); }
    RSDK_FORCE_INLINE void Size(Vector2 *size, bool32 usePixelUnits) { RSDKTable->GetLayerSize(id, size, usePixelUnits); }

    RSDK_FORCE_INLINE Tile GetTile(int32 x, int32 y) { return Tile(RSDKTable->GetTile(id, x, y)); }
    RSDK_FORCE_INLINE void SetTile(int32 x, int32 y, Tile tile) { RSDKTable->SetTile(id, x, y, tile.id); }

    static RSDK_FORCE_INLINE TileLayer *GetTileLayer(const char *name) { return RSDKTable->GetTileLayer(RSDKTable->GetTileLayerID(name)); }
    static RSDK_FORCE_INLINE TileLayer *GetTileLayer(int32 id) { return RSDKTable->GetTileLayer(id); }

    static RSDK_FORCE_INLINE void Copy(SceneLayer dstLayer, int32 dstStartX, int32 dstStartY, SceneLayer srcLayer, int32 srcStartX, int32 srcStartY,
                            int32 countX, int32 countY)
    {
        RSDKTable->CopyTileLayer(dstLayer.id, dstStartX, dstStartY, srcLayer.id, srcStartX, srcStartY, countX, countY);
    }

    static RSDK_FORCE_INLINE void Copy(uint16 dstLayer, int32 dstStartX, int32 dstStartY, uint16 srcLayer, int32 srcStartX, int32 srcStartY, int32 countX,
                            int32 countY)
    {
        RSDKTable->CopyTileLayer(dstLayer, dstStartX, dstStartY, srcLayer, srcStartX, srcStartY, countX, countY);
    }
};

namespace Stage
{

RSDK_FORCE_INLINE ScanlineInfo *GetScanlines() { return RSDKTable->GetScanlines(); }

} // namespace Stage

} // namespace RSDK