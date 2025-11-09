add_library(codec_interface INTERFACE)

target_sources(codec_interface INTERFACE
  base64.cpp
)

if(${KOTOOLS_BUILD_DIVIDEDLY})
  add_library(kotool_codec ${KOTOOLS_LIB_BUILD_FLAG})
  target_link_libraries(kotool_codec PRIVATE codec_interface)
endif()
