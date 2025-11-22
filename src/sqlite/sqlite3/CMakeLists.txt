add_library(sqlite3 STATIC sqlite3.c)

target_compile_definitions(sqlite3 PRIVATE
  SQLITE_THREADSAFE=1
  SQLITE_DQS=0
  SQLITE_DEFAULT_MEMSTATUS=0
  SQLITE_DEFAULT_WAL_SYNCHRONOUS=1
  SQLITE_MAX_EXPR_DEPTH=0
  SQLITE_STRICT_SUBTYPE=1
  SQLITE_USE_ALLOCA
  SQLITE_USE_URI
  SQLITE_ENABLE_COLUMN_METADATA
  SQLITE_ENABLE_FTS5
  SQLITE_ENABLE_RTREE
  SQLITE_OMIT_DEPRECATED
  SQLITE_OMIT_PROGRESS_CALLBACK
  SQLITE_OMIT_SHARED_CACHE
  SQLITE_LIKE_DOESNT_MATCH_BLOBS
)

if(MSVC)
else()
  target_compile_options(sqlite3 PRIVATE -Wno-stringop-overread)
endif()

if(WIN32)
  target_link_libraries(sqlite3 PRIVATE ws2_32 shell32)
  target_compile_definitions(sqlite3 PRIVATE
    _CRT_SECURE_NO_WARNINGS
    _CRT_NONSTDC_NO_DEPRECATE
  )
else()
  target_link_libraries(sqlite3 PRIVATE pthread dl m)
endif()
