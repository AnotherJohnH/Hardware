//-------------------------------------------------------------------------------
// Copyright (c) 2024 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

#include "PLT/Event.h"
#include "PLT/Frame.h"

class Rack
{
public:
    static Rack* alloc(unsigned width_, unsigned height_, unsigned& ox_, unsigned& oy_)
    {
       static Rack* rack{};

       if (rack == nullptr)
       {
          rack = new Rack(width_, height_);

          ox_ = 0;
          oy_ = 0;
       }
       else
       {
          ox_ = rack->frame.getWidth();
          oy_ = 0;

          rack->extend(width_, height_);
       }

       return rack;
    }

    void span(STB::Colour colour, unsigned x1, unsigned y, unsigned x2)
    {
       frame.span(colour, x1, y, x2);
    }

    void refresh()
    {
       frame.refresh();
    }

    void eventPoll()
    {
       PLT::Event::Message event;
       PLT::Event::poll(event);

       if (event.type == PLT::Event::QUIT)
          exit(0);
    }

private:
    Rack(unsigned width_, unsigned height_)
       : frame("Hardware - Virtual Component Rack", width_, height_)
       , max_height(height_)
    {

    }

    void extend(unsigned width_, unsigned height_)
    {
       if (height_ > max_height)
          max_height = height_;

       frame.resize(frame.getWidth() + width_, max_height);
    }

    PLT::Frame frame;
    unsigned   max_height{0};
};
