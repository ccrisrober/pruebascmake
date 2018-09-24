set(SOURCES main.cpp)
set(HEADERS)

add_executable( RenderHeadless ${SOURCES} ${HEADERS})
target_link_libraries( RenderHeadless  PRIVATE lava )
#set_target_properties( RenderHeadless PROPERTIES FOLDER "Samples")