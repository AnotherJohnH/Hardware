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
       CACHE INTERNAL "picoX7 config Variations")

elseif(${PLT_TARGET} STREQUAL rpipico2)

   set(hw_picoX7_config_list
       I2S_DAC
       PWM_DAC
       WAVESHARE_REV2_1
       PIMORONI_PICO_AUDIO
       CACHE INTERNAL "picoX7 config Variations")

elseif(${PLT_TARGET} STREQUAL native)

   set(hw_picoX7_config_list
       NATIVE
       CACHE INTERNAL "picoX7 config Variations")

endif()

#-------------------------------------------------------------------------------
# Test

autogen_py(Table_sine)

foreach(hw_config ${hw_picoX7_config_list})

   add_executable(test_picoX7_${hw_config}
      Table_sine.cpp
      test_picoX7.cpp)

   target_include_directories(test_picoX7_${hw_config}
      PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
      )

   target_compile_definitions(test_picoX7_${hw_config} PRIVATE HW_${hw_config})

   target_link_libraries(test_picoX7_${hw_config} PRIVATE HW)

   set_target_properties(test_picoX7_${hw_config} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

endforeach()
