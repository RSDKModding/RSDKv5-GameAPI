#ifndef GAME_VARIABLES_H
#define GAME_VARIABLES_H

// =========================
// GAME ENUMS
// =========================

#include "RSDKv5/RSDKv5.hpp"

#define PLAYER_COUNT (4)

#ifndef GAME_NO_VARIABLES

#if GAME_IS_MANIA || GAME_IS_S3
enum ManiaGameModes {
#if !MANIA_USE_PLUS && !GAME_IS_S3
    MODE_NOSAVE,
#endif
    MODE_MANIA, // officially called "MODE_SAVEGAME" in pre-plus, but it's easier to re-use names lol
#if MANIA_USE_PLUS || GAME_IS_S3
    MODE_ENCORE,
#endif
    MODE_TIMEATTACK,
    MODE_COMPETITION,
};

enum ManiaPlayerIDs {
    ID_NONE     = 0 << 0,
    ID_SONIC    = 1 << 0,
    ID_TAILS    = 1 << 1,
    ID_KNUCKLES = 1 << 2,
#if MANIA_USE_PLUS || GAME_IS_S3
    ID_MIGHTY = 1 << 3,
    ID_RAY    = 1 << 4,
#endif
    ID_TAILS_ASSIST    = ID_TAILS << 8,
    ID_KNUCKLES_ASSIST = ID_KNUCKLES << 8, // custom-added, can be used to check if "& knux" is active
    ID_DEFAULT_PLAYER  = ID_SONIC | ID_TAILS_ASSIST,
};

#define GET_CHARACTER_ID(playerNum)                (((globals->playerID >> (8 * ((playerNum)-1))) & 0xFF))
#define CHECK_CHARACTER_ID(characterID, playerNum) (((globals->playerID >> (8 * ((playerNum)-1))) & 0xFF) == (characterID))

#if MANIA_USE_PLUS
#define GET_STOCK_ID(stockNum)                (((globals->stock >> (8 * ((stockNum)-1))) & 0xFF))
#define CHECK_STOCK_ID(characterID, stockNum) (((globals->stock >> (8 * ((stockNum)-1))) & 0xFF) == (characterID))
#endif

enum ManiaItemModes { ITEMS_FIXED, ITEMS_RANDOM, ITEMS_TELEPORT };

enum ManiaPlaneFilterTypes {
    PLANEFILTER_NONE,
    PLANEFILTER_AL, // - Plane A, Low Layer
    PLANEFILTER_BL, // - Plane B, Low Layer
    PLANEFILTER_AH, // - Plane A, High Layer
    PLANEFILTER_BH, // - Plane B, High Layer
};
#endif

#if GAME_IS_MANIA
enum ManiaMedalMods {
    MEDAL_DEBUGMODE   = 1 << 0,
    MEDAL_ANDKNUCKLES = 1 << 1,
    MEDAL_PEELOUT     = 1 << 2,
    MEDAL_INSTASHIELD = 1 << 3,
    MEDAL_NODROPDASH  = 1 << 4,
#if MANIA_USE_PLUS
    MEDAL_NOTIMEOVER = 1 << 5,
#endif
};

enum ManiaCategoryIDS { MEDIA_DEMO };

enum ManiaScreenSplit { FORCE_SPLIT };

enum ManiaSaveSlots { NO_SAVE_SLOT = 255 };
#endif
#endif

enum ScreenSizes { WIDE_SCR_XSIZE = 424, WIDE_SCR_XCENTER = 212 };

#if RETRO_REV02
enum SceneFilters {
    // General Filters
    FILTER_NONE  = 0 << 0,
    FILTER_SLOT1 = 1 << 0,
    FILTER_SLOT2 = 1 << 1,
    FILTER_SLOT3 = 1 << 2,
    FILTER_SLOT4 = 1 << 3,
    FILTER_SLOT5 = 1 << 4,
    FILTER_SLOT6 = 1 << 5,
    FILTER_SLOT7 = 1 << 6,
    FILTER_SLOT8 = 1 << 7,
    FILTER_ANY   = FILTER_SLOT1 | FILTER_SLOT2 | FILTER_SLOT3 | FILTER_SLOT4 | FILTER_SLOT5 | FILTER_SLOT6 | FILTER_SLOT7 | FILTER_SLOT8,
};
#endif

