/*

Copyright (C) 2017 Julian L�hr
All rights reserved.

Filename:
	DeviceInterfacePublic.h

Abstract:
	Shared types and values for the Device Interface, provided by the driver and used by the user mode dll.

*/
#pragma once

#include <initguid.h>

// {8259315A-7B87-4D02-83A3-20CBCDAD7647}
DEFINE_GUID(GUID_DEVINTERFACE_HIDWIIMOTE,
	0x8259315a, 0x7b87, 0x4d02, 0x83, 0xa3, 0x20, 0xcb, 0xcd, 0xad, 0x76, 0x47);

// IOCTLs
// 0x00-0x7FF (0-2047) reserved, 0x800-0xFFF (2048-4095) for custom use
#define FUNCTION_CODE(base, id) (0x800 | base | id)

#define HID_WIIMOTE_CTL_CODE(base, id)			CTL_CODE(FILE_DEVICE_KEYBOARD, FUNCTION_CODE(base, id), METHOD_NEITHER, FILE_ANY_ACCESS)
#define HID_WIIMOTE_BUFFERED_CTL_CODE(base, id)	CTL_CODE(FILE_DEVICE_KEYBOARD, FUNCTION_CODE(base, id), METHOD_BUFFERED, FILE_ANY_ACCESS)

// Device
#define DEVICE_IOCTL_BASE	0x000

#define IOCTL_WIIMOTE_GET_STATE				HID_WIIMOTE_BUFFERED_CTL_CODE(DEVICE_IOCTL_BASE, 0x01)
#define IOCTL_WIIMOTE_READ_STATUS			HID_WIIMOTE_BUFFERED_CTL_CODE(DEVICE_IOCTL_BASE, 0x02)

// Settings
#define SETTINGS_IOCTL_BASE 0x100

#define IOCTL_WIIMOTE_SET_MODE									HID_WIIMOTE_BUFFERED_CTL_CODE(SETTINGS_IOCTL_BASE, 0x01)
#define IOCTL_WIIMOTE_SET_ENABLE_WIIMOTE_XAXIS_ACCELEROMETER	HID_WIIMOTE_BUFFERED_CTL_CODE(SETTINGS_IOCTL_BASE, 0x02)
#define IOCTL_WIIMOTE_SET_ENABLE_WIIMOTE_YAXIS_ACCELEROMETER	HID_WIIMOTE_BUFFERED_CTL_CODE(SETTINGS_IOCTL_BASE, 0x03)
#define IOCTL_WIIMOTE_SET_SWITCH_MOUSEBUTTONS					HID_WIIMOTE_BUFFERED_CTL_CODE(SETTINGS_IOCTL_BASE, 0x04)
#define IOCTL_WIIMOTE_SET_SWITCH_TRIGGERANDSHOULDER				HID_WIIMOTE_BUFFERED_CTL_CODE(SETTINGS_IOCTL_BASE, 0x10)
#define IOCTL_WIIMOTE_SET_SPLIT_TRIGGERAXIS						HID_WIIMOTE_BUFFERED_CTL_CODE(SETTINGS_IOCTL_BASE, 0x11)
#define IOCTL_WIIMOTE_SET_MAP_TRIGGER_AS_AXIS					HID_WIIMOTE_BUFFERED_CTL_CODE(SETTINGS_IOCTL_BASE, 0x12)
#define IOCTL_WIIMOTE_SET_MAP_TRIGGER_AS_BUTTONS				HID_WIIMOTE_BUFFERED_CTL_CODE(SETTINGS_IOCTL_BASE, 0x13)

// LEDs
#define WIIMOTE_LEDS_ONE (0x10)
#define WIIMOTE_LEDS_TWO (0x20)
#define WIIMOTE_LEDS_THREE (0x40)
#define WIIMOTE_LEDS_FOUR (0x80)
#define WIIMOTE_LEDS_ALL (WIIMOTE_LEDS_FOUR | WIIMOTE_LEDS_THREE | WIIMOTE_LEDS_TWO | WIIMOTE_LEDS_ONE)

// Enumerations
typedef enum _WIIMOTE_EXTENSION { None, Nunchuck, BalanceBoard, ClassicController, ClassicControllerPro, WiiUProController, Guitar } WIIMOTE_EXTENSION, *PWIIMOTE_EXTENSION;
typedef enum _WIIMOTE_DRIVER_MODE { Gamepad, PassThrough, IRMouse, DPadMouse, GamepadAndIRMouse } WIIMOTE_DRIVER_MODE, *PWIIMOTE_DRIVER_MODE;

// IOCTL data structs
typedef struct _WIIMOTE_SETTINGS
{
	WIIMOTE_DRIVER_MODE Mode;

	BOOLEAN EnableWiimoteXAxisAccelerometer;
	BOOLEAN EnableWiimoteYAxisAcceleromenter;
	BOOLEAN SwitchMouseButtons;
	BOOLEAN SwitchTriggerAndShoulder;
	BOOLEAN SplitTriggerAxis;
	BOOLEAN MapTriggerAsAxis;
	BOOLEAN MapTriggerAsButtons;

} WIIMOTE_SETTINGS, *PWIIMOTE_SETTINGS;

typedef struct _WIIMOTE_STATUS_IOCTL_DATA
{
	UCHAR LEDs;
	UCHAR BatteryLevel;
	WIIMOTE_EXTENSION Extension;

} WIIMOTE_STATUS_IOCTL_DATA, *PWIIMOTE_STATUS_IOCTL_DATA;

typedef struct _WIIMOTE_STATE_IOCTL_DATA
{
	WIIMOTE_SETTINGS Settings;
	WIIMOTE_STATUS_IOCTL_DATA Status;

} WIIMOTE_STATE_IOCTL_DATA, *PWIIMOTE_STATE_IOCTL_DATA;