#pragma once

#include "Types.hpp"

#ifndef SCREEN_XMAX
#define SCREEN_XMAX (1280)
#endif

#ifndef SCREEN_YSIZE
#define SCREEN_YSIZE (240)
#endif

#include <stdio.h>
#include <cstring>

namespace RSDK
{

// RSDK forward decls
struct Vector2;

struct String;

struct Matrix;
struct Animator;
struct SpriteFrame;

struct Hitbox;
struct CollisionSensor;
struct CollisionMask;

struct ScrollInfo;
struct TileLayer;
struct TileInfo;
struct ScanlineInfo;

// API forward decls
struct AchievementID;
struct LeaderboardID;
struct LeaderboardAvail;
struct LeaderboardEntry;
struct StatInfo;

struct RSDKFunctionTable;
struct APIFunctionTable;
#if RETRO_USE_MOD_LOADER
struct ModFunctionTable;
#endif
struct SceneInfo;
struct GameInfo;
struct SKUInfo;
struct ControllerState;
struct AnalogState;
struct AnalogState;
struct TriggerState;
struct TriggerState;
struct TouchInfo;
struct UnknownInfo;
struct ScreenInfo;

extern RSDKFunctionTable *RSDKTable;
extern APIFunctionTable *APITable;
#if RETRO_USE_MOD_LOADER
extern ModFunctionTable *modTable;
#endif

extern SceneInfo *sceneInfo;

extern GameInfo *gameInfo;
extern SKUInfo *SKU;

extern ControllerState *controllerInfo;
extern AnalogState *analogStickInfoL;
extern AnalogState *analogStickInfoR;
extern TriggerState *triggerInfoL;
extern TriggerState *triggerInfoR;
extern TouchInfo *touchInfo;

extern UnknownInfo *unknownInfo;

extern ScreenInfo *screenInfo;

enum Scopes {
    SCOPE_NONE,
    SCOPE_GLOBAL,
    SCOPE_STAGE,
};

enum GameRegions {
    REGION_US,
    REGION_JP,
    REGION_EU,
};

enum GameLanguages {
    LANGUAGE_EN,
    LANGUAGE_FR,
    LANGUAGE_IT,
    LANGUAGE_GE,
    LANGUAGE_SP,
    LANGUAGE_JP,
    LANGUAGE_KO,
    LANGUAGE_SC,
    LANGUAGE_TC,
};

#if RETRO_USE_MOD_LOADER
// Mod Table
struct ModFunctionTable {
    // Registration & Core
#if RETRO_REV0U
    void (*RegisterGlobals)(const char *globalsPath, void **globals, uint32 size, void (*initCB)(void *globals));
    void (*RegisterObject)(void **staticVars, void **modStaticVars, const char *name, uint32 entityClassSize, uint32 staticClassSize,
                           uint32 modClassSize, void (*update)(void), void (*lateUpdate)(void), void (*staticUpdate)(void), void (*draw)(void),
                           void (*create)(void *), void (*stageLoad)(void), void (*editorLoad)(void), void (*editorDraw)(void),
                           void (*serialize)(void), void (*staticLoad)(void *staticVars), const char *inherited);
#else
    void (*RegisterGlobals)(const char *globalsPath, void **globals, uint32 size);
    void (*RegisterObject)(void **staticVars, void **modStaticVars, const char *name, uint32 entityClassSize, uint32 staticClassSize,
                           uint32 modClassSize, void (*update)(void), void (*lateUpdate)(void), void (*staticUpdate)(void), void (*draw)(void),
                           void (*create)(void *), void (*stageLoad)(void), void (*editorLoad)(void), void (*editorDraw)(void),
                           void (*serialize)(void), const char *inherited);
#endif
    void *RegisterObject_STD;
    void (*RegisterObjectHook)(void **staticVars, const char *staticName);
    void *(*FindObject)(const char *name);
    void *(*GetGlobals)(void);
    void (*Super)(int32 classID, int32 callback, void *data);

    // Mod Info
    bool32 (*LoadModInfo)(const char *id, String *name, String *description, String *version, bool32 *active);
    void (*GetModPath)(const char *id, String *result);
    int32 (*GetModCount)(bool32 active);
    const char *(*GetModIDByIndex)(uint32 index);
    bool32 (*ForeachModID)(String *id);

    // Mod Callbacks & Public Functions
    void (*AddModCallback)(int32 callbackID, void (*callback)(void *));
    void *AddModCallback_STD;
    void (*AddPublicFunction)(const char *functionName, void *functionPtr);
    void *(*GetPublicFunction)(const char *id, const char *functionName);

    // Mod Settings
    bool32 (*GetSettingsBool)(const char *id, const char *key, bool32 fallback);
    int32 (*GetSettingsInteger)(const char *id, const char *key, int32 fallback);
    float (*GetSettingsFloat)(const char *id, const char *key, float fallback);
    void (*GetSettingsString)(const char *id, const char *key, String *result, const char *fallback);
    void (*SetSettingsBool)(const char *key, bool32 val);
    void (*SetSettingsInteger)(const char *key, int32 val);
    void (*SetSettingsFloat)(const char *key, float val);
    void (*SetSettingsString)(const char *key, String *val);
    void (*SaveSettings)(void);

