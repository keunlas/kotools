cmake_minimum_required(VERSION 3.16)
project(KoTools VERSION 1.0.0 LANGUAGES C CXX)

include(cmake/build_option.cmake)
include(cmake/cxx.cmake)
include(cmake/output.cmake)
include(cmake/ctest.cmake)

include_directories(BEFORE "include" "deps/include")

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(examples)

include(cmake/install.cmake)
include(cmake/cpack.cmake)
