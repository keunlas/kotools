# Is build shared library.
option(KOTOOLS_BUILD_SHARED "Is build shared library" OFF)
option(KOTOOLS_BUILD_DIVIDEDLY "Is enable CTest toolkit" ON)
option(KOTOOLS_INCLUDE_CTEST "Is enable CTest toolkit" ON)

# C++ Compile Options (Global)
add_compile_options(-Wall)
add_compile_options(-Werror)

# Message for debug
message(STATUS "KOTOOLS_BUILD_SHARED = ${KOTOOLS_BUILD_SHARED}")
message(STATUS "KOTOOLS_BUILD_DIVIDEDLY = ${KOTOOLS_BUILD_DIVIDEDLY}")
message(STATUS "KOTOOLS_INCLUDE_CTEST = ${KOTOOLS_INCLUDE_CTEST}")
