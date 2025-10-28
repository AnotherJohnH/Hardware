//-------------------------------------------------------------------------------
// Copyright (c) 2024 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

// \brief E-paper interface

#pragma once

#if defined(HW_EPAPER_WAVESHARE)

#include "MTL/EPaper_WS2_13_V3.h"

#elif defined(HW_EPAPER_BADGER2040)

#include "MTL/badger2040.h"

#elif defined(HW_EPAPER_NATIVE)

#include "native/ScaledFrame.h"

#endif

namespace hw {

#if defined(HW_EPAPER_WAVESHARE)

using EPaper = MTL::EPaper_WS2_13_V3;

#elif defined(HW_EPAPER_BADGER2040)

using EPaper = MTL::badger2040::EPaper;

#elif defined(HW_EPAPER_NATIVE)

class EPaper
{
public:
   static constexpr unsigned WIDTH  = 296;
   static constexpr unsigned HEIGHT = 128;

   using FakePaper = ScaledFrame<WIDTH, HEIGHT, /* SCALE */ 3, /* BORDER */ 16>;

   class Canvas : public FakePaper
   {
   public:
      Canvas() : FakePaper("simulated E-paper") {}
   };

   static constexpr unsigned getWidth() { return WIDTH; }

   static constexpr unsigned getHeight() { return HEIGHT; }
};

#endif

} // namespace hw
