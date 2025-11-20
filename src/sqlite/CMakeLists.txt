add_subdirectory(sqlite3)

add_library(sqlite_interface INTERFACE)
target_link_libraries(sqlite_interface INTERFACE sqlite3)
target_sources(sqlite_interface INTERFACE
  sqlite3.cpp
)

if(${KOTOOLS_BUILD_DIVIDEDLY})
  add_library(kotool_sqlite ${KOTOOLS_LIB_BUILD_FLAG})
  target_link_libraries(kotool_sqlite PRIVATE sqlite_interface)
endif()
