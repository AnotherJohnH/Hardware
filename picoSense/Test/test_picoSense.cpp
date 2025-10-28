//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#include "Hardware/picoSense/Config.h"

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

//--- TEST E-PAPER -------------------------------------------------------------

static NOINLINE void testEPaper(Phase phase_)
{
   static hw::EPaper::Canvas epaper{};
   static const STB::Colour WHITE = STB::RGB(0xC0, 0xC0, 0xC0);
   static const STB::Colour BLACK = STB::RGB(0x00, 0x00, 0x00);

   switch(phase_)
   {
   case DECL:
      break;

   case INFO:
      printf("EPaper: \n");
      break;

   case START:
      epaper.clear(WHITE);
      epaper.drawLine(BLACK, 0, 0, epaper.getWidth(), epaper.getHeight());
      epaper.drawLine(BLACK, 0, epaper.getHeight(), epaper.getWidth(), 0);
      epaper.refresh();
      break;

   case RUN:
      epaper.refresh();
      break;
   }
}

//--- TEST USB INTERFACES -----------------------------------------------------

#include "STB/FAT/FAT16.h"

class FileSystem: public STB::FAT16<6>
{
public:
   FileSystem()
      : STB::FAT16<6>("HW_TEST")
   {
      static const char* readme_txt = "Hello, world!";

      addFile("README.txt", strlen(readme_txt), (uint8_t*)readme_txt);
   }
};

static hw::UsbFile* usb_ptr{nullptr};

extern "C" void IRQ_USBCTRL()
{
   if (usb_ptr != nullptr)
   {
      usb_ptr->irq();
   }
}

//! USB test
static NOINLINE void testUsb(Phase phase_)
{
   static FileSystem  file_portal{};
   static hw::UsbFile usb{0x91C0, "test_hw", file_portal};

   switch(phase_)
   {
   case DECL:
      usb_ptr = &usb;
      break;

   case INFO:
      printf("USB: Mass storage device \"HW_TEST\" with a simple README\n" );
      break;

   case START:
      break;

   case RUN:
      break;
   }
}

//------------------------------------------------------------------------------

static void test(Phase phase_)
{
   if (1) testLED(phase_);
   if (1) testEPaper(phase_);
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
   printf("Program  : Test picoSense (%s)\n", HW_DESCR);
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
