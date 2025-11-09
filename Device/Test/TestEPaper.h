//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#include "Test.h"

#include <cstdio>

namespace hw {

inline NOINLINE void testEPaper(TestPhase phase_)
{
   static hw::EPaper::Canvas epaper{};
   static const STB::Colour WHITE = STB::RGB(0xC0, 0xC0, 0xC0);
   static const STB::Colour BLACK = STB::RGB(0x00, 0x00, 0x00);

   switch(phase_)
   {
   case DECL:
      break;

   case INFO:
      printf("EPaper: \n");
      break;

   case START:
      epaper.clear(WHITE);
      epaper.drawLine(BLACK, 0, 0, epaper.getWidth(), epaper.getHeight());
      epaper.drawLine(BLACK, 0, epaper.getHeight(), epaper.getWidth(), 0);
      epaper.refresh();
      break;

   case RUN:
      epaper.refresh();
      break;
   }
}

} // namespace hw
