cmake_minimum_required(VERSION 3.28.3)
project(Flags VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME}
  STATIC
  source/common.cc
  source/flags.cc
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_compile_features(${PROJECT_NAME}
  PUBLIC
  cxx_std_17
)

target_compile_options(
  ${PROJECT_NAME}
  PRIVATE
  # -Wall
  # -Werror
  # -Wextra
  # -Wpedantic
)

add_executable(test main.cc)

target_link_libraries(test Flags)
