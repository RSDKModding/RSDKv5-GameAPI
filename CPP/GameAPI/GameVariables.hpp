#ifndef GAME_VARIABLES_H
#define GAME_VARIABLES_H

// =========================
// GAME ENUMS
// =========================

#include "RSDKv5/RSDKv5.hpp"

#define PLAYER_COUNT (4)

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
#if GAME_IS_MANIA || GAME_IS_S3
#define GET_CHARACTER_ID(playerNum)                (((globals->playerID >> (8 * ((playerNum) - 1))) & 0xFF))
#define CHECK_CHARACTER_ID(characterID, playerNum) (((globals->playerID >> (8 * ((playerNum) - 1))) & 0xFF) == (characterID))

#if MANIA_USE_PLUS || GAME_IS_S3
#define GET_STOCK_ID(stockNum)                (((globals->stock >> (8 * ((stockNum) - 1))) & 0xFF))
#define CHECK_STOCK_ID(characterID, stockNum) (((globals->stock >> (8 * ((stockNum) - 1))) & 0xFF) == (characterID))
#endif //! MANIA_USE_PLUS || GAME_IS_S3

enum ManiaItemModes {
    ITEMS_FIXED,
    ITEMS_RANDOM,
    ITEMS_TELEPORT,
};

enum ManiaPlaneFilterTypes {
    PLANEFILTER_NONE,
    PLANEFILTER_AL, // - Plane A, Low Layer
    PLANEFILTER_BL, // - Plane B, Low Layer
    PLANEFILTER_AH, // - Plane A, High Layer
    PLANEFILTER_BH, // - Plane B, High Layer
};

#if MANIA_USE_PLUS || GAME_IS_S3
enum ManiaFilters {
    // Mania-Specific filter uses
    FILTER_BOTH   = FILTER_SLOT1,
    FILTER_MANIA  = FILTER_SLOT2,
    FILTER_ENCORE = FILTER_SLOT3,
};

enum ManiaDLC { DLC_PLUS };
#endif //! MANIA_USE_PLUS || GAME_IS_S3

#endif //! GAME_IS_MANIA || GAME_IS_S3
#endif //! GAME_NO_VARIABLES

enum ScreenSizes { WIDE_SCR_XSIZE = 424, WIDE_SCR_XCENTER = 212 };

#ifndef GAME_NO_VARIABLES
#if GAME_IS_MANIA
enum ManiaGameModes {
#if !MANIA_USE_PLUS
    MODE_NOSAVE,
#endif
    MODE_MANIA, // officially called "MODE_SAVEGAME" in pre-plus, but it's easier to re-use names lol
#if MANIA_USE_PLUS
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
#if MANIA_USE_PLUS
    ID_MIGHTY = 1 << 3,
    ID_RAY    = 1 << 4,
#endif

    ID_TAILS_ASSIST    = ID_TAILS << 8,
    ID_KNUCKLES_ASSIST = ID_KNUCKLES << 8, // custom-added, can be used to check if "& knux" is active
    ID_DEFAULT_PLAYER  = ID_SONIC | ID_TAILS_ASSIST,
};

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
#endif //! MANIA_USE_PLUS

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
enum ManiaSaveSlots { NO_SAVE_SLOT = 0xFF };
#endif //! GAME_IS_MANIA

#if GAME_IS_S3
enum S3GameModes {
    MODE_SAVEGAME,
    MODE_ENCORE,
    MODE_TIMEATTACK,
    MODE_COMPETITION,
};

enum S3PlayerIDs {
    ID_NONE     = 0 << 0,
    ID_SONIC    = 1 << 0,
    ID_TAILS    = 1 << 1,
    ID_KNUCKLES = 1 << 2,
#if ORIGINS_USE_PLUS
    ID_AMY    = 1 << 3,
    ID_MIGHTY = 1 << 4,
    ID_RAY    = 1 << 5,
#else
    ID_MIGHTY = 1 << 3,
    ID_RAY    = 1 << 4,
#endif

