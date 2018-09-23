set(SOURCES main.cpp)
set(HEADERS)

add_executable( VkInfo ${SOURCES} ${HEADERS})
target_link_libraries( VkInfo  PRIVATE lava )
#set_target_properties( VkInfo PROPERTIES FOLDER "Samples")