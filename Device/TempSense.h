//-------------------------------------------------------------------------------
// Copyright (c) 2024 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

// \brief Temperature sensor interface

#pragma once

#if defined(HW_TEMP_SENSE_P21_P22_MCP9808)

#include "MTL/TempSens_MCP9808.h"
#include "MTL/rp2040/I2C.h"

#elif defined(HW_TEMP_SENSE_BADGER_MCP9808)

#include "MTL/TempSens_MCP9808.h"

#elif defined(HW_TEMP_SENSE_NATIVE)

#include "native/TempSense.h"

#endif

namespace hw {

#if defined(HW_TEMP_SENSE_P21_P22_MCP9808)

using TempSense = MTL::TempSens_MCP9808<MTL::I2C0_P21_P22>;

#elif defined(HW_TEMP_SENSE_BADGER_MCP9808)

using TempSense = MTL::TempSens_MCP9808<MTL::badger2040::I2C_QwSt>;

#elif defined(HW_TEMP_SENSE_NATIVE)

using TempSense = ::TempSens;

#endif

} // namespace hw
