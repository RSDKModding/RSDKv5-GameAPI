#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"
#include "../Graphics/Sprite.hpp"

namespace GameAPI::RSDK
{
struct String {
public:
    String() {}
    String(const char *str) { Init(str); }
    String(String &other) { Copy(this, &other); }
    String(String *other) { Copy(this, other); }

    String(const String &other)
    {
        chars  = other.chars;
        length = other.length;
        size   = other.size;
    }
    String(const String *other)
    {
        chars  = other->chars;
        length = other->length;
        size   = other->size;
    }

    RSDK_FORCE_INLINE bool operator==(String other) { return Compare(this, &other, true); }
    RSDK_FORCE_INLINE String &operator+=(String other)
    {
        Append(&other);
        return *this;
    }

    friend RSDK_FORCE_INLINE String operator+(String lhs, String rhs)
    {
        lhs += rhs;
        return lhs;
    }

    RSDK_FORCE_INLINE void Init(const char *str, uint32 length = 0) { RSDKTable->InitString(this, str, length); }
    RSDK_FORCE_INLINE void Set(const char *str) { RSDKTable->SetString(this, str); }

    RSDK_FORCE_INLINE void Prepend(String *str) { *this = str + *this; }
    RSDK_FORCE_INLINE void Prepend(const char *str) { *this = String(str) + *this; }

    RSDK_FORCE_INLINE void Append(String *str) { RSDKTable->AppendString(this, str); }
    RSDK_FORCE_INLINE void Append(const char *str) { RSDKTable->AppendText(this, str); }

    static RSDK_FORCE_INLINE void Copy(String *dst, String *src) { RSDKTable->CopyString(dst, src); }
    static RSDK_FORCE_INLINE void Copy(String *dst, const char *src) { RSDKTable->SetString(dst, src); }
    static bool32 Compare(String *strA, String *strB, bool32 exactMatch) { return RSDKTable->CompareStrings(strA, strB, exactMatch); }

    RSDK_FORCE_INLINE void CStr(char *buffer) { RSDKTable->GetCString(buffer, this); }

    RSDK_FORCE_INLINE bool32 Initialized() { return chars != nullptr; }
    RSDK_FORCE_INLINE bool32 Empty() { return !length; }

    RSDK_FORCE_INLINE void SetSpriteString(SpriteAnimation aniFrames, uint16 listID) { RSDKTable->SetSpriteString(aniFrames.aniFrames, listID, this); }
    RSDK_FORCE_INLINE int32 GetWidth(SpriteAnimation aniFrames, uint16 listID, int32 spacing)
    {
        return RSDKTable->GetStringWidth(aniFrames.aniFrames, listID, this, 0, length, spacing);
    }
    RSDK_FORCE_INLINE int32 GetWidth(SpriteAnimation aniFrames, uint16 listID, int32 start, int32 length, int32 spacing)
    {
        return RSDKTable->GetStringWidth(aniFrames.aniFrames, listID, this, start, length, spacing);
    }

    RSDK_FORCE_INLINE void LoadStrings(const char *filepath, uint32 charSize = 16) { RSDKTable->LoadStringList(this, filepath, charSize); }
    RSDK_FORCE_INLINE bool32 Split(String *list, int32 startID, int32 count) { return RSDKTable->SplitStringList(list, this, startID, count); }

    uint16 *chars = nullptr;
    uint16 length = 0;
    uint16 size   = 0;
};

} // namespace GameAPI::RSDK