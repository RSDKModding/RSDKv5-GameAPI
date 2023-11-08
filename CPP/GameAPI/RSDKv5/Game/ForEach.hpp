#pragma once

#include "../Essentials/String.hpp"
#include <list>

#if RETRO_USE_MOD_LOADER

namespace RSDK
{

namespace Mod
{

namespace List
{

inline std::list<String> GetIDs()
{
    std::list<String> list;

    String string{};
    while (modTable->ForeachModID(&string)) {
        String copy;
        copy.chars  = string.chars;
        copy.length = string.length;
        copy.size   = string.size;

        list.push_back(copy);
    }

    return list;
}

} // namespace List

#if RETRO_MOD_LOADER_VER >= 2
namespace Settings
{

inline std::list<String> Get(const char *id)
{
    std::list<String> list;

    String string{};
    while (modTable->ForeachSetting(id, &string)) {
        String copy;
        copy.chars  = string.chars;
        copy.length = string.length;
        copy.size   = string.size;

        list.push_back(copy);
    }

    return list;
}

inline std::list<String> GetCategories(const char *id)
{
    std::list<String> list;

    String string{};
    while (modTable->ForeachSettingCategory(id, &string)) {
        String copy;
        copy.chars  = string.chars;
        copy.length = string.length;
        copy.size   = string.size;

        list.push_back(copy);
    }

    return list;
}
} // namespace Settings
#endif

namespace Config
{

inline std::list<String> Get()
{
    std::list<String> list;

    String string{};
    while (modTable->ForeachConfig(&string)) {
        String copy;
        copy.chars  = string.chars;
        copy.length = string.length;
        copy.size   = string.size;

        list.push_back(copy);
    }

    return list;
}

inline std::list<String> GetCategories()
{
    std::list<String> list;

    String string{};
    while (modTable->ForeachConfigCategory(&string)) {
        String copy;
        copy.chars  = string.chars;
        copy.length = string.length;
        copy.size   = string.size;

        list.push_back(copy);
    }

    return list;
}
} // namespace Config

} // namespace Mod

} // namespace RSDK

#endif