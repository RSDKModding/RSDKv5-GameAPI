#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"
#include "Sprite.hpp"

#define SCREEN_YCENTER (SCREEN_YSIZE / 2)

#define LAYER_COUNT     (8)
#define DRAWGROUP_COUNT (16)

#ifndef SCREEN_COUNT
#if RETRO_REV02
#define SCREEN_COUNT (4)
#else
#define SCREEN_COUNT (2)
#endif
#endif

#define CAMERA_COUNT (4)

namespace RSDK
{
enum DrawFX { FX_NONE = 0, FX_FLIP = 1, FX_ROTATE = 2, FX_SCALE = 4 };

enum FlipFlags { FLIP_NONE, FLIP_X, FLIP_Y, FLIP_XY };

enum Alignments { ALIGN_LEFT, ALIGN_RIGHT, ALIGN_CENTER };

enum InkEffects {
    INK_NONE,
    INK_BLEND,
    INK_ALPHA,
    INK_ADD,
    INK_SUB,
    INK_TINT,
    INK_MASKED,
    INK_UNMASKED,
};

enum VideoSettingsValues {
    VIDEOSETTING_WINDOWED,
    VIDEOSETTING_BORDERED,
    VIDEOSETTING_EXCLUSIVEFS,
    VIDEOSETTING_VSYNC,
    VIDEOSETTING_TRIPLEBUFFERED,
    VIDEOSETTING_WINDOW_WIDTH,
    VIDEOSETTING_WINDOW_HEIGHT,
    VIDEOSETTING_FSWIDTH,
    VIDEOSETTING_FSHEIGHT,
    VIDEOSETTING_REFRESHRATE,
    VIDEOSETTING_SHADERSUPPORT,
    VIDEOSETTING_SHADERID,
    VIDEOSETTING_SCREENCOUNT,
#if RETRO_REV02
    VIDEOSETTING_DIMTIMER,
#endif
    VIDEOSETTING_STREAMSENABLED,
    VIDEOSETTING_STREAM_VOL,
    VIDEOSETTING_SFX_VOL,
    VIDEOSETTING_LANGUAGE,
    VIDEOSETTING_STORE,
    VIDEOSETTING_RELOAD,
    VIDEOSETTING_CHANGED,
    VIDEOSETTING_WRITE,
};

struct Palette {

    Palette() : id(0) {}
    Palette(uint8 bankID) : id(bankID) {}

#if RETRO_REV02
    void Load(const char *path, uint16 disabledRows) { RSDKTable->LoadPalette(id, path, disabledRows); }
#endif

#if RETRO_REV01
    static uint16 *GetTintLookupTable() { return RSDKTable->GetTintLookupTable(); }
#endif

#if RETRO_REV02
    static void SetTintLookupTable(uint16 *lookupTable) { RSDKTable->SetTintLookupTable(lookupTable); }
#endif

    static void SetPaletteMask(uint32 maskColor) { RSDKTable->SetPaletteMask(maskColor); }

    void SetEntry(uint8 index, uint32 color) { RSDKTable->SetPaletteEntry(id, index, color); }

    uint32 GetEntry(uint8 index) { return RSDKTable->GetPaletteEntry(id, index); }

    void SetActivePalette(int32 startLine, int32 endLine) { RSDKTable->SetActivePalette(id, startLine, endLine); }

    void Rotate(uint8 startIndex, uint8 endIndex, bool32 right) { RSDKTable->RotatePalette(id, startIndex, endIndex, right ? 1 : 0); }

    void Copy(uint8 sourceBank, uint8 srcBankStart, uint8 destBankStart, uint16 count)
    {
        RSDKTable->CopyPalette(sourceBank, srcBankStart, id, destBankStart, count);
    }

    void SetLimitedFade(uint8 srcBankA, uint8 srcBankB, uint16 blendAmount, int32 startIndex, int32 endIndex)
    {
        RSDKTable->SetLimitedFade(id, srcBankA, srcBankB, blendAmount, startIndex, endIndex);
    }

#if RETRO_REV02
    void BlendColors(uint32 *srcColorsA, uint32 *srcColorsB, int32 blendAmount, int32 startIndex, int32 count)
    {
        RSDKTable->BlendColors(id, srcColorsA, srcColorsB, blendAmount, startIndex, count);
    }
#endif

