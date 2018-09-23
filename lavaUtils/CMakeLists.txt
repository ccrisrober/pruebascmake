set( LAVAUTILS_PUBLIC_HEADERS
	Mesh.h
	Material.h
	ModelImporter.h
	Geometry.h
	CustomMaterial.h
	ThreadPool.h
	###Glsl2SPV.h
	CustomFramebuffer.h
	CustomPingPong.h

	Wrappers.h

	##../thirdparty/imgui/imgui.h
	##VulkanUI.h

	glmConfig.h

	States.h
)

set( LAVAUTILS_SOURCES
	Mesh.cpp
	Material.cpp
	ModelImporter.cpp
	Geometry.cpp
	CustomMaterial.cpp
	ThreadPool.cpp
	###Glsl2SPV.cpp
	CustomFramebuffer.cpp

	Wrappers.cpp

	##../thirdparty/imgui/imgui.cpp
	##../thirdparty/imgui/imgui_draw.cpp

	##VulkanUI.cpp

	States.cpp
)

set( LAVAUTILS_HEADERS
)

set( LAVAUTILS_MOC_HEADERS
)

set( LAVAUTILS_LINK_LIBRARIES
	lava
	${GLM_LIBRARIES}
	${ASSIMP_LIBRARIES}
	###${GLSLANG_LIBRARIES}
)

add_library( lavaUtils STATIC 
  ${LAVAUTILS_SOURCES}
  ${LAVAUTILS_PUBLIC_HEADERS}
  ${LAVAUTILS_HEADERS}
)
target_link_libraries( lavaUtils ${LAVAUTILS_LINK_LIBRARIES} )