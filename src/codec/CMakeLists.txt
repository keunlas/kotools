add_library(codec_interface INTERFACE)

target_sources(codec_interface INTERFACE
  base64.cpp
)

add_library(codec ${KOTOOLS_LIB_BUILD_FLAG})
target_link_libraries(codec PRIVATE codec_interface)
