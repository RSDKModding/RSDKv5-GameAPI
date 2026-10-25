#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

namespace GameAPI::RSDK
{
#if RETRO_USE_MOD_LOADER && RETRO_MOD_LOADER_VER >= 3
namespace IO
{
enum IOSeekWhence {
    IOSEEK_SET = 0, /* Seek from beginning of file. */
    IOSEEK_CUR = 1, /* Seek from current position. */
    IOSEEK_END = 2  /* Seek from end of file. */
};

RSDK_FORCE_INLINE IOHandle Open(const char *filename, const char *mode) {
    return modTable->IOOpen(filename, mode);
}

RSDK_FORCE_INLINE uint32 Read(void *buffer, uint32 elementSize, uint32 elementCount, IOHandle file) {
    return modTable->IORead(buffer, elementSize, elementCount, file);
}

RSDK_FORCE_INLINE int32 Seek(IOHandle file, int32 offset, int32 whence) {
    return modTable->IOSeek(file, offset, whence);
}

RSDK_FORCE_INLINE int32 Tell(IOHandle file) {
    return modTable->IOTell(file);
}

RSDK_FORCE_INLINE int32 Close(IOHandle file) {
    return modTable->IOClose(file);
}

RSDK_FORCE_INLINE uint32 Write(const void *buffer, uint32 elementSize, uint32 elementCount, IOHandle file) {
    return modTable->IOWrite(buffer, elementSize, elementCount, file);
}

} // namespace IO
#endif

} // namespace GameAPI::RSDK