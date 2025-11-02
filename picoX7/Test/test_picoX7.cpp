//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#include "Hardware/picoX7/Config.h"

#include <cstdio>
#include <unistd.h>

enum Phase { DECL, INFO, START, RUN };

#define NOINLINE __attribute__ ((noinline))


//--- TEST ONBOARD LED ---------------------------------------------------------

static NOINLINE void testLED(Phase phase_)
{
   static hw::Led led{};

   switch(phase_)
   {
   case DECL:
      break;

   case INFO:
      printf("LED: (onboard) flash at 1Hz\n");
      break;

   case START:
      break;

   case RUN:
      led = not led;
      break;
   }
}

//--- TEST 16x2 LCD ------------------------------------------------------------

static NOINLINE void testLCD(Phase phase_)
{
   static hw::Lcd lcd{};

   switch(phase_)
   {
   case DECL:
      break;

   case INFO:
      printf("LCD: display \"Hello World!\", an incrementing value and an up arrow\n");
      break;

   case START:
      {
         uint8_t ch[8] =
         {
            0b00000,
            0b00100,
            0b01110,
            0b10101,
            0b00100,
            0b00100,
            0b00100,
            0b00000
         };

         lcd.progChar(0, ch);
      }
      break;

   case RUN:
      {
         static unsigned n{0};

         char text[16];
         snprintf(text, sizeof(text), "Hello %u", n++);

         lcd.move(0, 0);
         lcd.print(text);

         lcd.move(0, 1);
         lcd.print("World!");

         lcd.move(15, 1);
         lcd.putchar('\0');
      }
      break;
   }
}

//--- TEST PHYSICAL MIDI ------------------------------------------------------

static NOINLINE void testPhysMIDI(Phase phase_)
{
   static hw::PhysMidi phys_midi{};

   switch(phase_)
   {
   case DECL:
      break;

   case INFO:
      printf("MIDI: Laggy log of MIDI messages on the console\n" );
      break;

   case START:
      phys_midi.setDebug(true);
      break;

   case RUN:
      phys_midi.tick();
      break;
   }
}


//--- TEST USB INTERFACES -----------------------------------------------------

#include "Hardware/FilePortal.h"

static hw::UsbFileMidi* usb_ptr{nullptr};

extern "C" void IRQ_USBCTRL()
{
   if (usb_ptr != nullptr)
   {
      usb_ptr->irq();
   }
}

//! USB MIDI test
static NOINLINE void testUsb(Phase phase_)
{
   static hw::FilePortal file_portal{"HW_TEST",
                                     "https://github.com/AnotherJohnH/Hardware/"};

   static hw::UsbFileMidi usb{0x91C0, "test_hw", file_portal};

   switch(phase_)
   {
   case DECL:
      usb_ptr = &usb;
      break;

   case INFO:
      printf("USB: Mass storage device \"HW_TEST\" with a simple README\n" );
      printf("USB: Laggy log of MIDI messages on the console\n" );
      break;

   case START:
      usb.setDebug(true);
      file_portal.addREADME("Test picoX7");
      break;

   case RUN:
      usb.tick();
      break;
   }
}


//------------------------------------------------------------------------------

static void test(Phase phase_)
{
   if (1) testLED(phase_);
   if (1) testLCD(phase_);
   if (1) testPhysMIDI(phase_);
   if (1) testUsb(phase_);
}

//------------------------------------------------------------------------------

static void consoleReport()
{
   // Clear screen and cursor to home
   printf("\e[2J");
   printf("\e[1,1H");

   printf("TEST HARDWARE\n");
   printf("\n");
   printf("Program  : Test picoX7 (%s)\n", HW_DESCR);
   printf("Author   : Copyright (c) 2025 John D. Haughton\n");
   printf("License  : MIT\n");
   printf("Version  : %s\n", PLT_VERSION);
   printf("Commit   : %s\n", PLT_COMMIT);
   printf("Built    : %s %s\n", __TIME__, __DATE__);
   printf("Compiler : %s\n", __VERSION__);

#if !defined(HW_NATIVE)
   char config[1024];
   MTL::config.format(config, sizeof(config));
   puts(config);
#endif
}

//------------------------------------------------------------------------------

int main()
{
   test(DECL);

   consoleReport();

   printf("INFO\n\n");

   test(INFO);

   printf("\nSTART\n");

   test(START);

   printf("RUN\n\n");

   while(true)
   {
      test(RUN);

      usleep(500000);
   }

   return 0;
}
