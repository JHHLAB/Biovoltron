cmake_minimum_required(VERSION 3.16)

project(biovoltron)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

# biovoltron
add_library(biovoltron INTERFACE)
set_target_properties(biovoltron PROPERTIES INTERFACE_COMPILE_FEATURES cxx_std_20)

# zlib
find_package(ZLIB REQUIRED)
target_link_libraries(biovoltron INTERFACE ZLIB::ZLIB)

# tbb
find_package(TBB CONFIG REQUIRED)
# FIXME: https://github.com/microsoft/vcpkg/issues/31617
add_compile_definitions(TBB_USE_ASSERT)
target_link_libraries(biovoltron INTERFACE TBB::tbb TBB::tbbmalloc)

# range-v3
find_package(range-v3 CONFIG REQUIRED)
target_link_libraries(biovoltron INTERFACE range-v3::meta range-v3::concepts range-v3::range-v3)

# boost
find_package(Boost CONFIG REQUIRED)
target_include_directories(biovoltron INTERFACE ${Boost_INCLUDE_DIRS})
target_link_libraries(biovoltron INTERFACE ${Boost_LIBRARIES})

# Threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(biovoltron INTERFACE Threads::Threads)

# openmp
find_package(OpenMP 4.5 REQUIRED)

# spdlog
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(biovoltron INTERFACE spdlog::spdlog)

# libsimdpp
find_path(LIBSIMDPP_INCLUDE_DIRS "simdpp/simd.h")
target_include_directories(biovoltron INTERFACE ${LIBSIMDPP_INCLUDE_DIRS})

# target_compile_options(biovoltron INTERFACE
#   -mavx -mavx2
#   -Wno-sign-compare -Wno-nonnull -Wno-char-subscripts -Wno-narrowing)
# 

# build test
option(BIOVOLTRON_TESTS "Build the tests" ON)
if(BIOVOLTRON_TESTS)
  include(CTest)
  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tests)
endif()
# 
# # build document
# option(BIOVOLTRON_DOC "Build documentation" OFF)
# if (BIOVOLTRON_DOC)
#   add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/docs)
# endif()
