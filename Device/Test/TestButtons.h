//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#include "Test.h"

#include <cstdio>

namespace hw {

inline NOINLINE void testButtons(TestPhase phase_)
{
   static hw::Buttons buttons{};

   switch(phase_)
   {
   case DECL:
      break;

   case INFO:
      printf("Buttons: Only build and declare for now\n");
      break;

   case START:
      break;

   case RUN:
      {
         unsigned index{};
         bool     pressed{};

         if (buttons.popEvent(index, pressed))
         {
            printf("BTN%u %s\n", index + 1, pressed ? "DN" : "UP");
         }
      }
      break;
   }
}

} // namespace hw
