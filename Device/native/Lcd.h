//-------------------------------------------------------------------------------
// Copyright (c) 2024 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

// \brief Simulated 16x2 Alphanumeric LCD interface

#pragma once

#include "GUI/Font/Lcd.h"

#include "Panel.h"

template <unsigned COLS, unsigned ROWS, unsigned SCALE = 4>
class Lcd
{
public:
   Lcd() = default;

   void progChar(unsigned ch, const uint8_t* bitmap_)
   {
      for(unsigned i = 0; i < 8; ++i)
         image[ch & 0x7][i] = bitmap_[i] << 3;
   }

   void move(unsigned col_, unsigned row_)
   {
      col = col_;
      row = row_;
   }

   void print(const char* text)
   {
      while(*text != '\0')
         writeChar(*text++);

      draw();
   }

   void putchar(char ch)
   {
      writeChar(ch);

      draw();
   }

private:
   void writeChar(char ch)
   {
      text[row][col] = ch;
      if (++col == COLS)
      {
         col = 0;
         if (++row == ROWS)
            row = 0;
      }
   }

   void draw()
   {
      panel.clear(BGCOL);

      for(unsigned row = 0; row < ROWS; ++row)
      {
         for(unsigned col = 0; col < COLS; ++col)
         {
            char ch = text[row][col];

            if (ch < 16)
            {
               panel.template drawAlphaMap<1>(FGCOL, 0x000000, 1 + col * 6, 1 + row * 9,
                                              6, 8, &image[unsigned(ch & 7)][0]);
            }
            else
            {
               panel.drawChar(FGCOL, 0x000000, 1 + col * 6, 1 + row * 9,
                              &GUI::font_lcd, ch);
            }
         }
      }

      panel.refresh();
      panel.eventPoll();
   }

   static const STB::Colour BGCOL = STB::RGB(0xC0, 0xC0, 0xC0);
   static const STB::Colour FGCOL = STB::RGB(0x00, 0x00, 0x00);

   static const unsigned WIDTH  = COLS * 6 + 1;
   static const unsigned HEIGHT = ROWS * 9 + 1;

   Panel<WIDTH,HEIGHT,SCALE> panel{};

   unsigned col{0};
   unsigned row{0};
   char     text[ROWS][COLS];
   uint8_t  image[8][8];
};
