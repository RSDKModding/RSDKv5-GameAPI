#pragma once

#include "../Types.hpp"
#include "../Essentials/String.hpp"

namespace RSDK
{

#if RETRO_REV02
enum LeaderboardLoadTypes {
    LEADERBOARD_LOAD_INIT,
    LEADERBOARD_LOAD_PREV,
    LEADERBOARD_LOAD_NEXT,
};

struct LeaderboardID {
    int32 idPS4;        // leaderboard id (PS4)
    int32 idUnknown;    // leaderboard id (unknown platform)
    int32 idSwitch;     // leaderboard id (switch)
    const char *idXbox; // Xbox One Leaderboard id (making an assumption based on the MS docs)
    const char *idPC;   // Leaderboard id (as a string, used for PC platforms)
};

struct LeaderboardAvail {
    int32 start;
    int32 length;
};

struct LeaderboardEntry {
    String username;
    String userID;
    int32 globalRank;
    int32 score;
    bool32 isUser;
    int32 status;
};

namespace API
{
namespace Leaderboards
{

#if RETRO_USE_EGS
inline bool32 CheckEnabled() { return APITable->CheckLeaderboardsEnabled(); }
#endif
inline void Init() { APITable->InitLeaderboards(); }
inline void Fetch(LeaderboardID *leaderboard, bool32 isUser) { APITable->FetchLeaderboard(leaderboard, isUser); }
inline void TrackScore(LeaderboardID *leaderboard, int32 score, void (*callback)(bool32 success, int32 rank))
{
    APITable->TrackScore(leaderboard, score, callback);
}
inline int32 GetStatus() { return APITable->GetLeaderboardsStatus(); }
inline LeaderboardAvail EntryViewSize() { return APITable->LeaderboardEntryViewSize(); }
inline LeaderboardAvail EntryLoadSize() { return APITable->LeaderboardEntryLoadSize(); }
inline void LoadEntries(int32 start, uint32 end, int32 type) { APITable->LoadLeaderboardEntries(start, end, type); }
inline void ResetInfo() { APITable->ResetLeaderboardInfo(); }
inline LeaderboardEntry *ReadEntry(uint32 entryID) { return APITable->ReadLeaderboardEntry(entryID); }

} // namespace Leaderboards
} // namespace API

#endif

} // namespace RSDK
