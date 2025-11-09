add_library(threadpool_interface INTERFACE)

target_sources(threadpool_interface INTERFACE
  taskqueue.cpp
)

if(${KOTOOLS_BUILD_DIVIDEDLY})
  add_library(kotool_threadpool ${KOTOOLS_LIB_BUILD_FLAG})
  target_link_libraries(kotool_threadpool PRIVATE threadpool_interface)
endif()
