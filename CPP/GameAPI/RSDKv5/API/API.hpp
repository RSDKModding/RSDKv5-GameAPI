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
RSDK_FORCE_INLINE void *GetFunction(const char *funcName) { return RSDKTable->GetAPIFunction(funcName); }
#endif

#if RETRO_REV02
RSDK_FORCE_INLINE int32 GetUserLanguage() { return APITable->GetUserLanguage(); }
RSDK_FORCE_INLINE bool32 GetConfirmButtonFlip() { return APITable->GetConfirmButtonFlip(); }
RSDK_FORCE_INLINE void ExitGame() { APITable->ExitGame(); }
RSDK_FORCE_INLINE void LaunchManual() { APITable->LaunchManual(); }
#if RETRO_REV0U
RSDK_FORCE_INLINE int32 GetDefaultGamepadType() { return APITable->GetDefaultGamepadType(); }
#endif
RSDK_FORCE_INLINE bool32 IsOverlayEnabled(uint32 inputID) { return APITable->IsOverlayEnabled(inputID); }
RSDK_FORCE_INLINE bool32 CheckDLC(int32 dlc) { return APITable->CheckDLC(dlc); }
#if RETRO_USE_EGS
RSDK_FORCE_INLINE bool32 SetupExtensionOverlay() { return APITable->SetupExtensionOverlay(); }
RSDK_FORCE_INLINE bool32 CanShowExtensionOverlay(int32 overlay) { return APITable->CanShowExtensionOverlay(overlay); }
#endif
RSDK_FORCE_INLINE bool32 ShowExtensionOverlay(int32 overlay) { return APITable->ShowExtensionOverlay(overlay); }
#if RETRO_USE_EGS
RSDK_FORCE_INLINE bool32 CanShowAltExtensionOverlay(int32 overlay) { return APITable->CanShowAltExtensionOverlay(overlay); }
RSDK_FORCE_INLINE bool32 ShowAltExtensionOverlay(int32 overlay) { return APITable->ShowAltExtensionOverlay(overlay); }
RSDK_FORCE_INLINE int32 GetConnectingStringID() { return APITable->GetConnectingStringID(); }
RSDK_FORCE_INLINE bool32 ShowLimitedVideoOptions(int32 id) { return APITable->ShowLimitedVideoOptions(id); }
#endif

#endif

} // namespace API
} // namespace RSDK