#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

namespace RSDK
{

namespace Input
{

enum InputIDs {
    INPUT_UNASSIGNED = -2,
    INPUT_AUTOASSIGN = -1,
    INPUT_NONE       = 0,
};

enum InputSlotIDs {
    CONT_ANY,
    CONT_P1,
    CONT_P2,
    CONT_P3,
    CONT_P4,
};

enum InputDeviceTypes {
    DEVICE_TYPE_NONE,
    DEVICE_TYPE_KEYBOARD,
    DEVICE_TYPE_CONTROLLER,
    DEVICE_TYPE_UNKNOWN,
    DEVICE_TYPE_STEAMOVERLAY,
};

enum InputDeviceIDs {
    DEVICE_KEYBOARD,
    DEVICE_XBOX,
    DEVICE_PS4,
    DEVICE_SATURN,
    DEVICE_SWITCH_HANDHELD,
    DEVICE_SWITCH_JOY_GRIP,
    DEVICE_SWITCH_JOY_L,
    DEVICE_SWITCH_JOY_R,
    DEVICE_SWITCH_PRO,
};

enum InputDeviceAPIs {
    DEVICE_API_NONE,
    DEVICE_API_KEYBOARD,
    DEVICE_API_XINPUT,
    DEVICE_API_RAWINPUT,
    DEVICE_API_STEAM,
};

enum KeyMappings {
    KEYMAP_AUTO_MAPPING                    = -1,
    KEYMAP_NO_MAPPING                      = 0,
    KEYMAP_LBUTTON                         = 0x01,
    KEYMAP_RBUTTON                         = 0x02,
    KEYMAP_CANCEL                          = 0x03,
    KEYMAP_MBUTTON                         = 0x04,
    KEYMAP_XBUTTON1                        = 0x05,
    KEYMAP_XBUTTON2                        = 0x06,
    KEYMAP_BACK                            = 0x08,
    KEYMAP_TAB                             = 0x09,
    KEYMAP_CLEAR                           = 0x0C,
    KEYMAP_RETURN                          = 0x0D,
    KEYMAP_SHIFT                           = 0x10,
    KEYMAP_CONTROL                         = 0x11,
    KEYMAP_MENU                            = 0x12,
    KEYMAP_PAUSE                           = 0x13,
    KEYMAP_CAPITAL                         = 0x14,
    KEYMAP_KANA                            = 0x15,
    KEYMAP_HANGEUL                         = 0x15,
    KEYMAP_HANGUL                          = 0x15,
    KEYMAP_JUNJA                           = 0x17,
    KEYMAP_FINAL                           = 0x18,
    KEYMAP_HANJA                           = 0x19,
    KEYMAP_KANJI                           = 0x19,
    KEYMAP_ESCAPE                          = 0x1B,
    KEYMAP_CONVERT                         = 0x1C,
    KEYMAP_NONCONVERT                      = 0x1D,
    KEYMAP_ACCEPT                          = 0x1E,
    KEYMAP_MODECHANGE                      = 0x1F,
    KEYMAP_SPACE                           = 0x20,
    KEYMAP_PRIOR                           = 0x21,
    KEYMAP_NEXT                            = 0x22,
    KEYMAP_END                             = 0x23,
    KEYMAP_HOME                            = 0x24,
    KEYMAP_LEFT                            = 0x25,
    KEYMAP_UP                              = 0x26,
    KEYMAP_RIGHT                           = 0x27,
    KEYMAP_DOWN                            = 0x28,
    KEYMAP_SELECT                          = 0x29,
    KEYMAP_PRINT                           = 0x2A,
    KEYMAP_EXECUTE                         = 0x2B,
    KEYMAP_SNAPSHOT                        = 0x2C,
    KEYMAP_INSERT                          = 0x2D,
    KEYMAP_DELETE                          = 0x2E,
    KEYMAP_HELP                            = 0x2F,
    KEYMAP_0                               = 0x30,
    KEYMAP_1                               = 0x31,
    KEYMAP_2                               = 0x32,
    KEYMAP_3                               = 0x33,
    KEYMAP_4                               = 0x34,
    KEYMAP_5                               = 0x35,
    KEYMAP_6                               = 0x36,
    KEYMAP_7                               = 0x37,
    KEYMAP_8                               = 0x38,
    KEYMAP_9                               = 0x39,
    KEYMAP_A                               = 0x41,
    KEYMAP_B                               = 0x42,
    KEYMAP_C                               = 0x43,
    KEYMAP_D                               = 0x44,
    KEYMAP_E                               = 0x45,
    KEYMAP_F                               = 0x46,
    KEYMAP_G                               = 0x47,
    KEYMAP_H                               = 0x48,
    KEYMAP_I                               = 0x49,
    KEYMAP_J                               = 0x4A,
    KEYMAP_K                               = 0x4B,
    KEYMAP_L                               = 0x4C,
    KEYMAP_M                               = 0x4D,
    KEYMAP_N                               = 0x4E,
    KEYMAP_O                               = 0x4F,
    KEYMAP_P                               = 0x50,
    KEYMAP_Q                               = 0x51,
    KEYMAP_R                               = 0x52,
    KEYMAP_S                               = 0x53,
    KEYMAP_T                               = 0x54,
    KEYMAP_U                               = 0x55,
    KEYMAP_V                               = 0x56,
    KEYMAP_W                               = 0x57,
    KEYMAP_X                               = 0x58,
    KEYMAP_Y                               = 0x59,
    KEYMAP_Z                               = 0x5A,
    KEYMAP_LWIN                            = 0x5B,
    KEYMAP_RWIN                            = 0x5C,
    KEYMAP_APPS                            = 0x5D,
    KEYMAP_SLEEP                           = 0x5F,
    KEYMAP_NUMPAD0                         = 0x60,
    KEYMAP_NUMPAD1                         = 0x61,
    KEYMAP_NUMPAD2                         = 0x62,
    KEYMAP_NUMPAD3                         = 0x63,
    KEYMAP_NUMPAD4                         = 0x64,
    KEYMAP_NUMPAD5                         = 0x65,
    KEYMAP_NUMPAD6                         = 0x66,
    KEYMAP_NUMPAD7                         = 0x67,
    KEYMAP_NUMPAD8                         = 0x68,
    KEYMAP_NUMPAD9                         = 0x69,
    KEYMAP_MULTIPLY                        = 0x6A,
    KEYMAP_ADD                             = 0x6B,
    KEYMAP_SEPARATOR                       = 0x6C,
    KEYMAP_SUBTRACT                        = 0x6D,
    KEYMAP_DECIMAL                         = 0x6E,
    KEYMAP_DIVIDE                          = 0x6F,
    KEYMAP_F1                              = 0x70,
    KEYMAP_F2                              = 0x71,
    KEYMAP_F3                              = 0x72,
    KEYMAP_F4                              = 0x73,
    KEYMAP_F5                              = 0x74,
    KEYMAP_F6                              = 0x75,
    KEYMAP_F7                              = 0x76,
    KEYMAP_F8                              = 0x77,
    KEYMAP_F9                              = 0x78,
    KEYMAP_F10                             = 0x79,
    KEYMAP_F11                             = 0x7A,
    KEYMAP_F12                             = 0x7B,
    KEYMAP_F13                             = 0x7C,
    KEYMAP_F14                             = 0x7D,
    KEYMAP_F15                             = 0x7E,
    KEYMAP_F16                             = 0x7F,
    KEYMAP_F17                             = 0x80,
    KEYMAP_F18                             = 0x81,
    KEYMAP_F19                             = 0x82,
    KEYMAP_F20                             = 0x83,
    KEYMAP_F21                             = 0x84,
    KEYMAP_F22                             = 0x85,
    KEYMAP_F23                             = 0x86,
    KEYMAP_F24                             = 0x87,
    KEYMAP_NAVIGATION_VIEW                 = 0x88,
    KEYMAP_NAVIGATION_MENU                 = 0x89,
    KEYMAP_NAVIGATION_UP                   = 0x8A,
    KEYMAP_NAVIGATION_DOWN                 = 0x8B,
    KEYMAP_NAVIGATION_LEFT                 = 0x8C,
    KEYMAP_NAVIGATION_RIGHT                = 0x8D,
    KEYMAP_NAVIGATION_ACCEPT               = 0x8E,
    KEYMAP_NAVIGATION_CANCEL               = 0x8F,
    KEYMAP_NUMLOCK                         = 0x90,
    KEYMAP_SCROLL                          = 0x91,
    KEYMAP_OEM_NEC_EQUAL                   = 0x92,
    KEYMAP_OEM_FJ_JISHO                    = 0x92,
    KEYMAP_OEM_FJ_MASSHOU                  = 0x93,
    KEYMAP_OEM_FJ_TOUROKU                  = 0x94,
    KEYMAP_OEM_FJ_LOYA                     = 0x95,
    KEYMAP_OEM_FJ_ROYA                     = 0x96,
    KEYMAP_LSHIFT                          = 0xA0,
    KEYMAP_RSHIFT                          = 0xA1,
    KEYMAP_LCONTROL                        = 0xA2,
    KEYMAP_RCONTROL                        = 0xA3,
    KEYMAP_LMENU                           = 0xA4,
    KEYMAP_RMENU                           = 0xA5,
    KEYMAP_BROWSER_BACK                    = 0xA6,
    KEYMAP_BROWSER_FORWARD                 = 0xA7,
    KEYMAP_BROWSER_REFRESH                 = 0xA8,
    KEYMAP_BROWSER_STOP                    = 0xA9,
    KEYMAP_BROWSER_SEARCH                  = 0xAA,
    KEYMAP_BROWSER_FAVORITES               = 0xAB,
    KEYMAP_BROWSER_HOME                    = 0xAC,
    KEYMAP_VOLUME_MUTE                     = 0xAD,
    KEYMAP_VOLUME_DOWN                     = 0xAE,
    KEYMAP_VOLUME_UP                       = 0xAF,
    KEYMAP_MEDIA_NEXT_TRACK                = 0xB0,
    KEYMAP_MEDIA_PREV_TRACK                = 0xB1,
    KEYMAP_MEDIA_STOP                      = 0xB2,
    KEYMAP_MEDIA_PLAY_PAUSE                = 0xB3,
    KEYMAP_LAUNCH_MAIL                     = 0xB4,
    KEYMAP_LAUNCH_MEDIA_SELECT             = 0xB5,
    KEYMAP_LAUNCH_APP1                     = 0xB6,
    KEYMAP_LAUNCH_APP2                     = 0xB7,
    KEYMAP_OEM_1                           = 0xBA,
    KEYMAP_OEM_PLUS                        = 0xBB,
    KEYMAP_OEM_COMMA                       = 0xBC,
    KEYMAP_OEM_MINUS                       = 0xBD,
    KEYMAP_OEM_PERIOD                      = 0xBE,
    KEYMAP_OEM_2                           = 0xBF,
    KEYMAP_OEM_3                           = 0xC0,
    KEYMAP_GAMEPAD_A                       = 0xC3,
    KEYMAP_GAMEPAD_B                       = 0xC4,
    KEYMAP_GAMEPAD_X                       = 0xC5,
    KEYMAP_GAMEPAD_Y                       = 0xC6,
    KEYMAP_GAMEPAD_RIGHT_SHOULDER          = 0xC7,
    KEYMAP_GAMEPAD_LEFT_SHOULDER           = 0xC8,
    KEYMAP_GAMEPAD_LEFT_TRIGGER            = 0xC9,
    KEYMAP_GAMEPAD_RIGHT_TRIGGER           = 0xCA,
    KEYMAP_GAMEPAD_DPAD_UP                 = 0xCB,
    KEYMAP_GAMEPAD_DPAD_DOWN               = 0xCC,
    KEYMAP_GAMEPAD_DPAD_LEFT               = 0xCD,
    KEYMAP_GAMEPAD_DPAD_RIGHT              = 0xCE,
    KEYMAP_GAMEPAD_MENU                    = 0xCF,
    KEYMAP_GAMEPAD_VIEW                    = 0xD0,
    KEYMAP_GAMEPAD_LEFT_THUMBSTICK_BUTTON  = 0xD1,
    KEYMAP_GAMEPAD_RIGHT_THUMBSTICK_BUTTON = 0xD2,
    KEYMAP_GAMEPAD_LEFT_THUMBSTICK_UP      = 0xD3,
    KEYMAP_GAMEPAD_LEFT_THUMBSTICK_DOWN    = 0xD4,
    KEYMAP_GAMEPAD_LEFT_THUMBSTICK_RIGHT   = 0xD5,
    KEYMAP_GAMEPAD_LEFT_THUMBSTICK_LEFT    = 0xD6,
    KEYMAP_GAMEPAD_RIGHT_THUMBSTICK_UP     = 0xD7,
    KEYMAP_GAMEPAD_RIGHT_THUMBSTICK_DOWN   = 0xD8,
    KEYMAP_GAMEPAD_RIGHT_THUMBSTICK_RIGHT  = 0xD9,
    KEYMAP_GAMEPAD_RIGHT_THUMBSTICK_LEFT   = 0xDA,
    KEYMAP_OEM_4                           = 0xDB,
    KEYMAP_OEM_5                           = 0xDC,
    KEYMAP_OEM_6                           = 0xDD,
    KEYMAP_OEM_7                           = 0xDE,
    KEYMAP_OEM_8                           = 0xDF,
    KEYMAP_OEM_AX                          = 0xE1,
    KEYMAP_OEM_102                         = 0xE2,
    KEYMAP_ICO_HELP                        = 0xE3,
    KEYMAP_ICO_00                          = 0xE4,
    KEYMAP_PROCESSKEY                      = 0xE5,
    KEYMAP_ICO_CLEAR                       = 0xE6,
    KEYMAP_PACKET                          = 0xE7,
    KEYMAP_OEM_RESET                       = 0xE9,
    KEYMAP_OEM_JUMP                        = 0xEA,
    KEYMAP_OEM_PA1                         = 0xEB,
    KEYMAP_OEM_PA2                         = 0xEC,
    KEYMAP_OEM_PA3                         = 0xED,
    KEYMAP_OEM_WSCTRL                      = 0xEE,
    KEYMAP_OEM_CUSEL                       = 0xEF,
    KEYMAP_OEM_ATTN                        = 0xF0,
    KEYMAP_OEM_FINISH                      = 0xF1,
    KEYMAP_OEM_COPY                        = 0xF2,
    KEYMAP_OEM_AUTO                        = 0xF3,
    KEYMAP_OEM_ENLW                        = 0xF4,
    KEYMAP_OEM_BACKTAB                     = 0xF5,
    KEYMAP_ATTN                            = 0xF6,
    KEYMAP_CRSEL                           = 0xF7,
    KEYMAP_EXSEL                           = 0xF8,
    KEYMAP_EREOF                           = 0xF9,
    KEYMAP_PLAY                            = 0xFA,
    KEYMAP_ZOOM                            = 0xFB,
    KEYMAP_NONAME                          = 0xFC,
    KEYMAP_PA1                             = 0xFD,
    KEYMAP_OEM_CLEAR                       = 0xFE,
};

#if RETRO_REV02
inline uint32 GetInputDeviceID(uint8 controllerID) { return RSDKTable->GetInputDeviceID(controllerID); }
inline uint32 GetFilteredInputDeviceID(bool32 confirmOnly, bool32 unassignedOnly, uint32 maxInactiveTimer)
{
    return RSDKTable->GetFilteredInputDeviceID(confirmOnly, unassignedOnly, maxInactiveTimer);
}
inline int32 GetInputDeviceType(uint32 deviceID) { return RSDKTable->GetInputDeviceType(deviceID); }
inline bool32 IsInputDeviceAssigned(uint32 deviceID) { return RSDKTable->IsInputDeviceAssigned(deviceID); }
inline int32 GetInputDeviceUnknown(uint32 deviceID) { return RSDKTable->GetInputDeviceUnknown(deviceID); }
inline int32 InputDeviceUnknown1(uint32 deviceID, int32 unknown1, int32 unknown2)
{
    return RSDKTable->InputDeviceUnknown1(deviceID, unknown1, unknown2);
}
inline int32 InputDeviceUnknown2(uint32 deviceID, int32 unknown1, int32 unknown2)
{
    return RSDKTable->InputDeviceUnknown2(deviceID, unknown1, unknown2);
}
inline int32 GetInputSlotUnknown(uint8 inputSlot) { return RSDKTable->GetInputSlotUnknown(inputSlot); }
inline int32 InputSlotUnknown1(uint8 inputSlot, int32 unknown1, int32 unknown2)
{
    return RSDKTable->InputSlotUnknown1(inputSlot, unknown1, unknown2);
}
inline int32 InputSlotUnknown2(uint8 inputSlot, int32 unknown1, int32 unknown2)
{
    return RSDKTable->InputSlotUnknown2(inputSlot, unknown1, unknown2);
}
inline void AssignInputSlotToDevice(uint8 inputSlot, uint32 inputID) { RSDKTable->AssignInputSlotToDevice(inputSlot, inputID); }
inline bool32 IsInputSlotAssigned(uint8 inputSlot) { return RSDKTable->IsInputSlotAssigned(inputSlot); }
inline void ResetInputSlotAssignments() { RSDKTable->ResetInputSlotAssignments(); }
#endif

#if !RETRO_REV02
inline void GetUnknownInputValue(int32 inputSlot, int32 type, int32 *value) { RSDKTable->GetUnknownInputValue(inputSlot, type, value); }
#endif

} // namespace Input

} // namespace RSDK