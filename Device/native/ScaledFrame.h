//-------------------------------------------------------------------------------
// Copyright (c) 2024 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

// \brief 

#pragma once

#include <cstdlib>

#include "GUI/Canvas.h"
#include "PLT/Frame.h"
#include "PLT/Event.h"

template <unsigned WIDTH, unsigned HEIGHT, unsigned SCALE = 3, unsigned BORDER = 0>
class ScaledFrame : public GUI::Canvas
{
public:
   ScaledFrame(const char* title_)
      : GUI::Canvas(WIDTH, HEIGHT)
      , frame(title_, WIDTH * SCALE + 2 * BORDER, HEIGHT * SCALE + 2 * BORDER)
   {
   }

   static unsigned getWidth() { return WIDTH; }

   static unsigned getHeight() { return HEIGHT; }

private:
   void canvasClear(STB::Colour colour) override
   {
      for(int32_t y = 0; y < frame.getHeight(); y++)
      { 
         frame.span(colour, 0, y, frame.getWidth());
      }
   }

   void canvasPoint(STB::Colour colour, int32_t x_, int32_t y_) override
   {
      for(unsigned i = 0; i < SCALE; ++i)
      {
         frame.span(colour, BORDER + x_ * SCALE, BORDER + y_ * SCALE + i, BORDER + (x_ + 1) * SCALE);
      }
   }

   void canvasRefresh(int32_t x1, int32_t y1, int32_t x2, int32_t y2) override
   {
      frame.refresh();

      PLT::Event::Message event;
      PLT::Event::poll(event);

      if (event.type == PLT::Event::QUIT)
         exit(0);
   }

   PLT::Frame frame;
};
