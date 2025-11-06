//-------------------------------------------------------------------------------
// Copyright (c) 2024 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

// \brief 16x2 Alphanumeric LCD interface

#pragma once

#if defined(HW_LCD_I2C)

#if defined(HW_LCD_I2C_BRIDGE)
#include "MTL/AlphaNumLcd_I2CBridge.h"
#else
#include "MTL/AlphaNumLcd_I2C.h"
#endif

#elif defined(HW_LCD_NATIVE)

#include "native/ScaledFrame.h"

#endif

namespace hw {

#if defined(HW_LCD_I2C)

class Lcd : public MTL::AlphaNumLcd<HW_LCD_I2C,
                                    /* COLS */ 16,
                                    /* ROWS */ 2>
{
public:
   Lcd()
      : MTL::AlphaNumLcd<HW_LCD_I2C,
                         /* COLS */ 16,
                         /* ROWS */ 2>{ HW_LCD_I2C_ADDR }
   {
      MTL::config.gpio(HW_LCD_I2C::SDA, ">I2C SDA (16x2 LCD)");
      MTL::config.gpio(HW_LCD_I2C::SCL, ">I2C SCL (16x2 LCD)");
   }
};

#elif defined(HW_LCD_NATIVE)

class Lcd
{
public:
   Lcd() = default;

   void progChar(unsigned ch, const uint8_t* bitmap_)
   {
      for(unsigned i = 0; i < 8; ++i)
         image[ch & 0x7][i] = bitmap_[i];
   }

   void move(unsigned col_, unsigned row_)
   {
      col = col_;
      row = row_;
   }

   void print(const char* text)
   {
      while(*text != '\0')
         putchar(*text++);
   }

   void putchar(char ch)
   {
      text[row][col] = ch;
      if (++col == COLS)
      {
         col = 0;
         if (++row == ROWS)
            row = 0;
      }

      draw();
   }

private:
   void draw()
   {
      frame.clear(BGCOL);

      for(unsigned row = 0; row < ROWS; ++row)
      {
         for(unsigned col = 0; col < COLS; ++col)
         {
            frame.drawLine(FGCOL, col * 6,       row * 8,
                                  (col + 1) * 6, row * 8);
         }
      }

      frame.refresh();
   }

   static const STB::Colour BGCOL = STB::RGB(0xC0, 0xC0, 0xC0);
   static const STB::Colour FGCOL = STB::RGB(0x00, 0x00, 0x00);

   static const unsigned COLS = 16;
   static const unsigned ROWS = 2;

   static const unsigned WIDTH  = COLS * 6 + 1;
   static const unsigned HEIGHT = ROWS * 9 + 1;

   ScaledFrame<WIDTH,HEIGHT> frame{"simulated 16x2 LCD"};

   unsigned col{0};
   unsigned row{0};
   char     text[ROWS][COLS];
   uint8_t  image[8][8];
};

#else

// Empty stub
class Lcd
{
public:
   Lcd() = default;
   void progChar(unsigned ch, const uint8_t* image) {}
   void move(unsigned col, unsigned row) { }
   void print(const char* text) { }
   void putchar(char ch) { }
};

#endif

} // namespace hw
