if(ARGOS_BUILD_FOR_SIMULATOR)
  configure_file(
    ${CMAKE_SOURCE_DIR}/testing/pi-puck/simulator/controllers/test_pipuck.lua
    ${CMAKE_BINARY_DIR}/testing/pi-puck/test_pipuck.lua
    COPYONLY    
  )
  configure_file(
    ${CMAKE_SOURCE_DIR}/testing/pi-puck/simulator/controllers/calibrate_pipuck.lua
    ${CMAKE_BINARY_DIR}/testing/pi-puck/calibrate_pipuck.lua
    COPYONLY)

    add_library(test_pipuck_cpp MODULE test_pipuck_cpp.h test_pipuck_cpp.cpp)
    target_link_libraries(test_pipuck_cpp
      argos3core_simulator
      argos3srocs_simulator_pipuck
      argos3plugin_simulator_genericrobot)
    
elseif(ARGOS_BUILD_FOR STREQUAL "pipuck")
  message("No tests added for the pipuck configuration")
endif(ARGOS_BUILD_FOR_SIMULATOR)