    // Config
    bool32 (*GetConfigBool)(const char *key, bool32 fallback);
    int32 (*GetConfigInteger)(const char *key, int32 fallback);
    float (*GetConfigFloat)(const char *key, float fallback);
    void (*GetConfigString)(const char *key, String *result, const char *fallback);
    bool32 (*ForeachConfig)(String *config);
    bool32 (*ForeachConfigCategory)(String *category);

    // Achievements
    void (*RegisterAchievement)(const char *identifier, const char *name, const char *desc);
    void (*GetAchievementInfo)(uint32 id, String *name, String *description, String *identifier, bool32 *achieved);
    int32 (*GetAchievementIndexByID)(const char *identifier);
    int32 (*GetAchievementCount)(void);

    // Shaders
    void (*LoadShader)(const char *shaderName, bool32 linear);

    // StateMachine
    void (*StateMachineRun)(void (*state)(void));
    void (*RegisterStateHook)(void (*state)(void), bool32 (*hook)(bool32 skippedState), bool32 priority);
    // runs all high priority state hooks hooked to the address of 'state', returns if the main state should be skipped or not
    bool32 (*HandleRunState_HighPriority)(void (*state)(void));
    // runs all low priority state hooks hooked to the address of 'state'
    void (*HandleRunState_LowPriority)(void (*state)(void), bool32 skipState);

#if RETRO_MOD_LOADER_VER >= 2
    // Mod Settings (Part 2)
    bool32 (*ForeachSetting)(const char *id, String *setting);
    bool32 (*ForeachSettingCategory)(const char *id, String *category);

    // Files
    bool32 (*ExcludeFile)(const char *id, const char *path);
    bool32 (*ExcludeAllFiles)(const char *id);
    bool32 (*ReloadFile)(const char *id, const char *path);
    bool32 (*ReloadAllFiles)(const char *id);

    // Graphics
    void *(*GetSpriteAnimation)(uint16 id);
    void *(*GetSpriteSurface)(uint16 id);
    uint16 *(*GetPaletteBank)(uint8 id);
    uint8 *(*GetActivePaletteBuffer)(void);
    void (*GetRGB32To16Buffer)(uint16 **rgb32To16_R, uint16 **rgb32To16_G, uint16 **rgb32To16_B);
    uint16 *(*GetBlendLookupTable)(void);
    uint16 *(*GetSubtractLookupTable)(void);
    uint16 *(*GetTintLookupTable)(void);
    color (*GetMaskColor)(void);
    void *(*GetScanEdgeBuffer)(void);
    void *(*GetCamera)(uint8 id);
    void *(*GetShader)(uint8 id);
    void *(*GetModel)(uint16 id);
    void *(*GetScene3D)(uint16 id);
    void (*DrawDynamicAniTiles)(Animator *animator, uint16 tileIndex);

    // Audio
    void *(*GetSfx)(uint16 id);
    void *(*GetChannel)(uint8 id);

    // Objects/Entities
    bool32 (*GetGroupEntities)(uint16 group, void **entity);

    // Collision
    void (*SetPathGripSensors)(CollisionSensor *sensors); // expects 5 sensors
    void (*FindFloorPosition)(CollisionSensor *sensor);
    void (*FindLWallPosition)(CollisionSensor *sensor);
    void (*FindRoofPosition)(CollisionSensor *sensor);
    void (*FindRWallPosition)(CollisionSensor *sensor);
    void (*FloorCollision)(CollisionSensor *sensor);
    void (*LWallCollision)(CollisionSensor *sensor);
    void (*RoofCollision)(CollisionSensor *sensor);
    void (*RWallCollision)(CollisionSensor *sensor);
    void (*CopyCollisionMask)(uint16 dst, uint16 src, uint8 cPlane, uint8 cMode);
    void (*GetCollisionInfo)(CollisionMask **masks, TileInfo **tileInfo);
#endif
};
#endif

#if RETRO_REV02
struct APIFunctionTable {
    // API Core
    int32 (*GetUserLanguage)(void);
    bool32 (*GetConfirmButtonFlip)(void);
    void (*ExitGame)(void);
    void (*LaunchManual)(void);
#if RETRO_REV0U
    int32 (*GetDefaultGamepadType)(void);
#endif
    bool32 (*IsOverlayEnabled)(uint32 deviceID);
    bool32 (*CheckDLC)(int32 dlc);
#if RETRO_USE_EGS
    bool32 (*SetupExtensionOverlay)(void);
    bool32 (*CanShowExtensionOverlay)(int32 overlay);
#endif
    bool32 (*ShowExtensionOverlay)(int32 overlay);
#if RETRO_USE_EGS
    bool32 (*CanShowAltExtensionOverlay)(int32 overlay);
    bool32 (*ShowAltExtensionOverlay)(int32 overlay);
    int32 (*GetConnectingStringID)(void);
    void (*ShowLimitedVideoOptions)(int32 id);
#endif

