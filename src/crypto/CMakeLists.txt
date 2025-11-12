add_library(crypto_interface INTERFACE)

target_sources(crypto_interface INTERFACE
  md5.cpp
)

if(${KOTOOLS_BUILD_DIVIDEDLY})
  add_library(kotool_crypto ${KOTOOLS_LIB_BUILD_FLAG})
  target_link_libraries(kotool_crypto PRIVATE crypto_interface)
endif()