    ID_TAILS_ASSIST    = ID_TAILS << 8,
    ID_KNUCKLES_ASSIST = ID_KNUCKLES << 8, // custom-added, can be used to check if "& knux" is active
    ID_DEFAULT_PLAYER  = ID_SONIC | ID_TAILS_ASSIST,

#if ORIGINS_USE_PLUS
    ID_AMY_TAILS = ID_AMY | ID_TAILS_ASSIST,
#endif
};

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
    RESTARTFLAG_SCENE_AIZ1_FIRE,
};

enum S3StageFinishedTypes {
    STAGEFINISH_NONE,
    STAGEFINISH_TRANSITION,
    STAGEFINISH_IN_ACT_RELOAD,
};

enum S3BossAttackClearTypes {
    BOSSATTACK_CLEAR_NONE         = 0,
    BOSSATTACK_CLEAR_FIREBREATH   = 1,
    BOSSATTACK_CLEAR_FLAMEMOBILE  = 2,
    BOSSATTACK_CLEAR_BIGSHAKER    = 3,
    BOSSATTACK_CLEAR_SCREWMOBILE  = 4,
    BOSSATTACK_CLEAR_GAKIN        = 5,
    BOSSATTACK_CLEAR_DRILLMOBILE  = 6,
    BOSSATTACK_CLEAR_FINALWEAPON2 = 9,
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

enum S3MissionFunctions {
    MISSIONNO_NONE            = 0,
    MISSIONNO_MERCY           = 8,
    MISSIONNO_RINGCHALLENGE50 = 10,
    MISSIONNO_TIMEDBATBOT     = 11,
    MISSIONNO_AERIALATTACK    = 18,
    MISSIONNO_RINGVACCUM      = 30,
    MISSIONNO_BALLOONBURST    = 38,
    MISSIONNO_FIREBALLDASH    = 39,
};

enum S3MissionConditions {
    MISSION_CONDITION_NONE,
    MISSION_CONDITION_CLEAR,
    MISSION_CONDITION_FAIL,
};

enum S3NotifyKillEnemyAttributes {
    KILL_ENEMY_ATTR_DEFAULT,
    KILL_ENEMY_ATTR_ANIMALPRISON,
    KILL_ENEMY_ATTR_SPINDASH,
    KILL_ENEMY_ATTR_GLIDING,
    KILL_ENEMY_ATTR_RINGVACUUM,
    KILL_ENEMY_ATTR_BALLOON,
    KILL_ENEMY_ATTR_FIREDASH,
};

enum S3HUDEnableTypes {
    HUDENABLE_OFF,
    HUDENABLE_ON,
};

enum S3TitleModes {
    TITLEMODE_SHOW_LOGOS,
    TITLEMODE_SKIP_LOGOS,
};

enum S3SaveSlots { NO_SAVE_SLOT = 0xFF };
#endif //! GAME_IS_S3
#endif //! GAME_NO_VARIABLES

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

    NOTIFY_DELETE_SAVE_SLOT       = 1001,
    NOTIFY_SELECT_SAVE_SLOT       = 1002,
    NOTIFY_PLAYER_SAVED_VALUES    = 1003,
    NOTIFY_STAGE_RESTART_OVERRIDE = 1004,
    NOTIFY_START_STAGE            = 1005,
    NOTIFY_DISPLAY_TITLECARD      = 1006,
#if ORIGINS_USE_PLUS
    NOTIFY_DISPLAY_PLUS_DLC_ERROR = 1007,
#endif
};
#endif //! RETRO_REV0U

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
#define HasNotifyCallback() RSDKTable->NotifyCallback != nullptr

#define NotifyCallback(callback, param1, param2, param3)                                                                                             \
    if (HasNotifyCallback())                                                                                                                         \
        RSDKTable->NotifyCallback(callback, param1, param2, param3);

#define SetGameFinished() RSDKTable->SetGameFinished();
#else
#define HasNotifyCallback() false

#define NotifyCallback(callback, param1, param2, param3)
#define SetGameFinished()
#endif //! RETRO_REV0U

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
#endif //! RETRO_REV0U

