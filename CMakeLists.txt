cmake_minimum_required(VERSION 3.10)

add_library(snxlib snxlib.c)

target_include_directories(snxlib PUBLIC includes)
set_target_properties(snxlib PROPERTIES PUBLIC_HEADER includes/snxlib.h)
set_target_properties(snxlib PROPERTIES SOVERSION 1)

install(TARGETS snxlib
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  PUBLIC_HEADER DESTINATION include
)