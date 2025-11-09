add_subdirectory(codec)

if(${KOTOOLS_BUILD_SHARED})
  set(KOTOOLS_LIB_BUILD_FLAG SHARED)
else()
  set(KOTOOLS_LIB_BUILD_FLAG STATIC)
endif()

add_library(kotools ${KOTOOLS_LIB_BUILD_FLAG})

target_link_libraries(kotools PRIVATE
  codec_interface
)
