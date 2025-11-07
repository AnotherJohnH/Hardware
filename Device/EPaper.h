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

#include "native/Panel.h"

#endif

namespace hw {

#if defined(HW_EPAPER_WAVESHARE)

class EPaper : public MTL::EPaper_WS2_13_V3
{
public:
   EPaper()
   {
      MTL::config.gpio(PIN_DC,  ">(e-paper)  DC");
      MTL::config.gpio(PIN_CS,  ">(e-paper)  CS");
      MTL::config.gpio(PIN_RST, ">(e-paper) RST");
      MTL::config.gpio(PIN_BSY, "<(e-paper) BSY");

      MTL::config.gpio(SPI::PIN_CS,   ">(e-paper) SPI   CS");
      MTL::config.gpio(SPI::PIN_CLK,  ">(e-paper) SPI  CLK");
      MTL::config.gpio(SPI::PIN_MOSI, ">(e-paper) SPI MOSI");
      MTL::config.gpio(SPI::PIN_MISO, "<(e-paper) SPI MISO");
   }
};

#elif defined(HW_EPAPER_BADGER2040)

class EPaper : public MTL::badger2040::EPaper
{
public:
   EPaper()
   {
      MTL::config.gpio(MTL::badger2040::PIN_EPAPER_DC,  ">DC  (e-paper)");
      MTL::config.gpio(MTL::badger2040::PIN_EPAPER_CS,  ">CS  (e-paper)");
      MTL::config.gpio(MTL::badger2040::PIN_EPAPER_RST, ">RST (e-paper)");
      MTL::config.gpio(MTL::badger2040::PIN_EPAPER_BSY, "<BSY (e-paper)");

      MTL::config.gpio(MTL::badger2040::EPAPER_SPI::PIN_CS,   ">SPI CS   (e-paper)");
      MTL::config.gpio(MTL::badger2040::EPAPER_SPI::PIN_CLK,  ">SPI CLK  (e-paper)");
      MTL::config.gpio(MTL::badger2040::EPAPER_SPI::PIN_MOSI, ">SPI MOSI (e-paper)");
      MTL::config.gpio(MTL::badger2040::EPAPER_SPI::PIN_MISO, "<SPI MISO (e-paper)");
   }
};

#elif defined(HW_EPAPER_NATIVE)

class EPaper
{
public:
   EPaper() = default;

   static constexpr unsigned WIDTH  = 296;
   static constexpr unsigned HEIGHT = 128;

   using Canvas = Panel<WIDTH, HEIGHT, /* SCALE */ 3>;

   static constexpr unsigned getWidth() { return WIDTH; }
   static constexpr unsigned getHeight() { return HEIGHT; }

   unsigned var{0};
};

#endif

} // namespace hw