    uint8 id;
};

extern Palette paletteBank[8];

struct Tile;

namespace Graphics
{

// Cameras
inline void AddCamera(Vector2 *targetPos, int32 offsetX, int32 offsetY, bool32 worldRelative)
{
    RSDKTable->AddCamera(targetPos, offsetX, offsetY, worldRelative);
}
inline void ClearCameras() { RSDKTable->ClearCameras(); }

// Drawing
inline void DrawLine(int32 x1, int32 y1, int32 x2, int32 y2, uint32 color, int32 alpha, uint8 inkEffect, bool32 screenRelative)
{
    RSDKTable->DrawLine(x1, y1, x2, y2, color, alpha, (InkEffects)inkEffect, screenRelative);
}

inline void DrawRect(int32 x, int32 y, int32 width, int32 height, uint32 color, int32 alpha, uint8 inkEffect, bool32 screenRelative)
{
    RSDKTable->DrawRect(x, y, width, height, color, alpha, (InkEffects)inkEffect, screenRelative);
}

inline void DrawCircle(int32 x, int32 y, int32 radius, uint32 color, int32 alpha, uint8 inkEffect, bool32 screenRelative)
{
    RSDKTable->DrawCircle(x, y, radius, color, alpha, (InkEffects)inkEffect, screenRelative);
}

inline void DrawCircleOutline(int32 x, int32 y, int32 innerRadius, int32 outerRadius, uint32 color, int32 alpha, uint8 inkEffect,
                              bool32 screenRelative)
{
    RSDKTable->DrawCircleOutline(x, y, innerRadius, outerRadius, color, alpha, inkEffect, screenRelative);
}

inline void DrawFace(Vector2 *vertices, int32 vertCount, int32 r, int32 g, int32 b, int32 alpha, int32 inkEffect)
{
    RSDKTable->DrawFace(vertices, vertCount, r, g, b, alpha, inkEffect);
}

inline void DrawBlendedFace(Vector2 *vertices, color *vertColors, int32 vertCount, int32 alpha, int32 inkEffect)
{
    RSDKTable->DrawBlendedFace(vertices, vertColors, vertCount, alpha, inkEffect);
}

inline void DrawDeformedSprite(SpriteSheet sheet, int32 inkEffect, bool32 screenRelative)
{
    RSDKTable->DrawDeformedSprite(sheet.id, inkEffect, screenRelative);
}

inline void DrawTile(Tile *tiles, int32 countX, int32 countY, Vector2 *position, Vector2 *offset, bool32 screenRelative)
{
    RSDKTable->DrawTile((uint16 *)tiles, countX, countY, position, offset, screenRelative);
}

inline void CopyTile(uint16 dest, uint16 src, uint16 count) { RSDKTable->CopyTile(dest, src, count); }

inline void DrawAniTiles(SpriteSheet sheet, uint16 tileIndex, uint16 srcX, uint16 srcY, uint16 width, uint16 height)
{
    RSDKTable->DrawAniTiles(sheet.id, tileIndex, srcX, srcY, width, height);
}

inline void FillScreen(color color, int32 alphaR, int32 alphaG, int32 alphaB) { RSDKTable->FillScreen(color, alphaR, alphaG, alphaB); }

// Screens & Displays
inline void GetDisplayInfo(int32 *displayID, int32 *width, int32 *height, int32 *refreshRate, char *text)
{
    RSDKTable->GetDisplayInfo(displayID, width, height, refreshRate, text);
}
inline void GetWindowSize(int32 *width, int32 *height) { RSDKTable->GetWindowSize(width, height); }
inline int32 SetScreenSize(uint8 screenID, uint16 width, uint16 height) { return RSDKTable->SetScreenSize(screenID, width, height); }
inline void SetClipBounds(uint8 screenID, int32 x1, int32 y1, int32 x2, int32 y2) { RSDKTable->SetClipBounds(screenID, x1, y1, x2, y2); }
#if RETRO_REV02
inline void SetScreenVertices(uint8 startVert2P_S1, uint8 startVert2P_S2, uint8 startVert3P_S1, uint8 startVert3P_S2, uint8 startVert3P_S3)
{
    RSDKTable->SetScreenVertices(startVert2P_S1, startVert2P_S2, startVert3P_S1, startVert3P_S2, startVert3P_S3);
}
#endif

// Window/Video Settings
inline int32 GetVideoSetting(VideoSettingsValues id) { return RSDKTable->GetVideoSetting(id); }
inline void SetVideoSetting(VideoSettingsValues id, int32 value) { RSDKTable->SetVideoSetting(id, value); }

inline void UpdateWindow() { RSDKTable->UpdateWindow(); }

// Entities & Objects
inline int32 GetDrawListRefSlot(uint8 drawGroup, uint16 listPos) { return RSDKTable->GetDrawListRefSlot(drawGroup, listPos); }
inline void *GetDrawListRef(uint8 drawGroup, uint16 listPos) { return RSDKTable->GetDrawListRef(drawGroup, listPos); }
template <typename T> inline T *GetDrawListRef(uint8 drawGroup, uint16 entitySlot) { return (T *)RSDKTable->GetDrawListRef(drawGroup, entitySlot); }
inline void AddDrawListRef(uint8 drawGroup, uint16 entitySlot) { RSDKTable->AddDrawListRef(drawGroup, entitySlot); }
inline void SwapDrawListEntries(uint8 drawGroup, uint16 slot1, uint16 slot2, uint16 count)
{
    RSDKTable->SwapDrawListEntries(drawGroup, slot1, slot2, count);
}
inline void SetDrawGroupProperties(uint8 drawGroup, bool32 sorted, void (*hookCB)()) { RSDKTable->SetDrawGroupProperties(drawGroup, sorted, hookCB); }

} // namespace Graphics

} // namespace RSDK
