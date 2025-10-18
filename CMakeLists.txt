#-------------------------------------------------------------------------------
# Copyright (c) 2025 John D. Haughton
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
   # Top level for stand-alone build

   cmake_minimum_required(VERSION 3.20)

   project(picoX21H
           LANGUAGES CXX C ASM
           VERSION 0.01)

   include(CTest)

   add_subdirectory(Platform)

   if(${PLT_TARGET} STREQUAL rpipico OR ${PLT_TARGET} STREQUAL rpipico2)
      math(EXPR plt_bcd_version "${CMAKE_MAJOR_VERSION} * 0x100 + ${CMAKE_MINOR_VERSION}"
           OUTPUT_FORMAT HEXADECIMAL)
      target_compile_definitions(MTL PUBLIC PLT_BCD_VERSION=${plt_bcd_version})
   endif()

endif()

#-------------------------------------------------------------------------------

add_library(HW INTERFACE)
target_include_directories(HW INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)

if(${PLT_TARGET} STREQUAL rpipico)

   set(hw_config_list
       I2S_DAC
       PWM_DAC
       WAVESHARE_REV2_1
       CACHE INTERNAL "Host List")

   target_link_libraries(HW INTERFACE TNY MTL)

   add_subdirectory(Test)

elseif(${PLT_TARGET} STREQUAL rpipico2)

   set(hw_config_list
       I2S_DAC
       PWM_DAC
       WAVESHARE_REV2_1
       CACHE INTERNAL "Host List")

   target_link_libraries(HW INTERFACE TNY MTL)

   add_subdirectory(Test)

elseif(${PLT_TARGET} STREQUAL native)

   set(hw_config_list
       NATIVE
       CACHE INTERNAL "Host List")

   target_link_libraries(HW INTERFACE PLT STB)

endif()

