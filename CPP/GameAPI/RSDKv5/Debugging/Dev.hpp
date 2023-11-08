#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"
#include "../Game/Collision.hpp"
#include <cstdarg>

#define vsprintf_s(x, y, z) vsprintf(x, y, z)

#if defined _WIN32
#undef vsprintf_s
#endif

namespace RSDK
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
inline void PrintString(PrintModes severity, String *string) { RSDKTable->PrintString(severity, string); }
inline void PrintUInt32(PrintModes severity, const char *message, uint32 integer) { RSDKTable->PrintUInt32(severity, message, integer); }
inline void PrintInt32(PrintModes severity, const char *message, int32 integer) { RSDKTable->PrintInt32(severity, message, integer); }
inline void PrintFloat(PrintModes severity, const char *message, float f) { RSDKTable->PrintFloat(severity, message, f); }
inline void PrintVector2(PrintModes severity, const char *message, int32 x, int32 y) { RSDKTable->PrintVector2(severity, message, Vector2(x, y)); }
inline void PrintVector2(PrintModes severity, const char *message, Vector2 *vec) { RSDKTable->PrintVector2(severity, message, *vec); }
inline void PrintVector2(PrintModes severity, const char *message, Vector2 vec) { RSDKTable->PrintVector2(severity, message, vec); }
inline void PrintHitbox(PrintModes severity, const char *message, Hitbox *hitbox) { RSDKTable->PrintHitbox(severity, message, *hitbox); }
inline void PrintHitbox(PrintModes severity, const char *message, Hitbox hitbox) { RSDKTable->PrintHitbox(severity, message, hitbox); }

inline void ClearViewableVariables() { RSDKTable->ClearViewableVariables(); }
inline void AddViewableVariable(const char *name, void *value, ViewableVarTypes type, int32 min, int32 max)
{
    RSDKTable->AddViewableVariable(name, value, type, min, max);
}
#else
inline void Print(PrintModes severity, const char *message, ...)
{
    char buffer[0x100];
    va_list args;
    va_start(args, message);
    vsprintf_s(buffer, message, args);
    RSDKTable->PrintMessage(buffer, MESSAGE_STRING);
};
#endif

} // namespace Dev

} // namespace RSDK