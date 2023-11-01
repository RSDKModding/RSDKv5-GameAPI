#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

namespace RSDK
{

enum EngineStates {
    ENGINESTATE_LOAD,
    ENGINESTATE_REGULAR,
    ENGINESTATE_PAUSED,
    ENGINESTATE_FROZEN,
};

struct SceneListInfo {
    uint32 hash[4];
    char name[0x20];
    uint16 sceneOffsetStart;
    uint16 sceneOffsetEnd;
    uint8 sceneCount;
};

struct SceneListEntry {
    uint32 hash[4];
    char name[0x20];
    char folder[0x10];
    char id[0x08];
#if RETRO_REV02
    uint8 filter;
#endif
};

struct SceneInfo {
    void *entity;
    SceneListEntry *listData;
    SceneListInfo *listCategory;
    int32 timeCounter;
    int32 currentDrawGroup;
    int32 currentScreenID;
    uint16 listPos;
    uint16 entitySlot;
    uint16 createSlot;
    uint16 classCount;
    bool32 inEditor;
    bool32 effectGizmo;
    bool32 debugMode;
    bool32 useGlobalScripts;
    bool32 timeEnabled;
    uint8 activeCategory;
    uint8 categoryCount;
    uint8 state;
#if RETRO_REV02
    uint8 filter;
#endif
    uint8 milliseconds;
    uint8 seconds;
    uint8 minutes;
};

namespace Stage
{

inline bool32 CheckSceneFolder(const char *folderName) { return RSDKTable->CheckSceneFolder(folderName); }
inline bool32 CheckValidScene() { return RSDKTable->CheckValidScene(); }
inline void SetScene(const char *categoryName, const char *sceneName) { RSDKTable->SetScene(categoryName, sceneName); }
inline void LoadScene() { RSDKTable->LoadScene(); }
inline void SetEngineState(EngineStates state) { RSDKTable->SetEngineState(state); }
#if RETRO_REV02
inline void ForceHardReset(bool32 shouldHardReset) { RSDKTable->ForceHardReset(shouldHardReset); }
#endif

} // namespace Stage

} // namespace RSDK