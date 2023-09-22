cmake_minimum_required(VERSION 3.16)

project(biovoltron)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

# biovoltron
add_library(biovoltron INTERFACE)
set_target_properties(biovoltron PROPERTIES INTERFACE_COMPILE_FEATURES cxx_std_20)

# zlib
find_package(ZLIB REQUIRED)

# tbb
set(TBB_ROOT "${CMAKE_CURRENT_LIST_DIR}/submodules/tbb")
include(${TBB_ROOT}/cmake/TBBBuild.cmake)
tbb_build(TBB_ROOT ${TBB_ROOT} CONFIG_DIR TBB_DIR MAKE_ARGS tbb_cpf=1)
find_package(TBB REQUIRED tbb_preview)

# range-v3
add_library(range_v3 INTERFACE IMPORTED)
set_target_properties(range_v3 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_LIST_DIR}/submodules/range-v3/include)

# boost
find_package(Boost 1.71.0)
if(Boost_FOUND)
  target_include_directories(biovoltron INTERFACE ${Boost_INCLUDE_DIRS})
  target_link_libraries(biovoltron INTERFACE ${Boost_LIBRARIES})
else()
  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/submodules/boost-cmake)
endif()

# Threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# openmp
find_package(OpenMP 4.5 REQUIRED)

# spdlog
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/submodules/spdlog)

# libsimdpp
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/submodules/libsimdpp)
target_include_directories(biovoltron INTERFACE ${CMAKE_CURRENT_LIST_DIR}/submodules/libsimdpp)

# htslib
include(ExternalProject)
set(HTSLIB_ROOT ${CMAKE_CURRENT_LIST_DIR}/submodules/htslib)
find_package(BZip2)
if(NOT BZIP2_FOUND)
  set(HTSLIB_DISABLE --disable-bz2)
endif()
find_package(LibLZMA)
if(NOT LIBLZMA_FOUND)
  set(HTSLIB_DISABLE ${HTSLIB_DISABLE} --disable-lzma)
endif()
ExternalProject_add(
    htslib
    SOURCE_DIR ${HTSLIB_ROOT}
    CONFIGURE_COMMAND cd ${HTSLIB_ROOT} && autoreconf -i && ./configure ${HTSLIB_DISABLE}
    BUILD_COMMAND cd ${HTSLIB_ROOT} && make -j
    INSTALL_COMMAND ""
  )
add_library(hts SHARED IMPORTED)
set_target_properties(hts PROPERTIES IMPORTED_LOCATION ${HTSLIB_ROOT}/libhts.so)
include_directories(${HTSLIB_ROOT})
add_dependencies(biovoltron htslib)

# link library
target_link_libraries(biovoltron INTERFACE ${TBB_IMPORTED_TARGETS})
target_link_libraries(biovoltron INTERFACE range_v3)
target_link_libraries(biovoltron INTERFACE z)
target_link_libraries(biovoltron INTERFACE Boost::boost)
target_link_libraries(biovoltron INTERFACE OpenMP::OpenMP_CXX)
target_link_libraries(biovoltron INTERFACE Threads::Threads)
target_link_libraries(biovoltron INTERFACE spdlog)
target_link_libraries(biovoltron INTERFACE hts)
target_compile_options(biovoltron INTERFACE
  -mavx -mavx2
  -Wno-sign-compare -Wno-nonnull -Wno-char-subscripts -Wno-narrowing)

# build test
option(BIOVOLTRON_TESTS "Build the tests" ON)
if(BIOVOLTRON_TESTS)
  include(CTest)
  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tests)
endif()

# build document
option(BIOVOLTRON_DOC "Build documentation" OFF)
if (BIOVOLTRON_DOC)
  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/docs)
endif()