#ifndef GAME_NO_GLOBALS
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
    int32 saveSlotID = NO_SAVE_SLOT;
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
    int32 presenceID = -1;
    int32 medallionDebug;
    int32 noSave;
    int32 notifiedAutosave;
    int32 recallEntities;
    int32 restartRings;
    int32 restart1UP;
    int32 restartPowerups;
    int32 restartPos[PLAYER_COUNT * 2];
    int32 restartSlot[PLAYER_COUNT];
    int32 restartDir[PLAYER_COUNT];
    int32 restartMinutes;
    int32 restartSeconds;
    int32 restartMilliseconds;
    int32 tempMinutes;
    int32 tempSeconds;
    int32 tempMilliseconds;
    int32 restartScore;
    int32 restartScore1UP;
    int32 restartLives[PLAYER_COUNT];
#if GAME_VERSION != VER_100
    int32 restartMusicID;
#endif
    int32 restartFlags;
    int32 tempFlags;
    int32 continues;
    int32 initCoolBonus;
    int32 coolBonus[PLAYER_COUNT];
#if MANIA_USE_PLUS
    int32 replayWriteBuffer[0x40000];
    int32 replayReadBuffer[0x40000];
    int32 replayTempWBuffer[0x40000];
    int32 replayTempRBuffer[0x40000];
    int32 replayTableID = 0xFFFF;
    int32 replayTableLoaded;
    int32 taTableID = 0xFFFF;
    int32 taTableLoaded;
    int32 stock          = (ID_RAY << 16) | (ID_KNUCKLES << 8) | ID_TAILS;         // order of buddies (not including the leader/sidekick)
    int32 characterFlags = ID_SONIC | ID_TAILS | ID_KNUCKLES | ID_MIGHTY | ID_RAY; // characters in the "party"
    int32 vapeMode;
    int32 secrets;
    int32 superSecret;
    int32 superMusicEnabled = true;
    int32 lastHasPlus;
    int32 hasPlusInitial;
#endif
};

