# ##############################################################################
# PROJECT
# ##############################################################################
cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)
project(
  Cieo
  VERSION 0.0.0
  LANGUAGES CXX C)

# ##############################################################################
# OPTIONS
# ##############################################################################
option(ENABLE_PROFILING "Enable profiling" FALSE)

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
# MACRO DEFINITIONS
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
macro(compress_resource FILE SOURCE_DIR EXT)
  file(GLOB FILES "${SOURCE_DIR}/*.${EXT}")
  add_custom_command(
    OUTPUT ${FILE}
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/scripts/compress.sh ${FILE}
            ${SOURCE_DIR} ${EXT}
    DEPENDS ${FILES}
    COMMENT "Compressing ${SOURCE_DIR}/*.${EXT} for ${FILE}")
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
load_submodule(opencv)
load_submodule(glfw)
load_submodule(glm)
load_submodule(assimp)

compress_resource(${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/shaders.hpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics glsl)

# find_package(OpenCV REQUIRED)
# message("OPENCV: ${OpenCV_LIBS}")

# ##############################################################################
# SOURCE
# ##############################################################################
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(SOURCES src/main.cpp src/graphics/core.cpp src/graphics/gl_window.cpp
            src/graphics/glad.c src/graphics/object.cpp src/graphics/shaders.hpp)
add_executable(cieo ${SOURCES})
set_target_properties(cieo PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES)
target_link_libraries(cieo glfw glm opencv_core opencv_videoio assimp ${CMAKE_DL_LIBS})

# ##############################################################################
# HPC
# ##############################################################################
find_package(OpenMP QUIET)
if(OpenNP_CXX_FOUND)
  message(STATUS "Using OpenMP ${OpenMP_CXX_FLAGS}")
  target_link_libraries(cieo ${OpenMP_CXX_LIBRARIES})
  target_compile_options(cieo PUBLIC ${OpenMP_CXX_FLAGS})
endif()
