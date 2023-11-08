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
inline void ClearPrerollErrors() { APITable->ClearPrerollErrors(); }
inline void TryAuth() { APITable->TryAuth(); }
inline int32 GetUserAuthStatus() { return APITable->GetUserAuthStatus(); }
inline bool32 GetUsername(String *userName) { return APITable->GetUsername(userName); }
} // namespace Auth
#endif

namespace Storage
{

// load user file from game dir
inline bool32 LoadFile(const char *fileName, void *buffer, uint32 size) { return RSDKTable->LoadUserFile(fileName, buffer, size); }
inline bool32 SaveFile(const char *fileName, void *buffer, uint32 size) { return RSDKTable->SaveUserFile(fileName, buffer, size); }

#if RETRO_REV02
// load user file from user dir (e.g. cloud saves or etc)
inline void LoadUserFile(const char *fileName, void *buffer, uint32 size, void (*callback)(int32 status))
{
    APITable->LoadUserFile(fileName, buffer, size, callback);
}
inline void SaveUserFile(const char *fileName, void *buffer, uint32 size, void (*callback)(int32 status), bool32 compressed)
{
    APITable->SaveUserFile(fileName, buffer, size, callback, compressed);
}
inline void DeleteUserFile(const char *fileName, void (*callback)(int32 status)) { APITable->DeleteUserFile(fileName, callback); }

// Storage
inline void TryInitStorage() { APITable->TryInitStorage(); }
inline int32 GetStorageStatus() { return APITable->GetStorageStatus(); }
inline int32 GetSaveStatus() { return APITable->GetSaveStatus(); }
inline void ClearSaveStatus() { APITable->ClearSaveStatus(); }
inline void SetSaveStatusContinue() { APITable->SetSaveStatusContinue(); }
inline void SetSaveStatusOK() { APITable->SetSaveStatusOK(); }
inline void SetSaveStatusForbidden() { APITable->SetSaveStatusForbidden(); }
inline void SetSaveStatusError() { APITable->SetSaveStatusError(); }
inline void SetNoSave(bool32 noSave) { APITable->SetNoSave(noSave); }
inline bool32 GetNoSave() { return APITable->GetNoSave(); }

struct UserDB {
    UserDB() {}

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
    inline void Init() { id = (uint16)-1; }
    template <class... Args> inline void Init(const char *name, Args... args) { id = APITable->InitUserDB(name, args...); }
    inline void Load(const char *filename, void (*callback)(int32 status)) { id = APITable->LoadUserDB(filename, callback); }
    inline void Save(void (*callback)(int32 status)) { APITable->SaveUserDB(id, callback); }
    inline void Clear() { APITable->ClearUserDB(id); }
    static inline void ClearAll() { APITable->ClearAllUserDBs(); }
    inline bool32 Loaded() { return id != (uint16)-1; }

    inline bool32 Matches(UserDB &other) { return this->id == other.id; }
    inline bool32 Matches(UserDB *other)
    {
        if (other)
            return this->id == other->id;
        else
            return this->id == (uint16)-1;
    }

    // Sorting
    inline void SetupSorting() { APITable->SetupUserDBRowSorting(id); }
    inline void Sort(int32 type, const char *name, bool32 sortAscending) { APITable->SortDBRows(id, type, name, sortAscending); }
    inline bool32 RowsChanged() { return APITable->GetUserDBRowsChanged(id); }
    inline void AddSortFilter(VarTypes type, const char *name, void *value) { APITable->AddRowSortFilter(id, type, name, value); }
    inline int32 SortedRowCount() { return APITable->GetSortedUserDBRowCount(id); }
    inline int32 GetSortedRowID(uint16 row) { return APITable->GetSortedUserDBRowID(id, row); }

    // Rows
    inline int32 AddRow() { return APITable->AddUserDBRow(id); }
    inline void RemoveRow(uint16 row) { APITable->RemoveDBRow(id, row); }
    inline void RemoveAllRows(uint16 row) { APITable->RemoveAllDBRows(id); }
    inline uint32 GetRowUUID(uint16 row) { return APITable->GetUserDBRowUUID(id, row); }
    inline int32 GetRowByID(uint32 uuid) { return APITable->GetUserDBRowByID(id, uuid); }
    inline void GetRowCreationTime(uint16 row, char *buffer, uint32 bufferSize, const char *format)
    {
        APITable->GetUserDBRowCreationTime(id, row, buffer, bufferSize, format);
    }

    // Values
    inline void SetValue(int32 row, VarTypes type, const char *name, void *value) { APITable->SetUserDBValue(id, row, type, name, value); }
    inline void GetValue(int32 row, VarTypes type, const char *name, void *value) { APITable->GetUserDBValue(id, row, type, name, value); }
};

#endif

} // namespace Storage
} // namespace API
} // namespace RSDK