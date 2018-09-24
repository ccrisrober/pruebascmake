include_directories(
  ${PROJECT_BINARY_DIR}/include
  ${PROJECT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/routes.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/routes.h)

FILE (GLOB demos ${CMAKE_CURRENT_SOURCE_DIR}/*)

include( glsl2spv )

glsl2spv( )

FOREACH( demo ${demos} )
  if( IS_DIRECTORY ${demo} )
    if( EXISTS ${demo}/CMakeLists.txt )
      string( REGEX REPLACE "^.*/([^/]*)$" "\\1" LINK_NAME ${demo} )
      #message(${LINK_NAME})
      add_subdirectory( ${LINK_NAME} )
    endif()
  endif()
ENDFOREACH( )
