cmake_minimum_required(VERSION 3.13)
project(ortcxx LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

# Include all cmake files in /cmake directory.
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/onnxruntimeConfig.cmake)
# Find OnnxRuntime lib.
find_package(onnxruntime)

set(SWIG_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/swig)
file(MAKE_DIRECTORY ${SWIG_OUTPUT_DIR})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../core
)

set(SWIG_INPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/ortcxx.i)
set_source_files_properties(${SWIG_INPUT_FILE} PROPERTIES CPLUSPLUS ON)
set_source_files_properties(${SWIG_INPUT_FILE} PROPERTIES SWIG_FLAGS "-namespace;Cinnamon")

swig_add_library(ortcxx
  LANGUAGE csharp
  SOURCES ${SWIG_INPUT_FILE} ${CMAKE_CURRENT_SOURCE_DIR}/async_helper.i
)

add_library(core SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/../../core/model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../core/modelManager.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/../../core/serviceManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/async_helper.cpp
)

swig_link_libraries(ortcxx core)

install(TARGETS ortcxx DESTINATION lib)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ortcxx.dll ${CMAKE_CURRENT_BINARY_DIR}/ortcxx.cs DESTINATION bin)