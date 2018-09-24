#includes
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

if( STBI_FOUND )
  include_directories(${STBI_INCLUDE_DIR})
endif( )

#definitions
add_definitions(
  -DNOMINMAX
)

set( LAVA_PUBLIC_HEADERS
  includes.hpp
  noncopyable.hpp
  
  Display.h

  Buffer.h
  CommandBuffer.h
  Descriptor.h
  Instance.h
  Device.h
  PhysicalDevice.h
  Event.h
  Fence.h
  Log.h
  MemoryUtils.h
  StringUtils.hpp
  RenderAPICapabilites.h

  Image.h
  RenderPass.h
  Surface.h
  Sampler.h
  Semaphore.h
  Swapchain.h
  Texture.h
  Texture1D.h
  Texture2D.h
  TextureCubemap.h
  Texture2DArray.h
  Texture3D.h
  Queue.h
  QueryPool.h
  Framebuffer.h
  Pipeline.h

  utils.hpp

  VulkanResource.h
  lava.h
)

set( LAVA_SOURCES
  Display.cpp
  
  Buffer.cpp
  CommandBuffer.cpp
  Descriptor.cpp
  Instance.cpp
  Device.cpp
  PhysicalDevice.cpp
  Event.cpp
  Fence.cpp
  Log.cpp

  Image.cpp
  RenderPass.cpp
  Surface.cpp
  Sampler.cpp
  Semaphore.cpp
  Swapchain.cpp
  Texture.cpp
  Texture1D.cpp
  Texture2D.cpp
  TextureCubemap.cpp
  Texture2DArray.cpp
  Texture3D.cpp
  Queue.cpp
  QueryPool.cpp
  Framebuffer.cpp
  Pipeline.cpp

  utils.cpp

  VulkanResource.cpp
)

set( LAVA_HEADERS )


set(COMMON_LIBRARY_TYPE SHARED CACHE STRING
  "Library type {any combination of SHARED, STATIC}")
set_property(CACHE COMMON_LIBRARY_TYPE PROPERTY STRINGS SHARED STATIC)

function(common_library Name)
  set(PROJECT_INCLUDE_NAME ${Name})

  string(TOUPPER ${Name} NAME)

  set(INCLUDE_NAME ${${NAME}_INCLUDE_NAME})
  if(NOT INCLUDE_NAME)
    set(INCLUDE_NAME ${PROJECT_INCLUDE_NAME})
  endif()

  message(${INCLUDE_NAME})

  set(namespace ${${NAME}_NAMESPACE})
  if(NOT namespace)
    set(namespace ${PROJECT_namespace})
  endif()
  string(TOUPPER ${namespace} NAMESPACE)

  set(SOURCES ${${NAME}_SOURCES})
  set(HEADERS ${${NAME}_HEADERS})
  set(PUBLIC_HEADERS ${${NAME}_PUBLIC_HEADERS})
  set(LINK_LIBRARIES ${${NAME}_LINK_LIBRARIES})

  # Generate api.h and version.h/cpp for non-interface libraries
  if(${NAME}_SOURCES)
    set(PROJECT_VERSION_ABI ${${PROJECT_NAME}_VERSION_ABI})
    configure_file(${CMAKE_SOURCE_DIR}/CMake/cpp/api.h
      ${PROJECT_BINARY_DIR}/include/${INCLUDE_NAME}/api.h @ONLY)
    configure_file(${CMAKE_SOURCE_DIR}/CMake/cpp/version.h
      ${PROJECT_BINARY_DIR}/include/${INCLUDE_NAME}/version.h @ONLY)
    configure_file(${CMAKE_SOURCE_DIR}/CMake/cpp/version.cpp
      ${CMAKE_CURRENT_BINARY_DIR}/version.cpp @ONLY)



    list(APPEND PUBLIC_HEADERS
      ${PROJECT_BINARY_DIR}/include/${INCLUDE_NAME}/api.h
      ${PROJECT_BINARY_DIR}/include/${INCLUDE_NAME}/version.h)
    list(APPEND SOURCES ${CMAKE_CURRENT_BINARY_DIR}/version.cpp)
  endif( )

  #if(NOT ${NAME}_OMIT_LIBRARY_HEADER)
    generate_library_header(${NAME})
  #endif()

  if(SOURCES)
    list(SORT SOURCES)
  endif()
  if(HEADERS)
    list(SORT HEADERS)
  endif()
  if(PUBLIC_HEADERS)
    list(SORT PUBLIC_HEADERS)
  endif()

  source_group(\\ FILES CMakeLists.txt)
  source_group(${INCLUDE_NAME} FILES ${SOURCES} ${HEADERS} ${PUBLIC_HEADERS})

  if(NOT ${NAME}_LIBRARY_TYPE)
    set(${NAME}_LIBRARY_TYPE ${COMMON_LIBRARY_TYPE})
    if(NOT ${NAME}_LIBRARY_TYPE)
      set(${NAME}_LIBRARY_TYPE SHARED)
    endif()
  endif()

  foreach(LIBRARY_TYPE ${${NAME}_LIBRARY_TYPE})
    set(LibName ${Name})
    if(TARGET ${Name})
      set(LibName "${Name}_${LIBRARY_TYPE}")
    endif()

    if(NOT ${NAME}_SOURCES)
      add_library(${LibName} INTERFACE)
      _target_include_directories(INTERFACE)
    else( )
      # append a debug suffix to library name on windows or if user requests it
      common_set_lib_name_postfix()

      add_library(${LibName} ${LIBRARY_TYPE}
        ${SOURCES} ${HEADERS} ${PUBLIC_HEADERS})
      #set_target_properties(${LibName} PROPERTIES
      #  VERSION ${${PROJECT_NAME}_VERSION}
      #  SOVERSION ${${PROJECT_NAME}_VERSION_ABI}
      #  OUTPUT_NAME ${Name} FOLDER ${PROJECT_NAME})
      target_link_libraries(${LibName} ${LINK_LIBRARIES})

      _target_include_directories(PUBLIC)
    endif( )
  endforeach( )
