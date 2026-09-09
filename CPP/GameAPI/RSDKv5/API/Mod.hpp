#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"
#include "../Game/Object.hpp"
#include "../Game/Stage.hpp"

#if RETRO_USE_MOD_LOADER
#include <functional>
#include <type_traits>

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
#if RETRO_MOD_LOADER_VER >= 3
    MODCB_BEFORESTAGELOAD,
    MODCB_BEFORESTATICUPDATE,
#endif
};

enum ModSuper {
    SUPER_UPDATE,
    SUPER_LATEUPDATE,
    SUPER_STATICUPDATE,
    SUPER_DRAW,
    SUPER_CREATE,
    SUPER_STAGELOAD,
#if RETRO_REV0U
    SUPER_STATICLOAD,
#endif
    SUPER_EDITORLOAD,
    SUPER_EDITORDRAW,
    SUPER_SERIALIZE
};

#if RETRO_MOD_LOADER_VER >= 3
enum RetroPlatform {
    RETRO_WIN    = 0,
    RETRO_PS4    = 1,
    RETRO_XB1    = 2,
    RETRO_SWITCH = 3,
    // CUSTOM
    RETRO_OSX     = 4,
    RETRO_LINUX   = 5,
    RETRO_iOS     = 6,
    RETRO_ANDROID = 7,
    RETRO_UWP     = 8,
    RETRO_OTHER   = 9
};

inline int32 GetRetroPlatform(void) { return modTable->GetRetroPlatform(); }

inline void GetGameTitle(String *result) { modTable->GetGameTitle(result); }
inline void SetGameTitle(const char *name) { modTable->SetGameTitle(name); }
#endif

namespace Mod
{

// Mod Callbacks & Public Functions
inline void AddModCallback(int32 callbackID, void (*callback)(void *)) { modTable->AddModCallback(callbackID, callback); }
inline void AddModCallback(int32 callbackID, std::function<void(void *)> callback) { modTable->AddModCallback_STD(callbackID, callback); }

#if RETRO_MOD_LOADER_VER >= 3
// Entities
struct Entity {
    int32 index;

    template <class T> static typename T::ModEntity *Get(void *entity) { return Get<T>(entity, nullptr); }

    template <class T> static typename T::ModEntity *Get(void *entity, const char *modID)
    {
        return (T::ModEntity *)(modTable->GetModEntityForModID(entity, modID));
    }

    template <class T> static typename T::ModEntity *Get(void *entity, int32 modIndex)
    {
        return (T::ModEntity *)(modTable->GetModEntityForModIndex(entity, modIndex));
    }

    template <class T> struct ModImpl {
        typename T::ModEntity *operator->()
        {
            // ModImpl is technically a variable, so we're gonna have to do a bit of math to get the address of the entity
            // else, this'll end up attempting to find a ModEntity for (char *)(entity) + offsetof(T, T::mod);
            return Get<T>((char *)(this) - offsetof(T, T::mod));
        }
    };
};
#endif

namespace PublicFunctions
{
struct FunctionObject {
    const char *id;
    const char *functionName;

