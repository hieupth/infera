cmake_minimum_required(VERSION 3.26.1)
project(ORTProject)

find_package(OpenCV REQUIRED)
add_library(onnxruntime SHARED IMPORTED)
set_property(TARGET onnxruntime PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/external/onnxruntime/build/Linux/RelWithDebInfo/libonnxruntime.so)
# find_package(ONNXRuntime REQUIRED)
include_directories(external/onnxruntime/include/onnxruntime/core/session)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} onnxruntime)



# add_subdirectory(external/opencv)
# add_subdirectory(external/onnxruntime/cmake)
# include_directories(external/opencv/include/opencv2)
# include_directories(external/onnxruntime/include)


# find_package(onnxruntime REQUIRED)

# install(TARGETS ${PROJECT_NAME} DESTINATION bin)
