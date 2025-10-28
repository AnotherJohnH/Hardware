#-------------------------------------------------------------------------------
# Copyright (c) 2025 John D. Haughton
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

if(${PLT_TARGET} STREQUAL rpipico)

   set(hw_picoSense_config_list
       WAVESHARE_EPAPER
       BADGER2040
       CACHE INTERNAL "Config Variations")

   add_subdirectory(Test)

elseif(${PLT_TARGET} STREQUAL rpipico2)

   set(hw_picoSense_config_list
       CACHE INTERNAL "Config Variations")

   add_subdirectory(Test)

elseif(${PLT_TARGET} STREQUAL native)

   set(hw_picoSense_config_list
       NATIVE
       CACHE INTERNAL "Config Variations")

   add_subdirectory(Test)

endif()