#ifndef GAME_NO_VARIABLES

#if GAME_IS_MANIA

#if MANIA_USE_PLUS
enum ManiaFilters {
    // Mania-Specific filter uses
    FILTER_BOTH   = FILTER_SLOT1,
    FILTER_MANIA  = FILTER_SLOT2,
    FILTER_ENCORE = FILTER_SLOT3,
};

enum ManiaDLC { DLC_PLUS };
#endif

enum ManiaReservedEntities {
    SLOT_PLAYER1 = 0,
    SLOT_PLAYER2 = 1,
#if MANIA_USE_PLUS
    SLOT_PLAYER3    = 2,
    SLOT_PLAYER4    = 3,
    SLOT_POWERUP1   = 4,
    SLOT_PLAYER5    = 4, // Used in TMZ2Outro
    SLOT_POWERUP2   = 5,
    SLOT_PLAYER6    = 5, // Used in TMZ2Outro
    SLOT_POWERUP3   = 6,
    SLOT_POWERUP4   = 7,
    SLOT_POWERUP1_2 = 8,
    SLOT_POWERUP2_2 = 9,
    SLOT_POWERUP3_2 = 10,
    SLOT_POWERUP4_2 = 11,
#else
    SLOT_POWERUP1   = 2,
    SLOT_POWERUP2   = 3,
    SLOT_POWERUP1_2 = 4,
    SLOT_POWERUP2_2 = 5,
#endif
    SLOT_BSS_SETUP   = 8,
    SLOT_PBL_SETUP   = 8,
    SLOT_UFO_SETUP   = 8,
    SLOT_MUSIC       = 9,
    SLOT_BSS_HUD     = 10,
    SLOT_UFO_CAMERA  = 10,
    SLOT_PBL_CAMERA  = 10,
    SLOT_BSS_MESSAGE = 11,
    SLOT_UFO_HUD     = 11,
    SLOT_ZONE        = MANIA_USE_PLUS ? 12 : 8,
    // 13 = ???
    // 14 = ???
    SLOT_CUTSCENESEQ         = 15,
    SLOT_PAUSEMENU           = 16,
    SLOT_GAMEOVER            = 16,
    SLOT_ACTCLEAR            = 16,
    SLOT_PAUSEMENU_UICONTROL = 17,
    SLOT_PAUSEMENU_BUTTON1   = 18,
    SLOT_PAUSEMENU_BUTTON2   = 19,
    SLOT_PAUSEMENU_BUTTON3   = 20,
    SLOT_DIALOG              = 21,
    SLOT_DIALOG_UICONTROL    = 22,
    SLOT_DIALOG_BUTTONS      = 23,
    SLOT_DIALOG_BUTTON2      = 24,
    SLOT_DIALOG_BUTTON3      = 25,
#if MANIA_USE_PLUS
    SLOT_POPOVER           = 26,
    SLOT_POPOVER_UICONTROL = 27,
    SLOT_POPOVER_BUTTONS   = 28,
    SLOT_POPOVER_BUTTON2   = 29,
    SLOT_POPOVER_BUTTON3   = 30,
    SLOT_POPOVER_BUTTON4   = 31,
#endif
    SLOT_BIGBUBBLE_P1 = 32,
    SLOT_BIGBUBBLE_P2 = 33,
#if MANIA_USE_PLUS
    SLOT_BIGBUBBLE_P3 = 34,
    SLOT_BIGBUBBLE_P4 = 36,
#endif
    SLOT_BSS_HORIZON    = 32,
    SLOT_UFO_SPEEDLINES = 34,
    SLOT_UFO_PLASMA     = 36,
#if MANIA_USE_PLUS
    SLOT_REPLAYRECORDER_PLAYBACK = 36,
    SLOT_REPLAYRECORDER_RECORD   = 37,
    SLOT_MUSICSTACK_START        = 40,
    //[41-47] are part of the music stack
    SLOT_MUSICSTACK_END = 48,
#endif
    SLOT_CAMERA1 = 60,
    SLOT_CAMERA2 = 61,
    SLOT_CAMERA3 = 62,
    SLOT_CAMERA4 = 63,
};

