//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#include <cstdio>
#include <unistd.h>

#include "GUI/Font/Teletext.h"

#include "Hardware/picoSense/Config.h"

inline const STB::Colour WHITE = STB::RGB(0xC0, 0xC0, 0xC0);
inline const STB::Colour BLACK = STB::RGB(0x00, 0x00, 0x00);

static hw::Led            led;
static hw::Buttons        buttons{/* enable_irq */ true};
static hw::EPaper::Canvas epaper;
static hw::TempSense      sensor;

extern "C" void IRQ_IO_BANK0() { buttons.irq(); }

int main()
{
   led = false;

   epaper.clear(WHITE);
   epaper.drawText(BLACK, WHITE, 10, 10, &GUI::font_teletext18, "Hello, world!");
   epaper.refresh();

   sensor.start();

   while(true)
   {
      unsigned index;
      bool     down;

      if (buttons.popEvent(index, down))
      {
         led = not led;

         if (down)
         {
            signed value = sensor.read() * 10 / 256;

            const char DEGREE_SYMBOL = 0x7F;

            char text[32];
            snprintf(text, sizeof(text), "%d.%u%cC\n",
                     value / 10, value % 10, DEGREE_SYMBOL);

            epaper.clear(WHITE);
            epaper.drawText(BLACK, WHITE, 10, 10, &GUI::font_teletext18, text);
            epaper.refresh();
         }
      }

      usleep(50000);
   }

   return 0;
}
