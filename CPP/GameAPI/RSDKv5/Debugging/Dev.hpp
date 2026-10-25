#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"
#include "../Game/Collision.hpp"
#include <cstdarg>

#define vsprintf_s(x, y, z) vsprintf(x, y, z)

#if defined _WIN32
#undef vsprintf_s
#endif

namespace GameAPI::RSDK
{

namespace Dev
{

#if RETRO_REV02
enum ViewableVarTypes {
    VIEWVAR_INVALID,
    VIEWVAR_BOOL,
    VIEWVAR_UINT8,
    VIEWVAR_UINT16,
    VIEWVAR_UINT32,
    VIEWVAR_INT8,
    VIEWVAR_INT16,
    VIEWVAR_INT32,
};

typedef enum {
    PRINT_NORMAL,
    PRINT_POPUP,
    PRINT_ERROR,
    PRINT_FATAL,
#if RETRO_REV0U
    PRINT_SCRIPTERR,
#endif
} PrintModes;
#else
typedef enum {
    MESSAGE_STRING,
    MESSAGE_INT32,
    MESSAGE_UINT32,
    MESSAGE_FLOAT,
} PrintMessageTypes;
#endif

#if RETRO_REV02
inline void Print(PrintModes severity, const char *message, ...)
{
    char buffer[0x100];
    va_list args;
    va_start(args, message);
    vsprintf_s(buffer, message, args);
    RSDKTable->PrintLog(severity, buffer);
};
RSDK_FORCE_INLINE void PrintText(PrintModes severity, const char *message) { RSDKTable->PrintText(severity, message); }
RSDK_FORCE_INLINE void PrintString(PrintModes severity, String *string) { RSDKTable->PrintString(severity, string); }
RSDK_FORCE_INLINE void PrintUInt32(PrintModes severity, const char *message, uint32 integer) { RSDKTable->PrintUInt32(severity, message, integer); }
RSDK_FORCE_INLINE void PrintInt32(PrintModes severity, const char *message, int32 integer) { RSDKTable->PrintInt32(severity, message, integer); }
RSDK_FORCE_INLINE void PrintFloat(PrintModes severity, const char *message, float f) { RSDKTable->PrintFloat(severity, message, f); }
RSDK_FORCE_INLINE void PrintVector2(PrintModes severity, const char *message, int32 x, int32 y) { RSDKTable->PrintVector2(severity, message, Vector2(x, y)); }
RSDK_FORCE_INLINE void PrintVector2(PrintModes severity, const char *message, Vector2 *vec) { RSDKTable->PrintVector2(severity, message, *vec); }
RSDK_FORCE_INLINE void PrintVector2(PrintModes severity, const char *message, Vector2 vec) { RSDKTable->PrintVector2(severity, message, vec); }
RSDK_FORCE_INLINE void PrintHitbox(PrintModes severity, const char *message, Hitbox *hitbox) { RSDKTable->PrintHitbox(severity, message, *hitbox); }
RSDK_FORCE_INLINE void PrintHitbox(PrintModes severity, const char *message, Hitbox hitbox) { RSDKTable->PrintHitbox(severity, message, hitbox); }

RSDK_FORCE_INLINE void ClearViewableVariables() { RSDKTable->ClearViewableVariables(); }
RSDK_FORCE_INLINE void AddViewableVariable(const char *name, void *value, ViewableVarTypes type, int32 min, int32 max)
{
    RSDKTable->AddViewableVariable(name, value, type, min, max);
}

RSDK_FORCE_INLINE void AddViewableVariable(const char *name, bool32 *value) { AddViewableVariable(name, value, VIEWVAR_BOOL, 0, 1); }
RSDK_FORCE_INLINE void AddViewableVariable(const char *name, uint8 *value, int32 min, int32 max) { AddViewableVariable(name, value, VIEWVAR_UINT8, min, max); }
RSDK_FORCE_INLINE void AddViewableVariable(const char *name, uint16 *value, int32 min, int32 max) { AddViewableVariable(name, value, VIEWVAR_UINT16, min, max); }
RSDK_FORCE_INLINE void AddViewableVariable(const char *name, uint32 *value, int32 min, int32 max) { AddViewableVariable(name, value, VIEWVAR_UINT32, min, max); }
RSDK_FORCE_INLINE void AddViewableVariable(const char *name, int8 *value, int32 min, int32 max) { AddViewableVariable(name, value, VIEWVAR_INT8, min, max); }
RSDK_FORCE_INLINE void AddViewableVariable(const char *name, int16 *value, int32 min, int32 max) { AddViewableVariable(name, value, VIEWVAR_INT16, min, max); }
RSDK_FORCE_INLINE void AddViewableVariable(const char *name, int32 *value, int32 min, int32 max) { AddViewableVariable(name, value, VIEWVAR_INT32, min, max); }
#else
RSDK_FORCE_INLINE void Print(void *msg, uint8 type) { RSDKTable->PrintMessage(msg, type); };
#endif

#if RETRO_USE_MOD_LOADER && RETRO_MOD_LOADER_VER >= 3
RSDK_FORCE_INLINE void AddDevMenuCharacter(const char *playerName, int32 id) { modTable->AddDevMenuCharacter(playerName, id); }
RSDK_FORCE_INLINE int32 GetActiveDevMenuCharacter(void) { return modTable->GetActiveDevMenuCharacter(); }
#endif

} // namespace Dev

} // namespace GameAPI::RSDK