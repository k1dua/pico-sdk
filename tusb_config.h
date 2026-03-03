#pragma once

#define CFG_TUSB_MCU              OPT_MCU_RP2040
#define CFG_TUSB_RHPORT0_MODE     (OPT_MODE_DEVICE | OPT_MODE_HOST)
#define CFG_TUSB_OS               OPT_OS_NONE

// Device stack
#define CFG_TUD_HID               1

// Host stack
#define CFG_TUH_HID               1
#define CFG_TUH_ENUMERATION_BUFSIZE 256
#define CFG_TUH_HID_EPIN_BUFSIZE  64
#define CFG_TUH_HID_EPOUT_BUFSIZE 64