enum ManiaPresenceTypes {
    PRESENCE_GENERIC,
    PRESENCE_MENU,
    PRESENCE_MANIA,
#if MANIA_USE_PLUS
    PRESENCE_ENCORE,
#endif
    PRESENCE_TA,
    PRESENCE_COMP,
    PRESENCE_TITLE,
};

#if MANIA_USE_PLUS
enum ManiaGameCheats {
    SECRET_RICKYMODE = 1 << 0,
    SECRET_SUPERDASH = 1 << 1,
};
#endif

#endif

#if GAME_IS_S3
enum S3GameTypes {
    GAME_S1,
    GAME_CD,
    GAME_S2,
    GAME_SM,
    GAME_S3K,
    GAME_S3,
    GAME_SK,
};

enum S3GameCheats {
    SECRET_RICKYMODE        = 1 << 0,
    SECRET_SUPERDASH        = 1 << 1,
    SECRET_BARRELHOTLINE    = 1 << 2, // unused in normal gameplay
    SECRET_NORMALPHYSICS_2P = 1 << 3,
    SECRET_REGIONSWAP       = 1 << 4,
    SECRET_CAMERATRACKING   = 1 << 5,
    SECRET_PENPENMODE       = 1 << 6,
    SECRET_RANDOMITEMS      = 1 << 7,
    SECRET_BLUESHIELDMODE   = 1 << 8,
    SECRET_UNKNOWN          = 1 << 9, // unused in normal gameplay
    SECRET_BANANAMODE       = 1 << 10,
    SECRET_NOITEMS          = 1 << 11,
    SECRET_HIDDENCREDITS    = 1 << 12,
};

enum S3RestartFlags {
    RESTARTFLAG_NONE,
    RESTARTFLAG_EXIT_SPECIAL_STAGE,
    RESTARTFLAG_GET_SUPER_EMERALD,
    RESTARTFLAG_EXIT_BONUS_STAGE,
    RESTARTFLAG_4,
};

enum S3ReservedEntities {
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

enum S3MedalMods {
    MEDAL_DEBUGMODE   = 1 << 0,
    MEDAL_ANDKNUCKLES = 1 << 1,
    MEDAL_PEELOUT     = 1 << 2,
    MEDAL_INSTASHIELD = 1 << 3,
    MEDAL_NODROPDASH  = 1 << 4,
    MEDAL_NOTIMEOVER  = 1 << 5,
    MEDAL_NOLIVES     = 1 << 6,
};

#endif

#endif

#if RETRO_REV0U
enum NotifyCallbackIDs {
    NOTIFY_DEATH_EVENT         = 0x80,
    NOTIFY_TOUCH_SIGNPOST      = 0x81,
    NOTIFY_HUD_ENABLE          = 0x82,
    NOTIFY_ADD_COIN            = 0x83,
    NOTIFY_KILL_ENEMY          = 0x84,
    NOTIFY_SAVESLOT_SELECT     = 0x85,
    NOTIFY_FUTURE_PAST         = 0x86,
    NOTIFY_GOTO_FUTURE_PAST    = 0x87,
    NOTIFY_BOSS_END            = 0x88,
    NOTIFY_SPECIAL_END         = 0x89,
    NOTIFY_DEBUGPRINT          = 0x8A,
    NOTIFY_KILL_BOSS           = 0x8B,
    NOTIFY_TOUCH_EMERALD       = 0x8C,
    NOTIFY_STATS_ENEMY         = 0x8D,
    NOTIFY_STATS_CHARA_ACTION  = 0x8E,
    NOTIFY_STATS_RING          = 0x8F,
    NOTIFY_STATS_MOVIE         = 0x90,
    NOTIFY_STATS_PARAM_1       = 0x91,
    NOTIFY_STATS_PARAM_2       = 0x92,
    NOTIFY_CHARACTER_SELECT    = 0x93,
    NOTIFY_SPECIAL_RETRY       = 0x94,
    NOTIFY_TOUCH_CHECKPOINT    = 0x95,
    NOTIFY_ACT_FINISH          = 0x96,
    NOTIFY_1P_VS_SELECT        = 0x97,
    NOTIFY_CONTROLLER_SUPPORT  = 0x98,
    NOTIFY_STAGE_RETRY         = 0x99,
    NOTIFY_SOUND_TRACK         = 0x9A,
    NOTIFY_GOOD_ENDING         = 0x9B,
    NOTIFY_BACK_TO_MAINMENU    = 0x9C,
    NOTIFY_LEVEL_SELECT_MENU   = 0x9D,
    NOTIFY_PLAYER_SET          = 0x9E,
    NOTIFY_EXTRAS_MODE         = 0x9F,
    NOTIFY_SPIN_DASH_TYPE      = 0xA0,
    NOTIFY_TIME_OVER           = 0xA1,
    NOTIFY_TIMEATTACK_MODE     = 0xA2,
    NOTIFY_STATS_BREAK_OBJECT  = 0xA3,
    NOTIFY_STATS_SAVE_FUTURE   = 0xA4,
    NOTIFY_STATS_CHARA_ACTION2 = 0xA5,