    // Achievements
    void (*TryUnlockAchievement)(AchievementID *id);
    bool32 (*GetAchievementsEnabled)(void);
    void (*SetAchievementsEnabled)(bool32 enabled);
#if RETRO_USE_EGS
    bool32 (*CheckAchievementsEnabled)(void);
    void (*SetAchievementNames)(String **names, int32 count);
#endif

    // Leaderboards
#if RETRO_USE_EGS
    bool32 (*CheckLeaderboardsEnabled)(void);
#endif
    void (*InitLeaderboards)(void);
    void (*FetchLeaderboard)(LeaderboardID *leaderboard, bool32 isUser);
    void (*TrackScore)(LeaderboardID *leaderboard, int32 score, void (*callback)(bool32 success, int32 rank));
    int32 (*GetLeaderboardsStatus)(void);
    LeaderboardAvail (*LeaderboardEntryViewSize)(void);
    LeaderboardAvail (*LeaderboardEntryLoadSize)(void);
    void (*LoadLeaderboardEntries)(int32 start, uint32 end, int32 type);
    void (*ResetLeaderboardInfo)(void);
    LeaderboardEntry *(*ReadLeaderboardEntry)(uint32 entryID);

    // Rich Presence
    void (*SetRichPresence)(int32 id, String *text);

    // Stats
    void (*TryTrackStat)(StatInfo *stat);
    bool32 (*GetStatsEnabled)(void);
    void (*SetStatsEnabled)(bool32 enabled);

    // Authorization
    void (*ClearPrerollErrors)(void);
    void (*TryAuth)(void);
    int32 (*GetUserAuthStatus)(void);
    bool32 (*GetUsername)(String *userName);

    // Storage
    void (*TryInitStorage)(void);
    int32 (*GetStorageStatus)(void);
    int32 (*GetSaveStatus)(void);
    void (*ClearSaveStatus)(void);
    void (*SetSaveStatusContinue)(void);
    void (*SetSaveStatusOK)(void);
    void (*SetSaveStatusForbidden)(void);
    void (*SetSaveStatusError)(void);
    void (*SetNoSave)(bool32 noSave);
    bool32 (*GetNoSave)(void);

    // User File Management
    void (*LoadUserFile)(const char *name, void *buffer, uint32 size, void (*callback)(int32 status)); // load user file from game dir
    void (*SaveUserFile)(const char *name, void *buffer, uint32 size, void (*callback)(int32 status),
                         bool32 compressed);                                  // save user file to game dir
    void (*DeleteUserFile)(const char *name, void (*callback)(int32 status)); // delete user file from game dir

    // User DBs
    uint16 (*InitUserDB)(const char *name, ...);
    uint16 (*LoadUserDB)(const char *filename, void (*callback)(int32 status));
    bool32 (*SaveUserDB)(uint16 tableID, void (*callback)(int32 status));
    void (*ClearUserDB)(uint16 tableID);
    void (*ClearAllUserDBs)(void);
    uint16 (*SetupUserDBRowSorting)(uint16 tableID);
    bool32 (*GetUserDBRowsChanged)(uint16 tableID);
    int32 (*AddRowSortFilter)(uint16 tableID, int32 type, const char *name, void *value);
    int32 (*SortDBRows)(uint16 tableID, int32 type, const char *name, bool32 sortAscending);
    int32 (*GetSortedUserDBRowCount)(uint16 tableID);
    int32 (*GetSortedUserDBRowID)(uint16 tableID, uint16 row);
    int32 (*AddUserDBRow)(uint16 tableID);
    bool32 (*SetUserDBValue)(uint16 tableID, uint32 row, int32 type, const char *name, void *value);
    bool32 (*GetUserDBValue)(uint16 tableID, uint32 row, int32 type, const char *name, void *value);
    uint32 (*GetUserDBRowUUID)(uint16 tableID, uint16 row);
    uint16 (*GetUserDBRowByID)(uint16 tableID, uint32 uuid);
    void (*GetUserDBRowCreationTime)(uint16 tableID, uint16 row, char *buffer, size_t bufferSize, const char *format);
    bool32 (*RemoveDBRow)(uint16 tableID, uint16 row);
    bool32 (*RemoveAllDBRows)(uint16 tableID);
};
#endif

// Function Table
struct RSDKFunctionTable {
    // Registration
#if RETRO_REV0U
    void (*RegisterGlobalVariables)(void **globals, int32 size, void (*initCB)(void *globals));
    void (*RegisterObject)(void **staticVars, const char *name, uint32 entityClassSize, uint32 staticClassSize, void (*update)(void),
                           void (*lateUpdate)(void), void (*staticUpdate)(void), void (*draw)(void), void (*create)(void *), void (*stageLoad)(void),
                           void (*editorLoad)(void), void (*editorDraw)(void), void (*serialize)(void), void (*staticLoad)(void *staticVars));
#else
    void (*RegisterGlobalVariables)(void **globals, int32 size);
    void (*RegisterObject)(void **staticVars, const char *name, uint32 entityClassSize, uint32 staticClassSize, void (*update)(void),
                           void (*lateUpdate)(void), void (*staticUpdate)(void), void (*draw)(void), void (*create)(void *), void (*stageLoad)(void),
                           void (*editorLoad)(void), void (*editorDraw)(void), void (*serialize)(void));
#endif
#if RETRO_REV02
    void (*RegisterStaticVariables)(void **varClass, const char *name, uint32 classSize);
#endif

