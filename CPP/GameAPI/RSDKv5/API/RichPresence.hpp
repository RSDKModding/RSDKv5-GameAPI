#pragma once

namespace RSDK
{

#if RETRO_REV02

namespace API
{
namespace RichPresence
{
inline void Set(int32 id, String *text) { APITable->SetRichPresence(id, text); }
} // namespace RichPresence
} // namespace API

#endif

} // namespace RSDK