    NOTIFY_1000                = 1000,
    NOTIFY_1001                = 1001,
    NOTIFY_1002                = 1002,
    NOTIFY_PLAYER_SAVED_VALUES = 1003,
    NOTIFY_1004                = 1004,
    NOTIFY_1005                = 1005,
    NOTIFY_TITLECARD_INIT      = 1006,
};
#endif

#if GAME_IS_S3 && !defined(GAME_NO_VARIABLES)
enum S3PlayModes {
    BOOT_PLAYMODE_CLASSIC,
    BOOT_PLAYMODE_ANNIVERSARY,
    BOOT_PLAYMODE_BOSSRUSH,
    BOOT_PLAYMODE_MIRRORING,
    BOOT_PLAYMODE_MISSION,
    BOOT_PLAYMODE_STORY,
};
#endif

#if RETRO_REV0U
#define HasNotifyCallback() RSDKTable->NotifyCallback != NULL

#define NotifyCallback(callback, param1, param2, param3)                                                                                             \
    if (HasNotifyCallback())                                                                                                                         \
        RSDKTable->NotifyCallback(callback, param1, param2, param3);
#else
#define HasNotifyCallback() false

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

#ifndef GAME_NO_GLOBALS
// Globals Example

#if !GAME_IS_MANIA && !GAME_IS_S3 && !defined(GAME_NO_VARIABLES)
// forward declare
struct GlobalVariables;

extern GlobalVariables *globals;

struct GlobalVariables {
    struct Constructor {
        Constructor()
        {
#if RETRO_REV0U
            RegisterGlobals((void **)&globals, sizeof(GlobalVariables), &GlobalVariables::Init);
#else
            RegisterGlobals((void **)&globals, sizeof(GlobalVariables));
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

#if GAME_IS_MANIA
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
#if GAME_VERSION != VER_100
    int32 restartMusicID;
#endif
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
#endif

#if GAME_IS_S3
// Use this if you're hooking onto Origins' S3
struct S3GlobalVariables {
    int32 gameMode;
    int32 playerID;
    int32 specialCleared;
    int32 specialRingID;
    int32 blueSpheresID;
    int32 blueSpheresInit;
    int32 atlEnabled;
    int32 atlEntityCount;
#if GAME_VERSION == VER_104
    int32 atlEntitySlot[0x120];
    void *atlEntityData[0x120 * 0x114];
#else
    int32 atlEntitySlot[0x20];
    int32 atlEntityData[0x20 * 0x400];
#endif
    int32 saveLoaded;
    int32 saveRAM[0x1C00];
    int32 saveSlotID;
    int32 noSaveSlot[0x100];
    int32 menuParam[0x4000];
    int32 itemMode;
    bool32 suppressTitlecard;
    bool32 suppressAutoMusic;
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
    RSDK::Vector2 restartPos[PLAYER_COUNT];
    int32 restartSlot[PLAYER_COUNT];
    int32 restartDir[PLAYER_COUNT];
    int32 restartMinutes;
    int32 restartSeconds;
    int32 restartMilliseconds;
    int32 restartScore;
    int32 restartScore1UP;
    int32 restartLives[4];
    int32 restartMusicID;
    bool32 restartFlags;
    int32 field_47B4C;
    int32 showExtendedTimeHUD;
    int32 overrideRestart;
    int32 overrideUnknown;
    RSDK::Vector2 overrideRestartPos[PLAYER_COUNT];
    int32 overrideRestartSlot[PLAYER_COUNT];
    int32 overrideRestartDir[PLAYER_COUNT];
    int32 overrideRestartMinutes;
    int32 overrideRestartSeconds;
    int32 overrideRestartMilliseconds;
    int32 tempMinutes;
    int32 tempSeconds;
    int32 tempMilliseconds;
    int32 persistentTimer;
    int32 tempFlags;
    int32 continues;
    bool32 initCoolBonus;
    int32 coolBonus[PLAYER_COUNT];
    int32 replayWriteBuffer[0x40000];
    int32 replayReadBuffer[0x40000];
    int32 replayTempWBuffer[0x40000];
    int32 replayTempRBuffer[0x40000];
    RSDK::API::Storage::UserDB replayTable;
    int32 replayTableLoaded;
    RSDK::API::Storage::UserDB taTable;
    int32 taTableLoaded;
    int32 stock;
    int32 characterFlags;
    bool32 vapeMode;
    int32 secrets;
    int32 field_447BF4;
    bool32 soundTestEnabled;
    bool32 superMusicEnabled;
    int32 playerSpriteStyle;
    int32 gameSpriteStyle;
    int32 ostStyle;
    int32 starpostStyle;
    bool32 stageFinished;
    int32 field_447C14;
    int32 storedOverrideUnknown;
    int32 atlCameraBoundsL[PLAYER_COUNT];
    int32 atlCameraBoundsR[PLAYER_COUNT];
    int32 atlCameraBoundsT[PLAYER_COUNT];
    int32 atlCameraBoundsB[PLAYER_COUNT];
    RSDK::Vector2 atlCameraPos[PLAYER_COUNT];
    RSDK::Vector2 atlOffset;
    int32 unknownValues[4];
    int32 unknownValues2[4];
    int32 field_447CA4;
    bool32 tileCollisionMode;
    uint8 gravityDir;
    uint8 blueSpheresSeed[4];
    bool32 blueSpheresHasPerfect;
    int32 field_447CB8;
    int32 field_447CBC;
    int32 field_447CC0;
    int32 field_447CC4;
    int32 field_447CC8;
    uint8 field_447CCC;
    int32 field_447CD0;
    bool32 disableLives;
    bool32 mirrorMode;
    bool32 useManiaBehavior;
    int32 coinCount;
    bool32 showHUD;
    bool32 showLives;
    bool32 disableSSAdvancement;
    int32 anyPress;
    bool32 isBossAttack;
    uint8 bossAttackCategory;
    int32 bossAttackRestartRings;
    uint8 bossAttackRestartMilliseconds;
    uint8 bossAttackRestartSeconds;
    uint8 bossAttackRestartMinutes;
    uint8 bossAttackRestartPowerup;
    bool32 hasBossAttackRestartState;
    int32 playMode;
    int32 callbackParam0;
    int32 callbackParam1;
    int32 callbackParam2;
    int32 callbackParam3;
    bool32 hudEnable;
    bool32 useCoins;
    bool32 forceKillPlayer;
    int32 missionCondition;
    int32 missionFunctionNo;
    int32 missionValue;
    int32 missionEnd;
    int32 continueFlag;
    bool32 skipSaveSelect;
    int32 field_447D40;
    int32 field_447D44;
    int32 field_447D48;
    int32 callbackResult;
    bool32 skipTitleIntro;
    bool32 allowRetries;
    bool32 clearBlueSpheres;
    int32 field_447D5C;
    int32 field_447D60;
    int32 field_447D64;
    int32 field_447D68;
    int32 field_447D6C;
    int32 statsParam7;
    int32 statsParam8;
    int32 statsParam2;
    int32 field_447D7C;
    int32 field_447D80;
    bool32 enableSSWaitRetry;
    int32 field_447D88;
    int32 field_447D8C;
    int32 field_447D90;
    int32 field_447D94;
#if GAME_VERSION == VER_104
    bool32 cheatsEnabled;
    int32 field_447D9C;
#endif
};
#endif

#endif

// =========================
// GAME HELPERS
// =========================

#if GAME_IS_MANIA || GAME_IS_S3

#if MANIA_USE_PLUS || GAME_IS_S3
#define isMainGameMode() (globals->gameMode == MODE_MANIA || globals->gameMode == MODE_ENCORE)
#else
#define isMainGameMode() (globals->gameMode == MODE_NOSAVE || globals->gameMode == MODE_MANIA)
#endif

#endif

#endif //! GAME_VARIABLES_H
