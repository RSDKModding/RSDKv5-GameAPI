#pragma once

#include "../Types.hpp"
#include "../Graphics/Sprite.hpp"

namespace RSDK
{
struct String {
public:
    String() {}
    String(const char *str) { Init(str); }
    String(String &other) { Init(other.ToString()); }
    String(String *other) { Init(other->ToString()); }

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

    inline bool operator==(String other) { return Compare(this, &other, true); }
    inline String &operator+=(String other)
    {
        Append(&other);
        return *this;
    }

    friend inline String operator+(String lhs, String rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline void Init(const char *str, uint32 length = 0) { RSDKTable->InitString(this, str, length); }
    inline void Set(const char *str) { RSDKTable->SetString(this, str); }

    String &Prepend(String *str);
    String &Prepend(const char *str);

    String &Append(String *str);
    String &Append(const char *str);

    static inline void Copy(String *dst, String *src) { RSDKTable->CopyString(dst, src); }
    static inline void Copy(String *dst, const char *src) { RSDKTable->SetString(dst, src); }
    static bool32 Compare(String *strA, String *strB, bool32 exactMatch) { return RSDKTable->CompareStrings(strA, strB, exactMatch); }

    void CStr(char *buffer) { RSDKTable->GetCString(buffer, this); }
    const char *ToString();

    inline bool32 Initialized() { return chars != nullptr; }
    inline bool32 Empty() { return !length; }

    inline void SetSpriteString(SpriteAnimation aniFrames, uint16 listID) { RSDKTable->SetSpriteString(aniFrames.aniFrames, listID, this); }
    inline int32 GetWidth(SpriteAnimation aniFrames, uint16 listID, int32 spacing)
    {
        return RSDKTable->GetStringWidth(aniFrames.aniFrames, listID, this, 0, length, spacing);
    }
    inline int32 GetWidth(SpriteAnimation aniFrames, uint16 listID, int32 start, int32 length, int32 spacing)
    {
        return RSDKTable->GetStringWidth(aniFrames.aniFrames, listID, this, start, length, spacing);
    }

    inline void LoadStrings(const char *filepath) { RSDKTable->LoadStringList(this, filepath, 16); }
    inline bool32 Split(String *list, int32 startID, int32 count) { return RSDKTable->SplitStringList(list, this, startID, count); }

    uint16 *chars = nullptr;
    uint16 length = 0;
    uint16 size   = 0;
};

} // namespace RSDK