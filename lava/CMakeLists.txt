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
  #-DLAVA_EXPORTS
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

  Compiler.h

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

  Compiler.cpp
)

set( LAVA_HEADERS )

source_group( lavaSources FILES ${LAVA_SOURCES} )
source_group( lavaHeaders FILES ${LAVA_PUBLIC_HEADERS} )
source_group( lavaPrivate FILES ${LAVA_HEADERS} )

add_library( lava STATIC 
  ${LAVA_SOURCES}
  ${LAVA_PUBLIC_HEADERS}
  ${LAVA_HEADERS}
)

target_include_directories(lava
  PUBLIC    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
  PUBLIC    "$ENV{VULKAN_SDK}/include"
  PUBLIC    "${CMAKE_SOURCE_DIR}/vendor"
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
  INTERFACE "$ENV{VULKAN_SDK}/include"
  INTERFACE  "${PROJECT_SOURCE_DIR}"
)

target_link_libraries( lava
  ${VULKAN_LIBRARY}
  glslang
  OGLCompiler
  OSDependent
  #HLSL
  SPIRV
)