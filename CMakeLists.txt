cmake_minimum_required(VERSION 3.28.3)
project(Flags VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME}
  INTERFACE
)

target_include_directories(${PROJECT_NAME}
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_compile_features(${PROJECT_NAME}
  INTERFACE
  cxx_std_17
)

target_compile_options(
  ${PROJECT_NAME}
  INTERFACE
  -Wall
  -Werror
  -Wextra
  -Wpedantic
)

# Example executable
add_executable(flags_example
  examples/usage.cpp
)

target_link_libraries(flags_example
  PRIVATE
  ${PROJECT_NAME}
)

target_compile_features(flags_example PRIVATE cxx_std_17)

target_compile_options(flags_example
  PRIVATE
  -Wall
  -Werror
  -Wextra
  -Wpedantic
)
