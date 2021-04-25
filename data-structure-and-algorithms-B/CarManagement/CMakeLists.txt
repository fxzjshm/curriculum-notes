cmake_minimum_required(VERSION 2.6)

project(CarManagement)

include_directories(include)
aux_source_directory(src DIR_SRCS)

add_executable(CarManagement ${DIR_SRCS})

target_compile_options(CarManagement PRIVATE -Os -Wall)