typedef ManiaGlobalVariables GlobalVariables;
extern GlobalVariables *globals;
#elif GAME_IS_S3
// Use this if you're hooking onto Origins' S3
struct S3GlobalVariables {
    int32 gameMode;
    int32 playerID = ID_DEFAULT_PLAYER;
    int32 specialCleared;
    int32 specialRingID;
    int32 blueSpheresID;
    int32 blueSpheresInit;
    int32 atlEnabled;
    int32 atlEntityCount;
#if GAME_VERSION >= VER_104
    int32 atlEntitySlot[0x120];
    void *atlEntityData[0x120 * 0x114];
#else
    int32 atlEntitySlot[0x20];
    int32 atlEntityData[0x20 * 0x400];
#endif
    int32 saveLoaded;
    int32 saveRAM[0x1C00];
    int32 saveSlotID = NO_SAVE_SLOT;
    int32 noSaveSlot[0x100];
    int32 menuParam[0x4000];
    int32 itemMode;
    bool32 suppressTitlecard;
    bool32 suppressAutoMusic;
    int32 competitionSession[0x4000];
    int32 medalMods = MEDAL_INSTASHIELD;
    int32 parallaxOffset[0x100];
    int32 enableIntro;
    int32 optionsLoaded;
    int32 optionsRAM[0x80];
    int32 presenceID = -1;
    int32 medallionDebug;
    int32 noSave;
    int32 notifiedAutosave;
    int32 recallEntities;
    int32 restartRings;
    int32 restart1UP = 100;
    int32 restartPowerups;
    RSDK::Vector2 restartPos[PLAYER_COUNT];
    int32 restartSlot[PLAYER_COUNT];
    int32 restartDir[PLAYER_COUNT];
    int32 restartMinutes;
    int32 restartSeconds;
    int32 restartMilliseconds;
    int32 restartScore;
    int32 restartScore1UP            = 50000;
    int32 restartLives[PLAYER_COUNT] = { 3, 3, 3, 3 };
    int32 restartMusicID;
    bool32 restartFlags;
    int32 restartPostID;
    bool32 timeOver;
    bool32 overrideRestart;
    bool32 overrideUseHiteRestartStage;
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
    int32 stock = (1 << 4) | (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0);
    int32 characterFlags;
    bool32 vapeMode;
    int32 secrets;
    int32 superSecret;
    bool32 soundTestEnabled;
    bool32 superMusicEnabled = true;
    int32 playerSpriteStyle  = GAME_S3K;
    int32 gameSpriteStyle    = GAME_S3K;
    int32 ostStyle           = GAME_S3K;
    int32 starpostStyle      = GAME_S3K;
    bool32 stageFinished;
    bool32 displayAct1Title;
    bool32 useHiteRestartStage;
    int32 atlCameraBoundsL[PLAYER_COUNT];
    int32 atlCameraBoundsR[PLAYER_COUNT];
    int32 atlCameraBoundsT[PLAYER_COUNT];
    int32 atlCameraBoundsB[PLAYER_COUNT];
    RSDK::Vector2 atlCameraPos[PLAYER_COUNT];
    RSDK::Vector2 atlOffset;
    uint8 atlScratchRAM[0x20];
    int32 atlTimer;
    int32 tileCollisionMode = RSDK::TILECOLLISION_DOWN;
    uint8 gravityDir;
    uint8 blueSpheresSeed[4];
    bool32 blueSpheresHasPerfect;
    int32 blueSpheresLevel;
    int32 blueSpheresProgress;
    int32 blueSpheresNextLevel = -1;
    bool32 blueSpheresDisableAdvancement;
    bool32 blueSpheresAdvancementStore;
    uint8 blueSpheresUnlockFlag;
    bool32 gameStarted  = true;
    bool32 disableLives = true;
    bool32 mirrorMode;
    bool32 useManiaBehavior;
    int32 coinCount;
    bool32 showHUD   = true;
    bool32 showLives = true;
    bool32 disableSSAdvancement;
    bool32 pressButton;
    int32 blueSpheresDifficulty;
    bool32 isBossAttack;
    uint8 bossAttackCategory;
    uint8 bossAttackRestartMilliseconds;
    uint8 bossAttackRestartSeconds;
    uint8 bossAttackRestartMinutes;
    int32 bossAttackRestartRings;
    uint8 bossAttackRestartPowerup;
    uint8 bossAttackClearType;
    bool32 hasBossAttackRestartState;
#if ORIGINS_USE_PLUS
    bool32 hasPlusDLC;
#endif
    int32 playMode;
    int32 callbackParam0;
    int32 callbackParam1;
    int32 callbackParam2;
    int32 callbackParam3;
    bool32 hudEnable;
    bool32 coinMode;
    bool32 forceKillPlayer;
    int32 missionCondition;
    int32 missionFunctionNo;
    int32 missionFunctionMask;
    int32 missionValue;
    bool32 missionEnd;
    bool32 continueFlag;
    bool32 titleCardDisable;
    bool32 bossOneLife;
    int32 mainMenuMode;
    int32 callbackResult;
    int32 titleMode;
    bool32 oneStageFlag;
    bool32 ssFastClearFlag;
    int32 statsUsabilityParam1;
    int32 statsUsabilityParam2;
    int32 statsUsabilityParam3;
    int32 statsUsabilityParam4;
    int32 statsUsabilityParam5;
    int32 statsParam7;
    int32 statsParam8;
    int32 statsParam2;
    int32 unused1;
    int32 unused2;
    bool32 retryWait;
    bool32 unused3;
    bool32 cheatEmeralds;
#if GAME_VERSION >= VER_104
    bool32 stageSelectLRZB;
    bool32 stageSelectDEZB;
    bool32 cheatsEnabled;
    bool32 enteredSpecialRing;
    bool32 exitedHPZShrine;
#endif
};

typedef S3GlobalVariables GlobalVariables;
extern GlobalVariables *globals;
#elif !defined(GAME_NO_VARIABLES)
// forward declare
struct GlobalVariables;

extern GlobalVariables *globals;

// Globals Example
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
#endif //! GAME_NO_GLOBALS

// =========================
// GAME HELPERS
// =========================

#if GAME_IS_MANIA
#if MANIA_USE_PLUS
#define isMainGameMode() (globals->gameMode == MODE_MANIA || globals->gameMode == MODE_ENCORE)
#else
#define isMainGameMode() (globals->gameMode == MODE_NOSAVE || globals->gameMode == MODE_MANIA)
#endif
#endif

#if GAME_IS_S3
#define isMainGameMode() (globals->gameMode == MODE_SAVEGAME || globals->gameMode == MODE_ENCORE)
#endif

#endif //! GAME_VARIABLES_H
