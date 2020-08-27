#
# Find the ARGoS package
#
find_package(PkgConfig)
pkg_check_modules(ARGOS REQUIRED argos3_simulator)
set(ARGOS_PREFIX ${ARGOS_PREFIX} CACHE INTERNAL "")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ARGOS_PREFIX}/share/argos3/cmake)
set(CMAKE_INSTALL_PREFIX ${ARGOS_PREFIX} CACHE STRING "Install path prefix, prepended onto install directories." FORCE)

include(ARGoSCheckQTOpenGL)
#
# Check for correct GCC version
#
macro(CHECK_GCC MIN_VERSION)
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
  if(GCC_VERSION VERSION_GREATER ${MIN_VERSION} OR GCC_VERSION VERSION_EQUAL ${MIN_VERSION})
    message(STATUS "GCC/G++ version >= ${MIN_VERSION}")
  else(GCC_VERSION VERSION_GREATER ${MIN_VERSION} OR GCC_VERSION VERSION_EQUAL ${MIN_VERSION})
    message(FATAL_ERROR "You need to have at least GCC/G++ version ${MIN_VERSION}!")
  endif(GCC_VERSION VERSION_GREATER ${MIN_VERSION} OR GCC_VERSION VERSION_EQUAL ${MIN_VERSION})
endmacro(CHECK_GCC)

#
# Set variables depending on current compiler
#
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # using Clang
  set(ARGOS_START_LIB_GROUP)
  set(ARGOS_END_LIB_GROUP)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC
  set(ARGOS_START_LIB_GROUP -Wl,--start-group)
  set(ARGOS_END_LIB_GROUP -Wl,--end-group)

  if(ARGOS_BUILD_FOR_SIMULATOR)
    # For the simulator it must be >= 6.1.0
    check_gcc(6.1.0)
  else(ARGOS_BUILD_FOR_SIMULATOR)
    # For a hardware build it must be >= 9.1.0
    check_gcc(9.1.0)
  endif(ARGOS_BUILD_FOR_SIMULATOR)
endif()

#
# Check for the AprilTag library
# It is required only when compiling for the hardware
#
if(ARGOS_BUILD_FOR STREQUAL "builderbot" OR ARGOS_BUILD_FOR STREQUAL "drone")
  find_package(AprilTag)
  if(NOT APRILTAG_FOUND)
    message(FATAL_ERROR "Required library AprilTag not found.")
  endif(NOT APRILTAG_FOUND)
  include_directories(${APRILTAG_INCLUDE_DIR})
endif(ARGOS_BUILD_FOR STREQUAL "builderbot" OR ARGOS_BUILD_FOR STREQUAL "drone")

#
# Check for Analog Device's IIO library
# It is required only when compiling for the hardware
#
if(ARGOS_BUILD_FOR STREQUAL "builderbot")
  find_package(IIO)
  if(NOT IIO_FOUND)
    message(FATAL_ERROR "Required library IIO not found.")
  endif(NOT IIO_FOUND)
  include_directories(${IIO_INCLUDE_DIR})
endif(ARGOS_BUILD_FOR STREQUAL "builderbot")

#
# Check for V4L2 Sub-device library
# It is required only when compiling for the hardware
#
if(ARGOS_BUILD_FOR STREQUAL "builderbot")
  find_package(V4L2Subdev)
  if(NOT V4L2SUBDEV_FOUND)
    message(FATAL_ERROR "Required V4L2 Sub-device library not found.")
  endif(NOT V4L2SUBDEV_FOUND)
endif(ARGOS_BUILD_FOR STREQUAL "builderbot")

#
# Check for Mediactl library
# It is required only when compiling for the hardware
#
if(ARGOS_BUILD_FOR STREQUAL "builderbot")
  find_package(Mediactl)
  if(NOT MEDIACTL_FOUND)
    message(FATAL_ERROR "Required library Mediactl not found.")
  endif(NOT MEDIACTL_FOUND)
  include_directories(${MEDIACTL_INCLUDE_DIR})
endif(ARGOS_BUILD_FOR STREQUAL "builderbot")

#
# Check for Lua 5.3
#
find_package(Lua53)
if(LUA53_FOUND)
  set(ARGOS_WITH_LUA ON)
  include_directories(${LUA_INCLUDE_DIR})
else(LUA53_FOUND)
  set(ARGOS_WITH_LUA OFF)
endif(LUA53_FOUND)

if(NOT APPLE)
  find_package(RT)
endif(NOT APPLE)

#
# Set ARGoS include dir
#
include_directories(${CMAKE_SOURCE_DIR} ${ARGOS_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

#
# Set ARGoS link dir
#
link_directories(${ARGOS_LIBRARY_DIRS})

