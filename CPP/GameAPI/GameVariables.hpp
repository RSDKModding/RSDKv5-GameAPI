#ifndef GAME_VARIABLES_H
#define GAME_VARIABLES_H

// =========================
// GAME ENUMS
// =========================

#define PLAYER_COUNT (4)

enum GameModes {
    MODE_MANIA,
    MODE_ENCORE,
    MODE_TIMEATTACK,
    MODE_COMPETITION,
};

#define isMainGameMode() (globals->gameMode == MODE_MANIA || globals->gameMode == MODE_ENCORE)

enum PlayerIDs {
    ID_NONE     = 0 << 0,
    ID_SONIC    = 1 << 0,
    ID_TAILS    = 1 << 1,
    ID_KNUCKLES = 1 << 2,
    // #if MANIA_USE_PLUS
    ID_MIGHTY = 1 << 3,
    ID_RAY    = 1 << 4,
    // #endif

    ID_TAILS_ASSIST    = ID_TAILS << 8,
    ID_KNUCKLES_ASSIST = ID_KNUCKLES << 8, // custom-added, can be used to check if "& knux" is active
    ID_DEFAULT_PLAYER  = ID_SONIC | ID_TAILS_ASSIST,
};

#define GET_CHARACTER_ID(playerNum)            (((globals->playerID >> (8 * ((playerNum)-1))) & 0xFF))
#define CHECK_CHARACTER_ID(characterID, plrID) (((globals->playerID >> (8 * ((plrID)-1))) & 0xFF) == (characterID))

// #if MANIA_USE_PLUS
#define GET_STOCK_ID(stockNum)                (((globals->stock >> (8 * ((stockNum)-1))) & 0xFF))
#define CHECK_STOCK_ID(characterID, stockNum) (((globals->stock >> (8 * ((stockNum)-1))) & 0xFF) == (characterID))
// #endif

enum ItemModes { ITEMS_FIXED, ITEMS_RANDOM, ITEMS_TELEPORT };

enum MedalMods {
    MEDAL_DEBUGMODE   = 1 << 0,
    MEDAL_ANDKNUCKLES = 1 << 1,
    MEDAL_PEELOUT     = 1 << 2,
    MEDAL_INSTASHIELD = 1 << 3,
    MEDAL_NODROPDASH  = 1 << 4,
    MEDAL_NOTIMEOVER  = 1 << 5,
};

enum ScreenSplit { FORCE_SPLIT = 2 };

enum ScreenSizes { WIDE_SCR_XSIZE = 424, WIDE_SCR_XCENTER = 212 };

enum SaveSlots { NO_SAVE_SLOT = 255 };

enum ReservedEntities {
    SLOT_PLAYER1         = 0,
    SLOT_PLAYER2         = 1,
    SLOT_PLAYER3         = 2,
    SLOT_PLAYER4         = 3,
    SLOT_POWERUP1        = 4,
    SLOT_POWERUP2        = 5,
    SLOT_POWERUP3        = 6,
    SLOT_POWERUP4        = 7,
    SLOT_POWERUP1_2      = 8,
    SLOT_POWERUP2_2      = 9,
    SLOT_POWERUP3_2      = 10,
    SLOT_POWERUP4_2      = 11,
    SLOT_SPECIAL_SETUP   = 8,
    SLOT_MUSIC           = 9,
    SLOT_SPECIAL_HUD     = 10,
    SLOT_SPECIAL_MESSAGE = 11,
    SLOT_ZONE            = 12,
    // 13 = ???
    // 14 = ???
    SLOT_CUTSCENESEQ      = 15,
    SLOT_PAUSEMENU        = 16,
    SLOT_GAMEOVER         = 16,
    SLOT_ACTCLEAR         = 16,
    SLOT_MUSICSTACK_START = 40,
    //[41-47] are part of the music stack
    SLOT_MUSICSTACK_END = 48,
    SLOT_CAMERA1        = 60,
    SLOT_CAMERA2        = 61,
    SLOT_CAMERA3        = 62,
    SLOT_CAMERA4        = 63,
};

enum GameCheats {
    SECRET_RICKYMODE = 1 << 0,
    SECRET_SUPERDASH = 1 << 1,
};

enum NotifyCallbackIDs {
    NOTIFY_DEATH_EVENT        = 0x80,
    NOTIFY_TOUCH_SIGNPOST     = 0x81,
    NOTIFY_HUD_ENABLE         = 0x82,
    NOTIFY_ADD_COIN           = 0x83,
    NOTIFY_KILL_ENEMY         = 0x84,
    NOTIFY_SAVESLOT_SELECT    = 0x85,
    NOTIFY_FUTURE_PAST        = 0x86,
    NOTIFY_GOTO_FUTURE_PAST   = 0x87,
    NOTIFY_BOSS_END           = 0x88,
    NOTIFY_SPECIAL_END        = 0x89,
    NOTIFY_DEBUGPRINT         = 0x8A,
    NOTIFY_KILL_BOSS          = 0x8B,
    NOTIFY_TOUCH_EMERALD      = 0x8C,
    NOTIFY_STATS_ENEMY        = 0x8D,
    NOTIFY_STATS_CHARA_ACTION = 0x8E,
    NOTIFY_STATS_RING         = 0x8F,
    NOTIFY_STATS_MOVIE        = 0x90,
    NOTIFY_STATS_PARAM_1      = 0x91,
    NOTIFY_STATS_PARAM_2      = 0x92,
    NOTIFY_CHARACTER_SELECT   = 0x93,
    NOTIFY_SPECIAL_RETRY      = 0x94,
    NOTIFY_TOUCH_CHECKPOINT   = 0x95,
    NOTIFY_ACT_FINISH         = 0x96,
    NOTIFY_1P_VS_SELECT       = 0x97,
    NOTIFY_CONTROLLER_SUPPORT = 0x98,
    NOTIFY_STAGE_RETRY        = 0x99,
    NOTIFY_SOUND_TRACK        = 0x9A,
    NOTIFY_GOOD_ENDING        = 0x9B,
    NOTIFY_BACK_TO_MAINMENU   = 0x9C,
    NOTIFY_LEVEL_SELECT_MENU  = 0x9D,
    NOTIFY_PLAYER_SET         = 0x9E,
    NOTIFY_EXTRAS_MODE        = 0x9F,
    NOTIFY_SPIN_DASH_TYPE     = 0xA0,
    NOTIFY_TIME_OVER          = 0xA1,

