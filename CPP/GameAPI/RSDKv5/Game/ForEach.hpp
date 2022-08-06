#pragma once

#include "Types.hpp"
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

    String string;
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

namespace Config
{

inline std::list<String> Get()
{
    std::list<String> list;

    String string;
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

    String string;
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