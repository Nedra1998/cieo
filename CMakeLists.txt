# ##############################################################################
# PROJECT
# ##############################################################################
cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)
project(
  Cieo
  VERSION 0.0.0
  LANGUAGES CXX)

# ##############################################################################
# OPTIONS
# ##############################################################################
option(ENABLE_PROFILING "Enable profiling" FALSE)
option(STATIC_ANALYSIS "Uset static analysis tools" TRUE)

# ##############################################################################
# BUILD MODE
# ##############################################################################
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE
      "Debug"
      CACHE STRING "" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
  if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    execute_process(
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
              ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
              ${CMAKE_CURRENT_SOURCE_DIR}/compile_comands.json)
  endif()
endif()
list(APPEND CMAKE_CXX_FLAGS "-Wall")
list(APPEND CMAKE_CXX_FLAGS_RELEASE "-O3")
if(ENABLE_PROFILING)
  list(APPEND CMAKE_CXX_FLAGS_DEBUG "-D__PROFILING__")
endif()

# ##############################################################################
# STATIC ANALYSIS
# ##############################################################################
if(STATIC_ANALYSIS OR CMAKE_BUILD_TYPE STREQUAL "Release")
  find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang tidy exe")
  if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
  endif()
  find_program(CPPCHECK_EXE NAME "cppcheck" DOC "Path to cppcheck exe")
  if(CPPCHECK_EXE)
    set(CMAKE_CXX_CPPCHECK "${CPPCHECK_EXE}" "--force")
  endif()
  find_program(CPPLINT_EXE "cpplint")
  if(CPPLINT_EXE)
    set(CMAKE_CXX_CPPLINT "${CPPLINT_EXE}")
  endif()
endif()

# ##############################################################################
# Fetch Macro
# ##############################################################################
find_package(Git REQUIRED)
macro(clone_git REPO_NAME)
  string(TOUPPER ${REPO_NAME} MODULE_NAME)
  if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/external/${REPO_NAME}/.git)
    execute_process(
      COMMAND
        git submodule update --init --recursive --
        ${CMAKE_CURRENT_SOURCE_DIR}/${REPO_NAME})
  elseif(NOT GIT_FOUND)
    message(FATAL_ERROR "Git is required for submodules ${MODULE_NAME}")
  else()
    set(${MODULE_NAME}_FOUND TRUE)
  endif()
endmacro()
macro(load_submodule REPO_NAME)
  clone_git(${REPO_NAME})
  string(TOUPPER ${REPO_NAME} MODULE_NAME)
  if(${MODULE_NAME}_FOUND)
    message(STATUS "FOUND PACKAGE: ${MODULE_NAME} / ${REPO_NAME}")
    message(
      STATUS "Module path: ${CMAKE_CURRENT_SOURCE_DIR}/external/${REPO_NAME}")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/${REPO_NAME}
                     EXCLUDE_FROM_ALL)
  else()
    message(STATUS "DID not find ${MODULE_NAME")
  endif()
endmacro()

# ##############################################################################
# DEPENDENCIES
# ##############################################################################
include(WriteCompilerDetectionHeader)
set(CIEO_COMPILERS MSVC GNU Clang Intel AppleClang)
write_compiler_detection_header(
  FILE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/preprocessor.hpp
  PREFIX
  SPECULA
  COMPILERS
  ${CIEO_COMPILERS}
  FEATURES
  cxx_constexpr
  cxx_noexcept
  cxx_static_assert
  cxx_attribute_deprecated)

# ##############################################################################
# SOURCE
# ##############################################################################
set(SOURCES
  src/main.cpp)
add_executable(cieo ${SOURCES})
set_target_properties(cieo PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES)

# ##############################################################################
# HPC
# ##############################################################################
find_package(OpenMP QUIET)
if(OpenNP_CXX_FOUND)
  message(STATUS "Using OpenMP ${OpenMP_CXX_FLAGS}")
  target_link_libraries(cieo ${OpenMP_CXX_LIBRARIES})
  target_compile_options(cieo PUBLIC ${OpenMP_CXX_FLAGS})
endif()
