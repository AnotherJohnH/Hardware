#-------------------------------------------------------------------------------
# Copyright (c) 2025 John D. Haughton
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

if(${PLT_TARGET} STREQUAL rpipico)

   set(hw_picoX7_config_list
       I2S_DAC
       PWM_DAC
       WAVESHARE_REV2_1
       PIMORONI_PICO_AUDIO
       PIMORONI_VGA_DEMO
       CACHE INTERNAL "Config Variations")

elseif(${PLT_TARGET} STREQUAL rpipico2)

   set(hw_picoX7_config_list
       I2S_DAC
       PWM_DAC
       WAVESHARE_REV2_1
       PIMORONI_PICO_AUDIO
       CACHE INTERNAL "Config Variations")

endif()
