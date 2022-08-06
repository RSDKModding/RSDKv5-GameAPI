#pragma once

#include "Types.hpp"

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

inline void Settings() { modTable->SaveSettings(); }
} // namespace Settings

namespace Config
{
inline bool32 GetBool(const char *key, bool32 fallback) { return modTable->GetConfigBool(key, fallback); }
inline int32 GetInteger(const char *key, int32 fallback) { return modTable->GetConfigInteger(key, fallback); }
inline float GetFloat(const char *key, float fallback) { return modTable->GetConfigFloat(key, fallback); }
inline void GetString(const char *key, String *result, const char *fallback) { modTable->GetConfigString(key, result, fallback); }

} // namespace Config

inline void RegisterStateHook(void (*state)(), bool32 (*hook)(bool32 skippedState), bool32 priority)
{
    modTable->RegisterStateHook(state, hook, priority);
}

extern const char* modID;

} // namespace Mod

} // namespace RSDK

#endif