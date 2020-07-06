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
    
elseif(ARGOS_BUILD_FOR STREQUAL "pipuck")
  message("No tests added for the pipuck configuration")
endif(ARGOS_BUILD_FOR_SIMULATOR)