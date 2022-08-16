// This is the file that should be included and start the include tree.
// If this file isn't included first, there will definitely be many errors.
#pragma once

#ifndef _MSC_VER
// Silence "offset of non standard type" warning
// I don't care about it
#pragma GCC diagnostic ignored "-Winvalid-offsetof"
#endif

// main tree path:
#include "API/Mod.hpp"
#include "Math/Math.hpp"
#include "Math/Matrix.hpp"
#include "Game/Object.hpp"
#include "Graphics/Sprite.hpp"
#include "Essentials/String.hpp"
#include "Game/Collision.hpp"
#include "Game/StateMachine.hpp"
#include "Graphics/Graphics.hpp"
#include "Graphics/Video.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/Animator.hpp"
#include "Input/Input.hpp"
#include "Audio/Audio.hpp"
#include "Graphics/Layer.hpp"
#include "Game/Stage.hpp"
#include "Game/ForEach.hpp"
#include "API/API.hpp"
#include "Debugging/Dev.hpp"

#ifdef RSDK_IMPL
#ifdef _MSC_VER
#define DLLExport __declspec(dllexport)
#else
#define DLLExport
#endif

const char *RSDK::currentState = nullptr;

int32 RSDK::registerObjectListCount = 0;
RSDK::ObjectRegistration RSDK::registerObjectList[0x400];

#if RETRO_REV02
int32 RSDK::registerStaticListCount = 0;
RSDK::ObjectRegistration RSDK::registerStaticList[0x400];
#endif

RSDK::Channel RSDK::channels[CHANNEL_COUNT] = { RSDK::Channel(0),  RSDK::Channel(1),  RSDK::Channel(2),  RSDK::Channel(3),
                                                RSDK::Channel(4),  RSDK::Channel(5),  RSDK::Channel(6),  RSDK::Channel(7),
                                                RSDK::Channel(8),  RSDK::Channel(9),  RSDK::Channel(10), RSDK::Channel(11),
                                                RSDK::Channel(12), RSDK::Channel(13), RSDK::Channel(14), RSDK::Channel(15) };

RSDK::Palette RSDK::paletteBank[8] = { RSDK::Palette(0), RSDK::Palette(1), RSDK::Palette(2), RSDK::Palette(3),
                                       RSDK::Palette(4), RSDK::Palette(5), RSDK::Palette(6), RSDK::Palette(7) };

RSDK::RSDKFunctionTable *RSDK::RSDKTable;
RSDK::APIFunctionTable *RSDK::APITable;
#if RETRO_USE_MOD_LOADER
RSDK::ModFunctionTable *RSDK::modTable;

const char* RSDK::Mod::modID = ":Unknown Mod ID:";
#endif

RSDK::SceneInfo *RSDK::sceneInfo = nullptr;

RSDK::GameInfo *RSDK::gameInfo = nullptr;
RSDK::SKUInfo *RSDK::SKU       = nullptr;

RSDK::ControllerState *RSDK::controllerInfo = nullptr;
RSDK::AnalogState *RSDK::analogStickInfoL   = nullptr;
RSDK::AnalogState *RSDK::analogStickInfoR   = nullptr;
RSDK::TriggerState *RSDK::triggerInfoL      = nullptr;
RSDK::TriggerState *RSDK::triggerInfoR      = nullptr;
RSDK::TouchInfo *RSDK::touchInfo            = nullptr;

RSDK::UnknownInfo *RSDK::unknownInfo = nullptr;

RSDK::ScreenInfo *RSDK::screenInfo = nullptr;
#endif
