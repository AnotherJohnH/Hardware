//-------------------------------------------------------------------------------
// Copyright (c) 2024 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

// \brief picoSense hardware configurations

#pragma once

#if not defined(HW_NATIVE)
#include "MTL/Config.h"
#endif

//------------------------------------------------------------------------------
#if defined(HW_WAVESHARE_EPAPER)

#define HW_DESCR          "WaveShare E-Paper"

#define HW_USB_FILE_DEVICE
#define HW_EPAPER_WAVESHARE
#define HW_TEMP_SENSE_P21_P22_MCP9808
#define HW_LED
#define HW_RTC

//------------------------------------------------------------------------------
#elif defined(HW_BADGER2040)

#define HW_DESCR          "Badger 2040"

#define HW_USB_FILE_DEVICE
#define HW_EPAPER_BADGER2040
#define HW_TEMP_SENSE_BADGER_MCP9808
#define HW_LED
#define HW_RTC

//------------------------------------------------------------------------------
#elif defined(HW_NATIVE)

#define HW_DESCR          "native"

#define HW_USB_FILE_NATIVE
#define HW_EPAPER_NATIVE
#define HW_TEMP_SENSE_NATIVE
#define HW_LED_NATIVE
#define HW_RTC_NATIVE

//------------------------------------------------------------------------------
#else

#error "Target hardware not specified"

#endif

//==============================================================================

#include "Hardware/Device/EPaper.h"
#include "Hardware/Device/TempSense.h"
#include "Hardware/Device/Led.h"
#include "Hardware/Device/UsbFile.h"
#include "Hardware/Device/Rtc.h"
