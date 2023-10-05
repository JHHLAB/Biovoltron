cmake_minimum_required(VERSION 3.16)
project(biovoltron-test)

include_directories(${CMAKE_CURRENT_LIST_DIR})

option(GCOV "Build with gcov" OFF)
if (GCOV)
  add_compile_options("--coverage")
  add_link_options("--coverage")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_serialization")

file(GLOB_RECURSE SOURCE_FILES *.cpp)

add_executable(biovoltron-test ${SOURCE_FILES})
target_link_libraries(biovoltron-test biovoltron)
target_compile_options(biovoltron-test PRIVATE -Wno-ignored-attributes)
target_compile_definitions(biovoltron-test
  PRIVATE DATA_PATH="${CMAKE_CURRENT_LIST_DIR}/data")

add_test(NAME biovoltron COMMAND biovoltron-test)
