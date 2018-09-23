cmake_minimum_required( VERSION 3.0 FATAL_ERROR )
project( lava )

# project version
set(VERSION_MAJOR 2)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")

# Default build type is Debug
if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug )
endif( NOT CMAKE_BUILD_TYPE )

if ( CMAKE_BUILD_TYPE MATCHES "Debug" )
  add_definitions( -DDEBUG )
endif( )

#add_definitions(-std=c++11)
SET(CMAKE_CXX_STANDARD 11)

find_package( Vulkan )

include_directories($ENV{VULKAN_SDK}/include)

#find_package( GLFW3 system 3.2.1 )

message(STATUS "Using find_package to locate Vulkan")
find_package(Vulkan)
message(STATUS "Vulkan FOUND = ${VULKAN_FOUND}")
message(STATUS "Vulkan Include = ${VULKAN_INCLUDE_DIR}")
message(STATUS "Vulkan Lib = ${VULKAN_LIBRARY}")

set(STBI_INCLUDE_DIR ../stbi)
find_package(STBI)

message(${STBI_INCLUDE_DIR})

find_package(GLFW)
find_package(GLM)

find_package( Boost COMPONENTS unit_test_framework )


option( LAVA_WITH_DEVICE_BUILDERS "enabling/disabling custom device builder" ON )
option( LAVA_WITH_EXAMPLES "LAVA examples" ON)
option( LAVAENGINE_WITH_COMPONENTS "LAVA with components" ON )

if ( LAVAENGINE_WITH_COMPONENTS )
  list(APPEND COMMON_FIND_PACKAGE_DEFINES LAVAENGINE_HASCOMPONENTS)
endif( )

if ( LAVA_WITH_DEVICE_BUILDERS )
  list(APPEND COMMON_FIND_PACKAGE_DEFINES LAVA_DEVICE_BUILDERS )
endif( )

#add glslang
option(ENABLE_GLSLANG_BINARIES "Enable GLSLang Binaries" OFF)
add_subdirectory( vendor/glslang )

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory( lava )
if( GLFW3_FOUND )
  add_subdirectory( glfwLava )
endif( )

if( QT5CORE_FOUND )
  add_subdirectory( qtLava )
endif( )

add_subdirectory( lavaUtils )
#add_subdirectory( lavaEngine )

add_subdirectory( demos )

if(${Boost_FOUND})
  add_subdirectory(tests)
endif()