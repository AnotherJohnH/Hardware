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

elseif(${PLT_TARGET} STREQUAL rpipico2)

   set(hw_picoX21H_config_list
       I2S_DAC
       PWM_DAC
       WAVESHARE_REV2_1
       CACHE INTERNAL "picoX21H config variations")

elseif(${PLT_TARGET} STREQUAL native)

   set(hw_picoX21H_config_list
       NATIVE
       CACHE INTERNAL "picoX21H config Variations")

endif()

#-------------------------------------------------------------------------------
# Test

autogen_py(Table_sine)

foreach(hw_config ${hw_picoX21H_config_list})

   add_executable(test_picoX21H_${hw_config}
      Table_sine.cpp
      test_picoX21H.cpp)

   target_include_directories(test_picoX21H_${hw_config}
      PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
      )

   target_compile_definitions(test_picoX21H_${hw_config} PRIVATE HW_${hw_config})

   target_link_libraries(test_picoX21H_${hw_config} PRIVATE HW)

   set_target_properties(test_picoX21H_${hw_config} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

endforeach()
