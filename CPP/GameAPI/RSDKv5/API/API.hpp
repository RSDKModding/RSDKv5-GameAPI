#pragma once

#include "../Types.hpp"

#include "Achievements.hpp"
#include "Leaderboards.hpp"
#include "Stats.hpp"
#include "RichPresence.hpp"
#include "UserStorage.hpp"

namespace RSDK
{
namespace API
{

#if !RETRO_REV02
void *GetFunction(const char *funcName) { return RSDKTable->GetAPIFunction(funcName); }
#endif

#if RETRO_REV02
inline int32 GetUserLanguage() { return APITable->GetUserLanguage(); }
inline bool32 GetConfirmButtonFlip() { return APITable->GetConfirmButtonFlip(); }
inline void ExitGame() { APITable->ExitGame(); }
inline void LaunchManual() { APITable->LaunchManual(); }
#if RETRO_REV0U
inline int32 GetDefaultGamepadType() { return APITable->GetDefaultGamepadType(); }
#endif
inline bool32 IsOverlayEnabled(uint32 inputID) { return APITable->IsOverlayEnabled(inputID); }
inline bool32 CheckDLC(int32 dlc) { return APITable->CheckDLC(dlc); }
#if RETRO_USE_EGS
inline bool32 SetupExtensionOverlay() { return APITable->SetupExtensionOverlay(); }
inline bool32 CanShowExtensionOverlay(int32 overlay) { return APITable->CanShowExtensionOverlay(overlay); }
#endif
inline bool32 ShowExtensionOverlay(int32 overlay) { return APITable->ShowExtensionOverlay(overlay); }
#if RETRO_USE_EGS
inline bool32 CanShowAltExtensionOverlay(int32 overlay) { return APITable->CanShowAltExtensionOverlay(overlay); }
inline bool32 ShowAltExtensionOverlay(int32 overlay) { return APITable->ShowAltExtensionOverlay(overlay); }
inline int32 GetConnectingStringID() { return APITable->GetConnectingStringID(); }
inline void ShowLimitedVideoOptions(int32 id) { return APITable->ShowLimitedVideoOptions(id); }
#endif

#endif

} // namespace API
} // namespace RSDK