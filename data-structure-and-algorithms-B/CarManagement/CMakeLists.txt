cmake_minimum_required(VERSION 2.6)

project(CarManagement)

include_directories(include)
aux_source_directory(src DIR_SRCS)

# ref: https://stackoverflow.com/questions/10046114/in-cmake-how-can-i-test-if-the-compiler-is-clang
if (MSVC)
# ref: https://stackoverflow.com/questions/47690822/possible-to-force-cmake-msvc-to-use-utf-8-encoding-for-source-files-without-a-bo
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
endif()

add_executable(CarManagement ${DIR_SRCS})

target_compile_options(CarManagement PRIVATE -Os ${ADDTIONAL_FLAGS})
