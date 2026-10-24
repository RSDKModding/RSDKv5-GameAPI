#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

namespace RSDK
{
namespace API
{

#if RETRO_REV02
namespace Auth
{

// Authorization
RSDK_FORCE_INLINE void ClearPrerollErrors() { APITable->ClearPrerollErrors(); }
RSDK_FORCE_INLINE void TryAuth() { APITable->TryAuth(); }
RSDK_FORCE_INLINE int32 GetUserAuthStatus() { return APITable->GetUserAuthStatus(); }
RSDK_FORCE_INLINE bool32 GetUsername(String *userName) { return APITable->GetUsername(userName); }
} // namespace Auth
#endif

namespace Storage
{

// load user file from game dir
RSDK_FORCE_INLINE bool32 LoadFile(const char *fileName, void *buffer, uint32 size) { return RSDKTable->LoadUserFile(fileName, buffer, size); }
RSDK_FORCE_INLINE bool32 SaveFile(const char *fileName, void *buffer, uint32 size) { return RSDKTable->SaveUserFile(fileName, buffer, size); }

#if RETRO_REV02
// load user file from user dir (e.g. cloud saves or etc)
RSDK_FORCE_INLINE void LoadUserFile(const char *fileName, void *buffer, uint32 size, void (*callback)(int32 status))
{
    APITable->LoadUserFile(fileName, buffer, size, callback);
}
RSDK_FORCE_INLINE void SaveUserFile(const char *fileName, void *buffer, uint32 size, void (*callback)(int32 status), bool32 compressed)
{
    APITable->SaveUserFile(fileName, buffer, size, callback, compressed);
}
RSDK_FORCE_INLINE void DeleteUserFile(const char *fileName, void (*callback)(int32 status)) { APITable->DeleteUserFile(fileName, callback); }

// Storage
RSDK_FORCE_INLINE void TryInitStorage() { APITable->TryInitStorage(); }
RSDK_FORCE_INLINE int32 GetStorageStatus() { return APITable->GetStorageStatus(); }
RSDK_FORCE_INLINE int32 GetSaveStatus() { return APITable->GetSaveStatus(); }
RSDK_FORCE_INLINE void ClearSaveStatus() { APITable->ClearSaveStatus(); }
RSDK_FORCE_INLINE void SetSaveStatusContinue() { APITable->SetSaveStatusContinue(); }
RSDK_FORCE_INLINE void SetSaveStatusOK() { APITable->SetSaveStatusOK(); }
RSDK_FORCE_INLINE void SetSaveStatusForbidden() { APITable->SetSaveStatusForbidden(); }
RSDK_FORCE_INLINE void SetSaveStatusError() { APITable->SetSaveStatusError(); }
RSDK_FORCE_INLINE void SetNoSave(bool32 noSave) { APITable->SetNoSave(noSave); }
RSDK_FORCE_INLINE bool32 GetNoSave() { return APITable->GetNoSave(); }

struct UserDB {
    UserDB() : id(0xFFFF) {}

    enum VarTypes {
        Unknown,
        Bool,
        UInt8,
        UInt16,
        UInt32,
        UInt64, // unimplemented in RSDKv5
        Int8,
        Int16,
        Int32,
        Int64, // unimplemented in RSDKv5
        Float,
        Double,  // unimplemented in RSDKv5
        Vector2, // unimplemented in RSDKv5
        Vector3, // unimplemented in RSDKv5
        Vector4, // unimplemented in RSDKv5
        Color,
        String,
        HashMD5, // unimplemented in RSDKv5
    };

    uint16 id;

    // Management
    RSDK_FORCE_INLINE void Init() { id = (uint16)-1; }
    template <class... Args> RSDK_FORCE_INLINE void Init(const char *name, Args... args) { id = APITable->InitUserDB(name, args...); }
    RSDK_FORCE_INLINE void Load(const char *filename, void (*callback)(int32 status)) { id = APITable->LoadUserDB(filename, callback); }
    RSDK_FORCE_INLINE void Save(void (*callback)(int32 status)) { APITable->SaveUserDB(id, callback); }
    RSDK_FORCE_INLINE void Clear() { APITable->ClearUserDB(id); }
    static RSDK_FORCE_INLINE void ClearAll() { APITable->ClearAllUserDBs(); }
    RSDK_FORCE_INLINE bool32 Loaded() { return id != (uint16)-1; }

    RSDK_FORCE_INLINE bool32 Matches(UserDB &other) { return this->id == other.id; }
    RSDK_FORCE_INLINE bool32 Matches(UserDB *other)
    {
        if (other)
            return this->id == other->id;
        else
            return this->id == (uint16)-1;
    }

    // Sorting
    RSDK_FORCE_INLINE void SetupSorting() { APITable->SetupUserDBRowSorting(id); }
    RSDK_FORCE_INLINE void Sort(int32 type, const char *name, bool32 sortAscending) { APITable->SortDBRows(id, type, name, sortAscending); }
    RSDK_FORCE_INLINE bool32 RowsChanged() { return APITable->GetUserDBRowsChanged(id); }
    RSDK_FORCE_INLINE void AddSortFilter(VarTypes type, const char *name, void *value) { APITable->AddRowSortFilter(id, type, name, value); }
    RSDK_FORCE_INLINE int32 SortedRowCount() { return APITable->GetSortedUserDBRowCount(id); }
    RSDK_FORCE_INLINE int32 GetSortedRowID(uint16 row) { return APITable->GetSortedUserDBRowID(id, row); }

    // Rows
    RSDK_FORCE_INLINE int32 AddRow() { return APITable->AddUserDBRow(id); }
    RSDK_FORCE_INLINE void RemoveRow(uint16 row) { APITable->RemoveDBRow(id, row); }
    RSDK_FORCE_INLINE void RemoveAllRows(uint16 row) { APITable->RemoveAllDBRows(id); }
    RSDK_FORCE_INLINE uint32 GetRowUUID(uint16 row) { return APITable->GetUserDBRowUUID(id, row); }
    RSDK_FORCE_INLINE int32 GetRowByID(uint32 uuid) { return APITable->GetUserDBRowByID(id, uuid); }
    RSDK_FORCE_INLINE void GetRowCreationTime(uint16 row, char *buffer, uint32 bufferSize, const char *format)
    {
        APITable->GetUserDBRowCreationTime(id, row, buffer, bufferSize, format);
    }

    // Values
    RSDK_FORCE_INLINE void SetValue(int32 row, VarTypes type, const char *name, void *value) { APITable->SetUserDBValue(id, row, type, name, value); }
    RSDK_FORCE_INLINE void GetValue(int32 row, VarTypes type, const char *name, void *value) { APITable->GetUserDBValue(id, row, type, name, value); }
};

#endif

} // namespace Storage
} // namespace API
} // namespace RSDK