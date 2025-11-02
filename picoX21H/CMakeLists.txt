#-------------------------------------------------------------------------------
# Copyright (c) 2025 John D. Haughton
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

if(${PLT_TARGET} STREQUAL rpipico)

   set(hw_picoX21H_config_list
       I2S_DAC
       PWM_DAC
       WAVESHARE_REV2_1
       CACHE INTERNAL "picoX21 config variations")

   add_subdirectory(Test)

elseif(${PLT_TARGET} STREQUAL rpipico2)

   set(hw_picoX21H_config_list
       I2S_DAC
       PWM_DAC
       WAVESHARE_REV2_1
       CACHE INTERNAL "picoX21H config variations")

   add_subdirectory(Test)

elseif(${PLT_TARGET} STREQUAL native)

   set(hw_picoX21H_config_list
       NATIVE
       CACHE INTERNAL "picoX21H config Variations")

   add_subdirectory(Test)

endif()