    template <typename T> inline operator T() const
    {
        if constexpr (std::is_member_function_pointer_v<T>) {
            union {
                void *in;
                T out;
            } u;
            u.in = modTable->GetPublicFunction(id, functionName);
            return u.out;
        }
        else {
            return reinterpret_cast<T>(modTable->GetPublicFunction(id, functionName));
        }
    }
};

template <typename obj, typename R> inline void Add(const char *functionName, R(obj::*functionPtr))
{
    modTable->AddPublicFunction(functionName, reinterpret_cast<void *&>(functionPtr));
}

template <typename R> inline void Add(const char *functionName, R(*functionPtr))
{
    modTable->AddPublicFunction(functionName, reinterpret_cast<void *&>(functionPtr));
}

inline FunctionObject Get(const char *id, const char *functionName) { return { id, functionName }; }

#if RETRO_MOD_LOADER_VER >= 3
inline void Hook(const char *id, const char *functionName, void *functionPtr, void **originalPtr)
{
    modTable->HookPublicFunction(id, functionName, functionPtr, originalPtr);
}

template <typename T> class HookContainer
{
public:
    constexpr HookContainer(const char *funcName, const char *funcModID = nullptr) : name(funcName), modID(funcModID) {}

    static void Register()
    {
        T instance = {};
        PublicFunctions::Hook(instance.modID, instance.name, reinterpret_cast<void *>(&T::Impl), reinterpret_cast<void **>(&instance.original));
    }

    template <typename... arguments> static decltype(auto) Original(arguments &&...args)
    {
        using T = decltype(&std::remove_reference_t<T>::Impl);
        return reinterpret_cast<T>(original)(std::forward<arguments>(args)...);
    }

protected:
    const char *modID;
    const char *name;
    inline static void *original = nullptr;
};
#endif
} // namespace PublicFunctions

// Shaders
inline void LoadShader(const char *shaderName, bool32 linear) { modTable->LoadShader(shaderName, linear); }

// Misc
template <typename T> inline T *GetGlobals() { return (T *)modTable->GetGlobals(); }

#if RETRO_MOD_LOADER_VER >= 3
inline void OpenModMenu() { modTable->OpenModMenu(); }
#endif

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
#if RETRO_MOD_LOADER_VER >= 3
inline bool32 FileExists(const char *path) { return modTable->FileExists(path); }
#endif
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

template <typename> struct function_info;
template <typename T, typename returning, typename... Args> struct function_info<returning (T::*)(Args...)> {
    using object_type = T;
};

template <auto hook, typename T> void RegisterStateHook(void (T::*state)(), bool32 priority)
{
    union {
        void (T::*in)();
        void (*out)();
    } u;
    u.in = state;

    if constexpr (std::is_member_function_pointer_v<decltype(hook)>)
        modTable->RegisterStateHook(u.out, +[](bool32 skippedState) -> bool32 { return ((T *)sceneInfo->entity->*hook)(skippedState); }, priority);
    else
        modTable->RegisterStateHook(u.out, hook, priority);
}

template <auto hook> void RegisterStateHook(void (*state)(), bool32 priority)
{
    using T = typename function_info<decltype(hook)>::object_type;

    if constexpr (std::is_member_function_pointer_v<decltype(hook)>)
        modTable->RegisterStateHook(state, +[](bool32 skippedState) -> bool32 { return ((T *)sceneInfo->entity->*hook)(skippedState); }, priority);
    else
        modTable->RegisterStateHook(state, hook, priority);
}

inline void RegisterStateHook(void (*state)(), bool32 (*hook)(bool32 skippedState), bool32 priority)
{
    modTable->RegisterStateHook(state, hook, priority);
}

extern const char *modID;

} // namespace Mod

} // namespace RSDK

#if RETRO_MOD_LOADER_VER >= 3
// Declare a generic hook
#define DECLARE_PUBLIC_FUNC_HOOK(modID, name, type, returnType, ...)                                                                                 \
    struct type : RSDK::Mod::PublicFunctions::HookContainer<type> {                                                                                  \
        type() : HookContainer(name, modID) {}                                                                                                       \
        static returnType Impl(__VA_ARGS__);                                                                                                         \
    };

// Declare a generic hook, hook into the current game's public functions
#define DECLARE_GAME_FUNC_HOOK(name, type, returnType, ...) DECLARE_PUBLIC_FUNC_HOOK(nullptr, name, type, returnType, __VA_ARGS__)

// Declare a generic hook, hook into other mods' public functions by ID
#define DECLARE_MOD_FUNC_HOOK(modID, name, type, returnType, ...) DECLARE_PUBLIC_FUNC_HOOK(modID, name, type, returnType, __VA_ARGS__)

// Define a generic hook
#define DEFINE_PUBLIC_FUNC_HOOK(name, returnType, ...) returnType name::Impl(__VA_ARGS__)

// Register a defined hook of the same name
#define REGISTER_FUNC_HOOK(name) name::Register()

#endif // !RETRO_MOD_LOADER_VER

#endif