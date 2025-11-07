//-------------------------------------------------------------------------------
// Copyright (c) 2024 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

// \brief Simulated LED interface

#pragma once

#include "Panel.h"

template <unsigned SCALE = 4>
class Led
{
public:
   Led() = default;

   bool operator=(bool state_)
   {
      state = state_;

      draw();

      return state;
   }

   operator bool() const { return state; }

private:
   void draw()
   {
      panel.clear(state ? FGCOL : BGCOL);
   }

   static const STB::Colour BGCOL = STB::RGB(0x00, 0x00, 0x00);
   static const STB::Colour FGCOL = STB::RGB(0xFF, 0x00, 0x00);

   static const unsigned WIDTH  = 8;
   static const unsigned HEIGHT = 8;

   Panel<WIDTH,HEIGHT,SCALE> panel{};

   bool state{false};
};
