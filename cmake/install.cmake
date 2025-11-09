# install include
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/kotools DESTINATION include)

# install lib
install(TARGETS kotools DESTINATION lib)
install(TARGETS codec DESTINATION lib)
