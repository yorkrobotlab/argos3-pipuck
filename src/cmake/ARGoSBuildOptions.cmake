
if(NOT DEFINED ARGOS_BUILD_FOR)
  # Variable was not set, set to default value
  set(ARGOS_BUILD_FOR "simulator" CACHE STRING "What is ARGoS being built for? \"simulator\" or a robot name (lowercase)")
else(NOT DEFINED ARGOS_BUILD_FOR)
  # Variable was set, make it public
  set(ARGOS_BUILD_FOR ${ARGOS_BUILD_FOR} CACHE STRING "What is ARGoS being built for? \"simulator\" or a robot name (lowercase)")
endif(NOT DEFINED ARGOS_BUILD_FOR)
# Set a macro according to value set in ARGOS_BUILD_FOR
add_definitions(-DARGOS_${ARGOS_BUILD_FOR}_BUILD)
if(ARGOS_BUILD_FOR STREQUAL "simulator")
  set(ARGOS_BUILD_FOR_SIMULATOR TRUE)
else(ARGOS_BUILD_FOR STREQUAL "simulator")
  set(ARGOS_BUILD_FOR_SIMULATOR FALSE)
endif(ARGOS_BUILD_FOR STREQUAL "simulator")

# check and set ARGOS_USE_DOUBLE
if(NOT DEFINED ARGOS_USE_DOUBLE)
  #variable was not set, use default value
  set(ARGOS_USE_DOUBLE ON)
else(NOT DEFINED ARGOS_USE_DOUBLE)
  set(ARGOS_USE_DOUBLE ${ARGOS_USE_DOUBLE})
endif(NOT DEFINED ARGOS_USE_DOUBLE)

# check and set ARGOS_WITH_LUA
if(NOT DEFINED ARGOS_WITH_LUA)
  set(ARGOS_WITH_LUA OFF)
else(NOT DEFINED ARGOS_WITH_LUA)
  set(ARGOS_WITH_LUA ${ARGOS_WITH_LUA})
endif(NOT DEFINED ARGOS_WITH_LUA)

# check and set ARGOS_COMPILE_QTOPENGL
if(NOT DEFINED ARGOS_COMPILE_QTOPENGL)
  set(ARGOS_COMPILE_QTOPENGL ON)
else(NOT DEFINED ARGOS_COMPILE_QTOPENGL)
  set(ARGOS_COMPILE_QTOPENGL ${ARGOS_COMPILE_QTOPENGL})
endif(NOT DEFINED ARGOS_COMPILE_QTOPENGL)

# check and set ARGOS_WITH_FREEIMAGE
#this needs to be on for the pipuck to actually render
if(NOT DEFINED ARGOS_WITH_FREEIMAGE)
  set(ARGOS_WITH_FREEIMAGE ON)
else(NOT DEFINED ARGOS_WITH_FREEIMAGE)
  set(ARGOS_WITH_FREEIMAGE ${ARGOS_WITH_FREEIMAGE})
endif(NOT DEFINED ARGOS_WITH_FREEIMAGE)

# check and set ARGOS_THREADSAFE_LOG
if(NOT DEFINED ARGOS_THREADSAFE_LOG)
  set(ARGOS_THREADSAFE_LOG ON)
else(NOT DEFINED ARGOS_THREADSAFE_LOG)
  set(ARGOS_THREADSAFE_LOG ${ARGOS_THREADSAFE_LOG})
endif(NOT DEFINED ARGOS_THREADSAFE_LOG)

#
# Optimize code for current platform?
#
if(NOT DEFINED ARGOS_BUILD_NATIVE)
  option(ARGOS_BUILD_NATIVE "ON -> compile with platform-specific optimizations, OFF -> compile to portable binary" OFF)
endif(NOT DEFINED ARGOS_BUILD_NATIVE)

