//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#include <cstdio>
#include <unistd.h>

#include "GUI/Font/Teletext.h"
#include "STB/Colour.h"

#include "Hardware/picoGame/Config.h"

inline const STB::Colour WHITE = STB::RGB(0xFF, 0xFF, 0xFF);
inline const STB::Colour BLACK = STB::RGB(0x00, 0x00, 0x00);

static hw::Led             led;
static hw::Buttons         buttons{/* enable_irq */ true};
static hw::Display         display{};
static hw::Display::Canvas canvas{};

extern "C" void IRQ_IO_BANK0() { buttons.irq(); }

int main()
{
   display.setBrightness(0xC0);

   led = false;

   canvas.clear(STB::BLACK);
   canvas.drawText(STB::WHITE, STB::BLACK, 10, 10, &GUI::font_teletext18, "Hello, world!");
   canvas.refresh();

   while(true)
   {
      unsigned index;
      bool     down;

      if (buttons.popEvent(index, down))
      {
         led = not led;
      }

      usleep(50000);
   }

   return 0;
}
