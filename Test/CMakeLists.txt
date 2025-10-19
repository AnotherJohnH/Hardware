#-------------------------------------------------------------------------------
# Copyright (c) 2025 John D. Haughton
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

autogen_py(Table_sine)

foreach(hw ${HARDWARE})
   foreach(hw_config ${hw_${hw}_config_list})

      add_executable(test_${hw}_${hw_config}
         Table_sine.cpp
         test_${hw}.cpp)

      target_include_directories(test_${hw}_${hw_config}
         PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
         )

      target_compile_definitions(test_${hw}_${hw_config} PRIVATE HW_${hw_config})

      target_link_libraries(test_${hw}_${hw_config} PRIVATE HW)

      set_target_properties(test_${hw}_${hw_config} PROPERTIES
         RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

   endforeach()
endforeach()