    // Entities & Objects
    bool32 (*GetActiveEntities)(uint16 group, void **entity);
    bool32 (*GetAllEntities)(uint16 classID, void **entity);
    void (*BreakForeachLoop)(void);
    void (*SetEditableVar)(uint8 type, const char *name, uint8 classID, int32 offset);
    void *(*GetEntity)(uint16 slot);
    int32 (*GetEntitySlot)(void *entity);
    int32 (*GetEntityCount)(uint16 classID, bool32 isActive);
    int32 (*GetDrawListRefSlot)(uint8 drawGroup, uint16 listPos);
    void *(*GetDrawListRef)(uint8 drawGroup, uint16 listPos);
    void (*ResetEntity)(void *entity, uint16 classID, void *data);
    void (*ResetEntitySlot)(uint16 slot, uint16 classID, void *data);
    void *(*CreateEntity)(uint16 classID, void *data, int32 x, int32 y);
    void (*CopyEntity)(void *destEntity, void *srcEntity, bool32 clearSrcEntity);
    bool32 (*CheckOnScreen)(void *entity, Vector2 *range);
    bool32 (*CheckPosOnScreen)(Vector2 *position, Vector2 *range);
    void (*AddDrawListRef)(uint8 drawGroup, uint16 entitySlot);
    void (*SwapDrawListEntries)(uint8 drawGroup, uint16 slot1, uint16 slot2, uint16 count);
    void (*SetDrawGroupProperties)(uint8 drawGroup, bool32 sorted, void (*hookCB)(void));

    // Scene Management
    void (*SetScene)(const char *categoryName, const char *sceneName);
    void (*SetEngineState)(uint8 state);
#if RETRO_REV02
    void (*ForceHardReset)(bool32 shouldHardReset);
#endif
    bool32 (*CheckValidScene)(void);
    bool32 (*CheckSceneFolder)(const char *folderName);
    void (*LoadScene)(void);
    int32 (*FindObject)(const char *name);

    // Cameras
    void (*ClearCameras)(void);
    void (*AddCamera)(Vector2 *targetPos, int32 offsetX, int32 offsetY, bool32 worldRelative);

    // API (Rev01 only)
#if !RETRO_REV02
    void *(*GetAPIFunction)(const char *funcName);
#endif

    // Window/Video Settings
    int32 (*GetVideoSetting)(int32 id);
    void (*SetVideoSetting)(int32 id, int32 value);
    void (*UpdateWindow)(void);

    // Math
    int32 (*Sin1024)(int32 angle);
    int32 (*Cos1024)(int32 angle);
    int32 (*Tan1024)(int32 angle);
    int32 (*ASin1024)(int32 angle);
    int32 (*ACos1024)(int32 angle);
    int32 (*Sin512)(int32 angle);
    int32 (*Cos512)(int32 angle);
    int32 (*Tan512)(int32 angle);
    int32 (*ASin512)(int32 angle);
    int32 (*ACos512)(int32 angle);
    int32 (*Sin256)(int32 angle);
    int32 (*Cos256)(int32 angle);
    int32 (*Tan256)(int32 angle);
    int32 (*ASin256)(int32 angle);
    int32 (*ACos256)(int32 angle);
    int32 (*Rand)(int32 min, int32 max);
    int32 (*RandSeeded)(int32 min, int32 max, int32 *seed);
    void (*SetRandSeed)(int32 seed);
    uint8 (*ATan2)(int32 x, int32 y);

    // Matrices
    void (*SetIdentityMatrix)(Matrix *matrix);
    void (*MatrixMultiply)(Matrix *dest, Matrix *matrixA, Matrix *matrixB);
    void (*MatrixTranslateXYZ)(Matrix *matrix, int32 x, int32 y, int32 z, bool32 setIdentity);
    void (*MatrixScaleXYZ)(Matrix *matrix, int32 x, int32 y, int32 z);
    void (*MatrixRotateX)(Matrix *matrix, int16 angle);
    void (*MatrixRotateY)(Matrix *matrix, int16 angle);
    void (*MatrixRotateZ)(Matrix *matrix, int16 angle);
    void (*MatrixRotateXYZ)(Matrix *matrix, int16 x, int16 y, int16 z);
    void (*MatrixInverse)(Matrix *dest, Matrix *matrix);
    void (*MatrixCopy)(Matrix *matDest, Matrix *matSrc);

    // Strings
    void (*InitString)(String *string, const char *text, uint32 textLength);
    void (*CopyString)(String *dst, String *src);
    void (*SetString)(String *string, const char *text);
    void (*AppendString)(String *string, String *appendString);
    void (*AppendText)(String *string, const char *appendText);
    void (*LoadStringList)(String *stringList, const char *filePath, uint32 charSize);
    bool32 (*SplitStringList)(String *splitStrings, String *stringList, int32 startStringID, int32 stringCount);
    void (*GetCString)(char *destChars, String *string);
    bool32 (*CompareStrings)(String *string1, String *string2, bool32 exactMatch);

