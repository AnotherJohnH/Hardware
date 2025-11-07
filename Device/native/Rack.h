//-------------------------------------------------------------------------------
// Copyright (c) 2024 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

// \brief 

#pragma once

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

    PLT::Frame frame;

private:
    Rack(unsigned width_, unsigned height_)
       : frame("Hardware - Virtual Rack", width_, height_)
    {
    }

    void extend(unsigned width_, unsigned height_)
    {
       frame.resize(frame.getWidth() + width_, frame.getHeight());
    }
};