endfunction( )


macro(common_set_lib_name_postfix)
  if(WIN32)
    set(CMAKE_DEBUG_POSTFIX "_D")
  elseif(COMMON_LIBRARY_DEBUG_POSTFIX)
    set(CMAKE_DEBUG_POSTFIX "_debug")
  else()
    set(CMAKE_DEBUG_POSTFIX "")
  endif()
endmacro()

# declare include directories for this target when using it in the build
# tree; the install tree include directory is declared via install()
# @param type: must be PUBLIC or INTERFACE
macro(_target_include_directories _type)
  target_include_directories(
      ${LibName} ${_type}
      "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>"
      "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>"
      "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>"
  )
  if(${NAME}_PUBLIC_INCLUDE_DIRECTORIES)
    target_include_directories(
      ${LibName} SYSTEM ${_type}
      "$<BUILD_INTERFACE:${${NAME}_PUBLIC_INCLUDE_DIRECTORIES}>"
      "$<INSTALL_INTERFACE:${${NAME}_PUBLIC_INCLUDE_DIRECTORIES}>"
    )
  endif()
endmacro()


macro(generate_library_header NAME)
  get_filename_component(__base_name ${INCLUDE_NAME} NAME)

  set(__generated_header ${PROJECT_BINARY_DIR}/include/${INCLUDE_NAME}/${__base_name}.h)
  set(__generated_header_in ${__generated_header}.in)

  message(${__generated_header_in})
  file(WRITE ${__generated_header_in}
    "// generated by CommonLibrary.cmake, do not edit\n"
    "#ifndef ${NAME}_H\n"
    "#define ${NAME}_H\n")
    foreach(PUBLIC_HEADER ${PUBLIC_HEADERS})
      if(IS_ABSOLUTE ${PUBLIC_HEADER})
        set(__base "${PROJECT_BINARY_DIR}/include/${INCLUDE_NAME}/")
        string(REGEX MATCH ${__base} __has_base ${PUBLIC_HEADER})
        if(__has_base)
          string(REPLACE ${__base} "" PUBLIC_HEADER ${PUBLIC_HEADER})
        else()
          get_filename_component(PUBLIC_HEADER ${PUBLIC_HEADER} NAME)
        endif()
      endif()
      if(NOT PUBLIC_HEADER MATCHES "defines.+\\.h" AND
        (PUBLIC_HEADER MATCHES ".*\\.h$" OR PUBLIC_HEADER MATCHES ".*\\.hpp$"))
        file(APPEND ${__generated_header_in}
          "#include <${INCLUDE_NAME}/${PUBLIC_HEADER}>\n")
      endif()
    endforeach()
  file(APPEND ${__generated_header_in} "#endif\n")

  # configure only touches file if changed, saves compilation after reconfigure
  configure_file( ${__generated_header_in} ${__generated_header} COPYONLY)
  list(APPEND PUBLIC_HEADERS ${__generated_header})
endmacro( )

set( LAVA_LINK_LIBRARIES
  ${VULKAN_LIBRARY}
  glslang
  OGLCompiler
  OSDependent
  #HLSL
  SPIRV
)

common_library( lava )

#target_link_libraries( lava
#  ${LAVA_LINK_LIBRARIES}
#)