cmake_minimum_required(VERSION 3.13)
project(unity-is-impossible)
set(UNIFY_IS_IMPOSSIBLE_VERSION 0.0.2)

## set Compiler Flags.
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++1z" COMPILER_SUPPORTS_CXX1Z)
if(COMPILER_SUPPORTS_CXX17)
  message("Use std C++17.")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif(COMPILER_SUPPORTS_CXX1Z)
  message("Use std C++1z.")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
else()
  message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++17 support. Please use a different C++ compiler.")
endif()

## extra compiler warnings
if ("${CMAKE_C_COMPILER_ID}" MATCHES ".*Clang.*")
	SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wunused-variable -Wswitch-default -Werror")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
	SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wunused-but-set-variable -Wunused-variable -Wswitch-default -Werror")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "Intel")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
endif()

SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/linux_pc)

## support pkg_check_modules
find_package(PkgConfig REQUIRED)
include(CheckSymbolExists)
include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)

option(BUILD_UI "Builds the ui subproject" ON)
option(BUILD_TEST "Enable to build ui test code" OFF)

if(BUILD_UI)
  # Include .h ###################################################################
  add_subdirectory(src)

  if(BUILD_TEST)
    add_subdirectory(3rdparty/googletest)
    add_subdirectory(test)
  endif() ##! BUILD_TEST
endif() ##! BUILD_UI
