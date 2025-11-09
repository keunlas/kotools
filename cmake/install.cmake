# install include
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/kotools DESTINATION include)

# install lib
install(TARGETS kotools DESTINATION lib)

# install lib devidedly
if(${KOTOOLS_BUILD_DIVIDEDLY})
  install(TARGETS kotool_codec DESTINATION lib)
  install(TARGETS kotool_threadpool DESTINATION lib)
endif()
