#-------------------------------------------------------------------------------
# Copyright (c) 2025 John D. Haughton
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

if(${PLT_TARGET} STREQUAL rpipico)

   set(hw_picoSense_config_list
       WAVESHARE_EPAPER
       BADGER2040
       CACHE INTERNAL "picoSense config Variations")

elseif(${PLT_TARGET} STREQUAL rpipico2)

   set(hw_picoSense_config_list
       CACHE INTERNAL "picoSense config Variations")

elseif(${PLT_TARGET} STREQUAL native)

   set(hw_picoSense_config_list
       NATIVE
       CACHE INTERNAL "picoSense config Variations")

endif()

#-------------------------------------------------------------------------------
# Test

foreach(hw_config ${hw_picoSense_config_list})

   add_executable(test_picoSense_${hw_config}
      test_picoSense.cpp)

   target_include_directories(test_picoSense_${hw_config}
      PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
      )

   target_compile_definitions(test_picoSense_${hw_config} PRIVATE HW_${hw_config})

   target_link_libraries(test_picoSense_${hw_config} PRIVATE HW)

   set_target_properties(test_picoSense_${hw_config} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

endforeach()
