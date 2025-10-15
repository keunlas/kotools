add_subdirectory(codec)

if(${KOTOOLS_BUILD_SHARED})
  add_library(kotools SHARED)
else() # !KOTOOLS_BUILD_SHARED
  add_library(kotools STATIC)
endif() # KOTOOLS_BUILD_SHARED

target_link_libraries(kotools PRIVATE
  codec
)
