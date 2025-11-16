add_subdirectory(codec)
add_subdirectory(threadpool)

if(${KOTOOLS_BUILD_SHARED})
  set(KOTOOLS_LIB_BUILD_FLAG SHARED)
else()
  set(KOTOOLS_LIB_BUILD_FLAG STATIC)
endif()
message(STATUS "KOTOOLS_LIB_BUILD_FLAG = ${KOTOOLS_LIB_BUILD_FLAG}")

add_library(kotools ${KOTOOLS_LIB_BUILD_FLAG})

target_link_libraries(kotools PRIVATE
  codec_interface
  threadpool_interface
)
