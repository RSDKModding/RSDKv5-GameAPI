#pragma once

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