    // Screens & Displays
    void (*GetDisplayInfo)(int32 *displayID, int32 *width, int32 *height, int32 *refreshRate, char *text);
    void (*GetWindowSize)(int32 *width, int32 *height);
    int32 (*SetScreenSize)(uint8 screenID, uint16 width, uint16 height);
    void (*SetClipBounds)(uint8 screenID, int32 x1, int32 y1, int32 x2, int32 y2);
#if RETRO_REV02
    void (*SetScreenVertices)(uint8 startVert2P_S1, uint8 startVert2P_S2, uint8 startVert3P_S1, uint8 startVert3P_S2, uint8 startVert3P_S3);
#endif

    // Spritesheets
    uint16 (*LoadSpriteSheet)(const char *filePath, uint8 scope);

    // Palettes & Colors
#if RETRO_REV02
    void (*SetTintLookupTable)(uint16 *lookupTable);
#else
    uint16 *(*GetTintLookupTable)(void);
#endif
    void (*SetPaletteMask)(color maskColor);
    void (*SetPaletteEntry)(uint8 bankID, uint8 index, uint32 color);
    color (*GetPaletteEntry)(uint8 bankID, uint8 index);
    void (*SetActivePalette)(uint8 newActiveBank, int32 startLine, int32 endLine);
    void (*CopyPalette)(uint8 sourceBank, uint8 srcBankStart, uint8 destinationBank, uint8 destBankStart, uint8 count);
#if RETRO_REV02
    void (*LoadPalette)(uint8 bankID, const char *path, uint16 disabledRows);
#endif
    void (*RotatePalette)(uint8 bankID, uint8 startIndex, uint8 endIndex, bool32 right);
    void (*SetLimitedFade)(uint8 destBankID, uint8 srcBankA, uint8 srcBankB, int16 blendAmount, int32 startIndex, int32 endIndex);
#if RETRO_REV02
    void (*BlendColors)(uint8 destBankID, color *srcColorsA, color *srcColorsB, int32 blendAmount, int32 startIndex, int32 count);
#endif

    // Drawing
    void (*DrawRect)(int32 x, int32 y, int32 width, int32 height, uint32 color, int32 alpha, int32 inkEffect, bool32 screenRelative);
    void (*DrawLine)(int32 x1, int32 y1, int32 x2, int32 y2, uint32 color, int32 alpha, int32 inkEffect, bool32 screenRelative);
    void (*DrawCircle)(int32 x, int32 y, int32 radius, uint32 color, int32 alpha, int32 inkEffect, bool32 screenRelative);
    void (*DrawCircleOutline)(int32 x, int32 y, int32 innerRadius, int32 outerRadius, uint32 color, int32 alpha, int32 inkEffect,
                              bool32 screenRelative);
    void (*DrawFace)(Vector2 *vertices, int32 vertCount, int32 r, int32 g, int32 b, int32 alpha, int32 inkEffect);
    void (*DrawBlendedFace)(Vector2 *vertices, color *vertColors, int32 vertCount, int32 alpha, int32 inkEffect);
    void (*DrawSprite)(Animator *animator, Vector2 *position, bool32 screenRelative);
    void (*DrawDeformedSprite)(uint16 sheetID, int32 inkEffect, bool32 screenRelative);
    void (*DrawText)(Animator *animator, Vector2 *position, String *string, int32 endFrame, int32 textLength, int32 align, int32 spacing, void *unused,
                     Vector2 *charOffsets, bool32 screenRelative);
    void (*DrawTile)(uint16 *tiles, int32 countX, int32 countY, Vector2 *position, Vector2 *offset, bool32 screenRelative);
    void (*CopyTile)(uint16 dest, uint16 src, uint16 count);
    void (*DrawAniTiles)(uint16 sheetID, uint16 tileIndex, uint16 srcX, uint16 srcY, uint16 width, uint16 height);
#if RETRO_REV0U
    void (*DrawDynamicAniTiles)(Animator *animator, uint16 tileIndex);
#endif
    void (*FillScreen)(uint32 color, int32 alphaR, int32 alphaG, int32 alphaB);

    // Meshes & 3D Scenes
    uint16 (*LoadMesh)(const char *filename, uint8 scope);
    uint16 (*Create3DScene)(const char *identifier, uint16 faceCount, uint8 scope);
    void (*Prepare3DScene)(uint16 sceneIndex);
    void (*SetDiffuseColor)(uint16 sceneIndex, uint8 x, uint8 y, uint8 z);
    void (*SetDiffuseIntensity)(uint16 sceneIndex, uint8 x, uint8 y, uint8 z);
    void (*SetSpecularIntensity)(uint16 sceneIndex, uint8 x, uint8 y, uint8 z);
    void (*AddModelTo3DScene)(uint16 modelFrames, uint16 sceneIndex, uint8 drawMode, Matrix *matWorld, Matrix *matView, color color);
    void (*SetModelAnimation)(uint16 modelFrames, Animator *animator, int16 speed, uint8 loopIndex, bool32 forceApply, int16 frameID);
    void (*AddMeshFrameTo3DScene)(uint16 modelFrames, uint16 sceneIndex, Animator *animator, uint8 drawMode, Matrix *matWorld, Matrix *matView,
                                  color color);
    void (*Draw3DScene)(uint16 sceneIndex);