    NOTIFY_1000                = 1000,
    NOTIFY_1001                = 1001,
    NOTIFY_1002                = 1002,
    NOTIFY_PLAYER_SAVED_VALUES = 1003,
    NOTIFY_1004                = 1004,
    NOTIFY_1005                = 1005,
    NOTIFY_TITLECARD_INIT      = 1006,
};

enum PlayModes {
    BOOT_PLAYMODE_CLASSIC,
    BOOT_PLAYMODE_ANNIVERSARY,
    BOOT_PLAYMODE_BOSSRUSH,
    BOOT_PLAYMODE_MIRRORING,
    BOOT_PLAYMODE_MISSION,
    BOOT_PLAYMODE_STORY,
};

#if RETRO_REV0U
#define HasNotifyCallback() RSDKTable->NotifyCallback != NULL

#define NotifyCallback(callback, param1, param2, param3)                                                                                             \
    if (HasNotifyCallback())                                                                                                                         \
        RSDKTable->NotifyCallback(callback, param1, param2, param3);
#else
#define NotifyCallback(callback, param1, param2, param3)
#endif

// =========================
// GLOBAL VARIABLES
// =========================

extern void **registerGlobals;
extern int32 registerGlobalsSize;
#if RETRO_REV0U
extern void (*registerGlobalsInitCB)(void *globalVars);

void RegisterGlobals(void **globals, int32 size, void (*initCB)(void *globals));
#else
void RegisterGlobals(void **globals, int32 size);
#endif

// Globals Example
/*

// forward declare
struct GlobalVariables;

extern GlobalVariables *globals;

struct GlobalVariables {
    struct Constructor {
        Constructor()
        {
#if RETRO_REV0U
            // RegisterGlobals((void **)&globals, sizeof(GlobalVariables), &GlobalVariables::Init);
#else
            // RegisterGlobals((void **)&globals, sizeof(GlobalVariables));
#endif
        }
    };

    static Constructor c;

#if RETRO_REV0U
    static void Init(void *g);
#endif

    // Your Variables Go Here
};
#endif
*/

// Use this if you're hooking onto Sonic Mania
struct ManiaGlobalVariables {
    int32 gameMode;
    int32 playerID; // active character IDs (usually leader & sidekick)
    int32 specialCleared;
    int32 specialRingID;
    int32 blueSpheresID;
    int32 blueSpheresInit;
    int32 atlEnabled;
    int32 atlEntityCount;
    int32 atlEntitySlot[0x20];
    int32 atlEntityData[0x4000];
    int32 saveLoaded;
    int32 saveRAM[0x4000];
    int32 saveSlotID;
    int32 noSaveSlot[0x400];
    int32 menuParam[0x4000];
    int32 itemMode;
    int32 suppressTitlecard;
    int32 suppressAutoMusic;
    int32 competitionSession[0x4000];
    int32 medalMods;
    int32 parallaxOffset[0x100];
    int32 enableIntro;
    int32 optionsLoaded;
    int32 optionsRAM[0x80];
    int32 presenceID;
    int32 medallionDebug;
    int32 noSave;
    int32 notifiedAutosave;
    int32 recallEntities;
    int32 restartRings;
    int32 restart1UP;
    int32 restartPowerups;
    int32 restartPos[8];
    int32 restartSlot[4];
    int32 restartDir[4];
    int32 restartMinutes;
    int32 restartSeconds;
    int32 restartMilliseconds;
    int32 tempMinutes;
    int32 tempSeconds;
    int32 tempMilliseconds;
    int32 restartScore;
    int32 restartScore1UP;
    int32 restartLives[4];
    int32 restartMusicID;
    int32 restartFlags;
    int32 tempFlags;
    int32 continues;
    int32 initCoolBonus;
    int32 coolBonus[4];
    // #if MANIA_USE_PLUS
    int32 replayWriteBuffer[0x40000];
    int32 replayReadBuffer[0x40000];
    int32 replayTempWBuffer[0x40000];
    int32 replayTempRBuffer[0x40000];
    int32 replayTableID;
    int32 replayTableLoaded;
    int32 taTableID;
    int32 taTableLoaded;
    int32 stock;          // order of buddies (not including the leader/sidekick)
    int32 characterFlags; // characters in the "party"
    int32 vapeMode;
    int32 secrets;
    int32 superSecret;
    int32 superMusicEnabled;
    int32 lastHasPlus;
    int32 hasPlusInitial;
    // #endif
};

// =========================
// GAME HELPERS
// =========================

#endif //! GAME_VARIABLES_H
