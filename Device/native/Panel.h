//-------------------------------------------------------------------------------
// Copyright (c) 2024 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

// \brief 

#pragma once

#include "GUI/Canvas.h"
#include "PLT/Event.h"

#include "Rack.h"

template <unsigned WIDTH, unsigned HEIGHT, unsigned SCALE = 4>
class Panel : public GUI::Canvas
{
public:
   Panel()
      : GUI::Canvas(WIDTH, HEIGHT)
   {
      rack = Rack::alloc(WIDTH * SCALE, HEIGHT * SCALE, ox, oy);
   }

   static unsigned getWidth() { return WIDTH; }
   static unsigned getHeight() { return HEIGHT; }

   void eventPoll()
   {
      PLT::Event::Message event;
      PLT::Event::poll(event);

      if (event.type == PLT::Event::QUIT)
         exit(0);
   }

private:
   void canvasClear(STB::Colour colour) override
   {
      for(unsigned y = 0; y < HEIGHT * SCALE; y++)
      { 
         rack->frame.span(colour, ox, oy + y, ox + WIDTH * SCALE);
      }
   }

   void canvasPoint(STB::Colour colour, int32_t x_, int32_t y_) override
   {
      for(unsigned i = 0; i < SCALE; ++i)
      {
         rack->frame.span(colour, ox + x_ * SCALE, oy + y_ * SCALE + i,
                                  ox + (x_ + 1) * SCALE);
      }
   }

   void canvasRefresh(int32_t x1, int32_t y1, int32_t x2, int32_t y2) override
   {
      rack->frame.refresh();
   }

   unsigned ox, oy;
   Rack*    rack;
};