    // Sprite Animations & Frames
    uint16 (*LoadSpriteAnimation)(const char *filePath, uint8 scope);
    uint16 (*CreateSpriteAnimation)(const char *filePath, uint32 frameCount, uint32 listCount, uint8 scope);
#if RETRO_MOD_LOADER_VER >= 2
    void (*SetSpriteAnimation)(uint16 aniFrames, uint16 listID, Animator *animator, bool32 forceApply, int32 frameID);
#else
    void (*SetSpriteAnimation)(uint16 aniFrames, uint16 listID, Animator *animator, bool32 forceApply, int16 frameID);
#endif
    void (*EditSpriteAnimation)(uint16 aniFrames, uint16 listID, const char *name, int32 frameOffset, uint16 frameCount, int16 speed, uint8 loopIndex,
                                uint8 rotationStyle);
    void (*SetSpriteString)(uint16 aniFrames, uint16 listID, String *string);
    uint16 (*FindSpriteAnimation)(uint16 aniFrames, const char *name);
    SpriteFrame *(*GetFrame)(uint16 aniFrames, uint16 listID, int32 frameID);
    Hitbox *(*GetHitbox)(Animator *animator, uint8 hitboxID);
    int16 (*GetFrameID)(Animator *animator);
    int32 (*GetStringWidth)(uint16 aniFrames, uint16 listID, String *string, int32 startIndex, int32 length, int32 spacing);
    void (*ProcessAnimation)(Animator *animator);

    // Tile Layers
    uint16 (*GetTileLayerID)(const char *name);
    TileLayer *(*GetTileLayer)(uint16 layerID);
    void (*GetLayerSize)(uint16 layer, Vector2 *size, bool32 usePixelUnits);
    uint16 (*GetTile)(uint16 layer, int32 x, int32 y);
    void (*SetTile)(uint16 layer, int32 x, int32 y, uint16 tile);
    void (*CopyTileLayer)(uint16 dstLayerID, int32 dstStartX, int32 dstStartY, uint16 srcLayerID, int32 srcStartX, int32 srcStartY, int32 countX,
                           int32 countY);
    void (*ProcessParallax)(TileLayer *tileLayer);
    ScanlineInfo *(*GetScanlines)(void);

    // Object & Tile Collisions
    bool32 (*CheckObjectCollisionTouchBox)(void *thisEntity, Hitbox *thisHitbox, void *otherEntity, Hitbox *otherHitbox);
    bool32 (*CheckObjectCollisionTouchCircle)(void *thisEntity, int32 thisRadius, void *otherEntity, int32 otherRadius);
    uint8 (*CheckObjectCollisionBox)(void *thisEntity, Hitbox *thisHitbox, void *otherEntity, Hitbox *otherHitbox, bool32 setPos);
    bool32 (*CheckObjectCollisionPlatform)(void *thisEntity, Hitbox *thisHitbox, void *otherEntity, Hitbox *otherHitbox, bool32 setPos);
    bool32 (*ObjectTileCollision)(void *entity, uint16 collisionLayers, uint8 collisionMode, uint8 collisionPlane, int32 xOffset, int32 yOffset,
                                  bool32 setPos);
    bool32 (*ObjectTileGrip)(void *entity, uint16 collisionLayers, uint8 collisionMode, uint8 collisionPlane, int32 xOffset, int32 yOffset,
                             int32 tolerance);
    void (*ProcessObjectMovement)(void *entity, Hitbox *outer, Hitbox *inner);
#if RETRO_REV0U
    void (*SetupCollisionConfig)(int32 minDistance, uint8 lowTolerance, uint8 highTolerance, uint8 floorAngleTolerance, uint8 wallAngleTolerance,
                                 uint8 roofAngleTolerance);
    void (*SetPathGripSensors)(CollisionSensor *sensors); // expects 5 sensors
    void (*FindFloorPosition)(CollisionSensor *sensor);
    void (*FindLWallPosition)(CollisionSensor *sensor);
    void (*FindRoofPosition)(CollisionSensor *sensor);
    void (*FindRWallPosition)(CollisionSensor *sensor);
    void (*FloorCollision)(CollisionSensor *sensor);
    void (*LWallCollision)(CollisionSensor *sensor);
    void (*RoofCollision)(CollisionSensor *sensor);
    void (*RWallCollision)(CollisionSensor *sensor);
#endif
    int32 (*GetTileAngle)(uint16 tile, uint8 cPlane, uint8 cMode);
    void (*SetTileAngle)(uint16 tile, uint8 cPlane, uint8 cMode, uint8 angle);
    uint8 (*GetTileFlags)(uint16 tile, uint8 cPlane);
    void (*SetTileFlags)(uint16 tile, uint8 cPlane, uint8 flag);
#if RETRO_REV0U
    void (*CopyCollisionMask)(uint16 dst, uint16 src, uint8 cPlane, uint8 cMode);
    void (*GetCollisionInfo)(CollisionMask **masks, TileInfo **tileInfo);
#endif

