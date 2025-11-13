//-------------------------------------------------------------------------------
// Copyright (c) 2024 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

// \brief picoGame hardware configurations

#pragma once

#if not defined(HW_NATIVE)
#include "MTL/Config.h"
#endif

//------------------------------------------------------------------------------
#if defined(HW_TUFTY2040)

#define HW_DESCR          "tufty2040"

#define HW_USB_FILE_DEVICE
#define HW_DISPLAY_TUFTY2040
#define HW_LED
#define HW_BUTTONS_TUFTY2040

//------------------------------------------------------------------------------
#elif defined(HW_NATIVE)

#define HW_DESCR          "native"

#define HW_USB_FILE_NATIVE
#define HW_DISPLAY_NATIVE
#define HW_DISPLAY_WIDTH 320
#define HW_DISPLAY_HEIGHT 256
#define HW_LED_NATIVE
#define HW_BUTTONS_NATIVE

//------------------------------------------------------------------------------
#else

#error "Target hardware not specified"

#endif

//==============================================================================

#include "Hardware/Device/Display.h"
#include "Hardware/Device/Led.h"
#include "Hardware/Device/UsbFile.h"
#include "Hardware/Device/Buttons.h"
