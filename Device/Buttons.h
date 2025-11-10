//-------------------------------------------------------------------------------
// Copyright (c) 2024 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

// \brief Button interface

#pragma once

#if defined(HW_BUTTONS_GPIO)

#include "MTL/Gpio.h"

#elif defined(HW_BUTTONS_BADGER)

#include "MTL/badger2040.h"

#elif defined(HW_BUTTONS_NATIVE)

#include "native/Buttons.h"

#endif

#include "STB/Keypad.h"

namespace hw {

#if defined(HW_BUTTONS_GPIO)

class Buttons : public STB::Keypad<5>
{
public:
   Buttons(bool scan_on_irq_ = false)
   {
      MTL::config.gpio(HW_BUTTONS_GPIO_PIN + 0, "= BTN1 ");
      MTL::config.gpio(HW_BUTTONS_GPIO_PIN + 1, "= BTN2 ");
      MTL::config.gpio(HW_BUTTONS_GPIO_PIN + 2, "= BTN3 ");
      MTL::config.gpio(HW_BUTTONS_GPIO_PIN + 3, "= BTN4 ");
      MTL::config.gpio(HW_BUTTONS_GPIO_PIN + 4, "= BTN5 ");
   }

   using Keypad<5>::operator[];

   void irq()
   {
      keypadScan();
   }

private:
   bool keypadSample(unsigned index_) const override
   {
      return (btns & (1 << index_)) != 0;
   }

   MTL::Gpio::In<6, HW_BUTTONS_GPIO_PIN, MTL::PadsBank::PULL_DOWN, /* schmitt trigger */ true> btns;
};

#elif defined(HW_BUTTONS_BADGER)

class Buttons : public STB::Keypad<5>
{
public:
   Buttons(bool scan_on_irq_ = false)
   {
      MTL::config.gpio(MTL::badger2040::PIN_SW_A,  "= BTN1 (A)");
      MTL::config.gpio(MTL::badger2040::PIN_SW_B,  "= BTN2 (B)");
      MTL::config.gpio(MTL::badger2040::PIN_SW_C,  "= BTN3 (C)");
      MTL::config.gpio(MTL::badger2040::PIN_SW_UP, "= BTN4 (UP)");
      MTL::config.gpio(MTL::badger2040::PIN_SW_DN, "= BTN5 (DN)");
   }

   using Keypad<5>::operator[];

   void irq()
   {
      keypadScan();
   }

private:
   bool keypadSample(unsigned index_) const override
   {
      switch(index_)
      {
      case 0: return btn1;
      case 1: return btn2;
      case 2: return btn3;
      case 3: return btn4;
      case 4: return btn5;
      }

      return false;
   }

   MTL::Switch::badger2040::SwitchA  btn1;
   MTL::Switch::badger2040::SwitchB  btn2;
   MTL::Switch::badger2040::SwitchC  btn3;
   MTL::Switch::badger2040::SwitchUp btn4;
   MTL::Switch::badger2040::SwitchDn btn5;
};

#elif defined(HW_BUTTONS_NATIVE)

using Buttons = ::Buttons<5>;

#else

class Buttons : public STB::Keypad<5>
{
public:
   Buttons(bool scan_on_irq_ = false) {}

   using Keypad<5>::operator[];

private:
   bool keypadSample(unsigned index_) const override { return false; }
};

#endif

} // namespace hw