    // Audio
    uint16 (*GetSfx)(const char *path);
    int32 (*PlaySfx)(uint16 sfx, int32 loopPoint, int32 priority);
    void (*StopSfx)(uint16 sfx);
    int32 (*PlayStream)(const char *filename, uint32 channel, uint32 startPos, uint32 loopPoint, bool32 loadASync);
    void (*SetChannelAttributes)(uint8 channel, float volume, float pan, float speed);
    void (*StopChannel)(uint32 channel);
    void (*PauseChannel)(uint32 channel);
    void (*ResumeChannel)(uint32 channel);
    bool32 (*IsSfxPlaying)(uint16 sfx);
    bool32 (*ChannelActive)(uint32 channel);
    uint32 (*GetChannelPos)(uint32 channel);

    // Videos & "HD Images"
    bool32 (*LoadVideo)(const char *filename, double startDelay, bool32 (*skipCallback)(void));
    bool32 (*LoadImage)(const char *filename, double displayLength, double fadeSpeed, bool32 (*skipCallback)(void));

    // Input
#if RETRO_REV02
    uint32 (*GetInputDeviceID)(uint8 inputSlot);
    uint32 (*GetFilteredInputDeviceID)(bool32 confirmOnly, bool32 unassignedOnly, uint32 maxInactiveTimer);
    int32 (*GetInputDeviceType)(uint32 deviceID);
    bool32 (*IsInputDeviceAssigned)(uint32 deviceID);
    int32 (*GetInputDeviceUnknown)(uint32 deviceID);
    int32 (*InputDeviceUnknown1)(uint32 deviceID, int32 unknown1, int32 unknown2);
    int32 (*InputDeviceUnknown2)(uint32 deviceID, int32 unknown1, int32 unknown2);
    int32 (*GetInputSlotUnknown)(uint8 inputSlot);
    int32 (*InputSlotUnknown1)(uint8 inputSlot, int32 unknown1, int32 unknown2);
    int32 (*InputSlotUnknown2)(uint8 inputSlot, int32 unknown1, int32 unknown2);
    void (*AssignInputSlotToDevice)(uint8 inputSlot, uint32 deviceID);
    bool32 (*IsInputSlotAssigned)(uint8 inputSlot);
    void (*ResetInputSlotAssignments)(void);
#endif
#if !RETRO_REV02
    void (*GetUnknownInputValue)(int32 inputSlot, int32 type, int32 *value);
#endif

    // User File Management
    bool32 (*LoadUserFile)(const char *fileName, void *buffer, uint32 size); // load user file from exe dir
    bool32 (*SaveUserFile)(const char *fileName, void *buffer, uint32 size); // save user file to exe dir

    // Printing (Rev02)
#if RETRO_REV02
    void (*PrintLog)(int32 mode, const char *message, ...);
    void (*PrintText)(int32 mode, const char *message);
    void (*PrintString)(int32 mode, String *message);
    void (*PrintUInt32)(int32 mode, const char *message, uint32 i);
    void (*PrintInt32)(int32 mode, const char *message, int32 i);
    void (*PrintFloat)(int32 mode, const char *message, float f);
    void (*PrintVector2)(int32 mode, const char *message, Vector2 vec);
    void (*PrintHitbox)(int32 mode, const char *message, Hitbox hitbox);
#endif

    // Editor
    void (*SetActiveVariable)(int32 classID, const char *name);
    void (*AddVarEnumValue)(const char *name);

    // Printing (Rev01)
#if !RETRO_REV02
    void (*PrintMessage)(void *message, uint8 type);
#endif

    // Debugging
#if RETRO_REV02
    void (*ClearViewableVariables)(void);
    void (*AddViewableVariable)(const char *name, void *value, int32 type, int32 min, int32 max);
#endif

#if RETRO_REV0U
    // Origins Extras
    void (*NotifyCallback)(int32 callbackID, int32 param1, int32 param2, int32 param3);
    void (*SetGameFinished)(void);
    void (*StopAllSfx)(void);
#endif
};

} // namespace RSDK

#include "Math/Vector2.hpp"

namespace RSDK
{

enum GamePlatforms {
    PLATFORM_PC,
    PLATFORM_PS4,
    PLATFORM_XB1,
    PLATFORM_SWITCH,

