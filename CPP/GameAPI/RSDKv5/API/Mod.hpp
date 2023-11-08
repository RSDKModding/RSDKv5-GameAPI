#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

#if RETRO_USE_MOD_LOADER

namespace RSDK
{

struct ModVersionInfo {
    uint8 engineVer;
    uint8 gameVer;
    uint8 modLoaderVer;
};

enum ModCallbackEvents {
    MODCB_ONGAMESTARTUP,
    MODCB_ONSTATICLOAD,
    MODCB_ONSTAGELOAD,
    MODCB_ONUPDATE,
    MODCB_ONLATEUPDATE,
    MODCB_ONSTATICUPDATE,
    MODCB_ONDRAW,
    MODCB_ONSTAGEUNLOAD,
    MODCB_ONSHADERLOAD,
    MODCB_ONVIDEOSKIPCB,
    MODCB_ONSCANLINECB,
};

enum ModSuper {
    SUPER_UPDATE,
    SUPER_LATEUPDATE,
    SUPER_STATICUPDATE,
    SUPER_DRAW,
    SUPER_CREATE,
    SUPER_STAGELOAD,
    SUPER_EDITORDRAW,
    SUPER_EDITORLOAD,
    SUPER_SERIALIZE
};

namespace Mod
{

// Mod Callbacks & Public Functions
inline void AddModCallback(int32 callbackID, void (*callback)(void *)) { modTable->AddModCallback(callbackID, callback); }
inline void AddPublicFunction(const char *functionName, void *functionPtr) { modTable->AddPublicFunction(functionName, functionPtr); }
inline void *GetPublicFunction(const char *id, const char *functionName) { return modTable->GetPublicFunction(id, functionName); }

// Shaders
inline void LoadShader(const char *shaderName, bool32 linear) { modTable->LoadShader(shaderName, linear); }

// Misc
inline void *GetGlobals() { return modTable->GetGlobals(); }

namespace List
{
// Mod Info
inline bool32 LoadModInfo(const char *id, String *name, String *description, String *version, bool32 *active)
{
    return modTable->LoadModInfo(id, name, description, version, active);
}
inline void GetModPath(const char *id, String *result) { modTable->GetModPath(id, result); }
inline int32 GetModCount(bool32 active = false) { return modTable->GetModCount(active); }
inline const char *GetModIDByIndex(uint32 index) { return modTable->GetModIDByIndex(index); }

} // namespace List

namespace Achievements
{
inline void Register(const char *identifier, const char *name, const char *desc) { modTable->RegisterAchievement(identifier, name, desc); }
inline void GetInfo(uint32 id, String *name, String *description, String *identifier, bool32 *achieved)
{
    modTable->GetAchievementInfo(id, name, description, identifier, achieved);
}
inline int32 GetIndexByID(const char *identifier) { return modTable->GetAchievementIndexByID(identifier); }
inline int32 GetCount() { return modTable->GetAchievementCount(); }
} // namespace Achievements

namespace Settings
{
inline bool32 GetBool(const char *id, const char *key, bool32 fallback) { return modTable->GetSettingsBool(id, key, fallback); }
inline int32 GetInteger(const char *id, const char *key, int32 fallback) { return modTable->GetSettingsInteger(id, key, fallback); }
inline float GetFloat(const char *id, const char *key, float fallback) { return modTable->GetSettingsFloat(id, key, fallback); }
inline void GetString(const char *id, const char *key, String *result, const char *fallback)
{
    modTable->GetSettingsString(id, key, result, fallback);
}

inline void SetBool(const char *key, bool32 val) { modTable->SetSettingsBool(key, val); }
inline void SetInteger(const char *key, int32 val) { modTable->SetSettingsInteger(key, val); }
inline void SetFloat(const char *key, float val) { modTable->SetSettingsFloat(key, val); }
inline void SetString(const char *key, String *val) { modTable->SetSettingsString(key, val); }

inline void SaveSettings() { modTable->SaveSettings(); }
} // namespace Settings

namespace Config
{
inline bool32 GetBool(const char *key, bool32 fallback) { return modTable->GetConfigBool(key, fallback); }
inline int32 GetInteger(const char *key, int32 fallback) { return modTable->GetConfigInteger(key, fallback); }
inline float GetFloat(const char *key, float fallback) { return modTable->GetConfigFloat(key, fallback); }
inline void GetString(const char *key, String *result, const char *fallback) { modTable->GetConfigString(key, result, fallback); }

} // namespace Config

#if RETRO_MOD_LOADER_VER >= 2
namespace Files
{
inline bool32 ExcludeFile(const char *id, const char *path) { return modTable->ExcludeFile(id, path); }
inline bool32 ExcludeAllFiles(const char *id) { return modTable->ExcludeAllFiles(id); }
inline bool32 ReloadFile(const char *id, const char *path) { return modTable->ReloadFile(id, path); }
inline bool32 ReloadAllFiles(const char *id) { return modTable->ReloadAllFiles(id); }
} // namespace Files

namespace Engine
{
inline void *GetSpriteAnimation(uint16 id) { return modTable->GetSpriteAnimation(id); }
inline void *GetSpriteSurface(uint16 id) { return modTable->GetSpriteSurface(id); }
inline uint16 *GetPaletteBank(uint8 id) { return modTable->GetPaletteBank(id); }
inline uint8 *GetActivePaletteBuffer() { return modTable->GetActivePaletteBuffer(); }
inline void GetRGB32To16Buffer(uint16 **rgb32To16_R, uint16 **rgb32To16_G, uint16 **rgb32To16_B)
{
    modTable->GetRGB32To16Buffer(rgb32To16_R, rgb32To16_G, rgb32To16_B);
}
inline uint16 *GetBlendLookupTable() { return modTable->GetBlendLookupTable(); }
inline uint16 *GetSubtractLookupTable() { return modTable->GetSubtractLookupTable(); }
inline uint16 *GetTintLookupTable() { return modTable->GetTintLookupTable(); }
inline color GetMaskColor() { return modTable->GetMaskColor(); }
inline void *GetScanEdgeBuffer() { return modTable->GetScanEdgeBuffer(); }
inline void *GetCamera(uint8 id) { return modTable->GetCamera(id); }
inline void *GetShader(uint8 id) { return modTable->GetShader(id); }
inline void *GetModel(uint16 id) { return modTable->GetModel(id); }
inline void *GetScene3D(uint16 id) { return modTable->GetScene3D(id); }
inline void *GetSfx(uint16 id) { return modTable->GetSfx(id); }
inline void *GetChannel(uint8 id) { return modTable->GetChannel(id); }

} // namespace Engine
#endif

inline void RegisterStateHook(void (*state)(), bool32 (*hook)(bool32 skippedState), bool32 priority)
{
    modTable->RegisterStateHook(state, hook, priority);
}

extern const char *modID;

} // namespace Mod

} // namespace RSDK

#endif