    PLATFORM_DEV = 0xFF,
};

struct SKUInfo {
    int32 platform;
    int32 language;
    int32 region;
};

enum StatusCodes {
    STATUS_NONE      = 0,
    STATUS_CONTINUE  = 100,
    STATUS_OK        = 200,
    STATUS_FORBIDDEN = 403,
    STATUS_NOTFOUND  = 404,
    STATUS_ERROR     = 500,
    STATUS_NOWIFI    = 503,
    STATUS_TIMEOUT   = 504,
    STATUS_CORRUPT   = 505,
    STATUS_NOSPACE   = 506,
};

// None of these besides the named 2 are even used
// and even then they're not even set in plus
struct UnknownInfo {
    int32 unknown1;
    int32 unknown2;
    int32 unknown3;
    int32 unknown4;
    bool32 pausePress;
    int32 unknown5;
    int32 unknown6;
    int32 unknown7;
    int32 unknown8;
    int32 unknown9;
    bool32 anyKeyPress;
    int32 unknown10;
};

struct GameInfo {
    char gameTitle[0x40];
    char gameSubtitle[0x100];
    char version[0x10];
};

struct InputState {
    bool32 down;
    bool32 press;
    int32 keyMap;
};

struct ControllerState {
    InputState keyUp;
    InputState keyDown;
    InputState keyLeft;
    InputState keyRight;
    InputState keyA;
    InputState keyB;
    InputState keyC;
    InputState keyX;
    InputState keyY;
    InputState keyZ;
    InputState keyStart;
    InputState keySelect;

    // Rev01 hasn't split these into different structs yet
#if RETRO_REV01
    InputState keyBumperL;
    InputState keyBumperR;
    InputState keyTriggerL;
    InputState keyTriggerR;
    InputState keyStickL;
    InputState keyStickR;
#endif
};

struct AnalogState {
    InputState keyUp;
    InputState keyDown;
    InputState keyLeft;
    InputState keyRight;
#if RETRO_REV02
    InputState keyStick;
    float deadzone;
    float hDelta;
    float vDelta;
#else
    float deadzone;
    float triggerDeltaL;
    float triggerDeltaR;
    float hDeltaL;
    float vDeltaL;
    float hDeltaR;
    float vDeltaR;
#endif
};

#if RETRO_REV02
struct TriggerState {
    InputState keyBumper;
    InputState keyTrigger;
    float bumperDelta;
    float triggerDelta;
};
#endif

struct TouchInfo {
    float x[0x10];
    float y[0x10];
    bool32 down[0x10];
    uint8 count;
#if !RETRO_REV02
    bool32 pauseHold;
    bool32 pausePress;
    bool32 waitRetryState;
    bool32 anyKeyHold;
    bool32 anyKeyPress;
    bool32 unknown2;
#endif
};

struct ScreenInfo {
    // uint16 *frameBuffer;
    uint16 frameBuffer[SCREEN_XMAX * SCREEN_YSIZE];
    Vector2 position;
    Vector2 size;
    Vector2 center;
    int32 pitch;
    int32 clipBound_X1;
    int32 clipBound_Y1;
    int32 clipBound_X2;
    int32 clipBound_Y2;
    int32 waterDrawPos;
};

struct EngineInfo {
#if RETRO_REV02
    RSDKFunctionTable *RSDKTable;
    APIFunctionTable *APITable;

    GameInfo *gameInfo;
    SKUInfo *currentSKU;
    SceneInfo *sceneInfo;

    ControllerState *controllerInfo;
    AnalogState *stickInfoL;
    AnalogState *stickInfoR;
    TriggerState *triggerInfoL;
    TriggerState *triggerInfoR;
    TouchInfo *touchInfo;

    UnknownInfo *unknownInfo;

    ScreenInfo *screenInfo;

#if RETRO_REV0U
    // only for origins, not technically needed for v5U if standalone I think
    void *hedgehogLink;
#endif

#else
    RSDKFunctionTable *RSDKFunctionTable;

    GameInfo *gameInfo;
    SceneInfo *sceneInfo;

    ControllerState *controllerInfo;
    AnalogState *stickInfoL;

    TouchInfo *touchInfo;

    ScreenInfo *screenInfo;
#endif

#if RETRO_USE_MOD_LOADER
    ModFunctionTable *modFunctionTable;
#endif
};

inline void InitEngineInfo(EngineInfo *info)
{
    RSDKTable = info->RSDKTable;
#if RETRO_REV02
    APITable = info->APITable;
#endif

    gameInfo = info->gameInfo;
#if RETRO_REV02
    SKU = info->currentSKU;
#endif
    sceneInfo      = info->sceneInfo;
    controllerInfo = info->controllerInfo;

    analogStickInfoL = info->stickInfoL;
#if RETRO_REV02
    analogStickInfoR = info->stickInfoR;
    triggerInfoL     = info->triggerInfoL;
    triggerInfoR     = info->triggerInfoR;
#endif
    touchInfo = info->touchInfo;

#if RETRO_REV02
    unknownInfo = info->unknownInfo;
#endif
    screenInfo = info->screenInfo;

#if RETRO_USE_MOD_LOADER
    modTable = info->modFunctionTable;
#endif
}

}; // namespace RSDK

#if GAME_CUSTOMLINKLOGIC
// DEFINE THIS YOURSELF!!!!
// This runs after LinkGameLogicDLL registers objects
void LinkGameLogic(RSDK::EngineInfo *info);
#endif