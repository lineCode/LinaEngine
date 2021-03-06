#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Author: Inan Evin
# www.inanevin.com
# 
# Copyright (C) 2018 Inan Evin
# 
# Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions 
# and limitations under the License.
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.6)
project(LinaEngine)
set(CMAKE_CXX_STANDARD 17)

#--------------------------------------------------------------------
# Set sources
#--------------------------------------------------------------------
set (LINAENGINE_SOURCES

	# CORE
    src/Core/Application.cpp
    src/Core/Layer.cpp
    src/Core/LayerStack.cpp
    src/Core/Transform.cpp
	
	# ECS 
	src/ECS/Systems/ECSMovementControlSystem.cpp
	src/ECS/ECSComponent.cpp
	src/ECS/ECSSystem.cpp
	src/ECS/EntityComponentSystem.cpp
	
	#Events
	src/Events/ActionDispatcher.cpp
	src/Events/ActionSubscriber.cpp
	
	#IMGUI
	src/IMGUI/IMGUILayer.cpp
	
	#Interfaces
	src/Interfaces/IInputSubscriber.cpp
	
	#PAM
	src/PackageManager/Generic/cmwc4096.cpp
	src/PackageManager/Generic/GenericMemory.cpp
	src/PackageManager/OpenGL/GLInputEngine.cpp
	src/PackageManager/OpenGL/GLRenderEngine.cpp
	src/PackageManager/OpenGL/GLWindow.cpp
	
	#Rendering
	src/Rendering/ArrayBitmap.cpp
	src/Rendering/DDSTexture.cpp
	src/Rendering/Shader.cpp
	src/Rendering/Texture.cpp
	src/Rendering/Vertex.cpp
	
	#Utility
	src/Utility/Math/Matrix.cpp
	src/Utility/Math/Quaternion.cpp
	src/Utility/Math/Transformation.cpp
	src/Utility/Math/Vector.cpp
	src/Utility/Math/VectorMath.cpp
	src/Utility/Log.cpp
	src/Utility/ResourceConstants.cpp
	

)

#--------------------------------------------------------------------
# Set headers
#--------------------------------------------------------------------
set(LINAENGINE_HEADERS

	#CORE
	include/Core/APIExport.hpp
	include/Core/Application.hpp
	include/Core/Common.hpp
	include/Core/DataStructures.hpp
	include/Core/Environment.hpp
	include/Core/Internal.hpp
	include/Core/Layer.hpp
	include/Core/LayerStack.hpp
	include/Core/Memory.hpp
	include/Core/STLImport.hpp
	include/Core/Transform.hpp

	
	#ECS
	include/ECS/Components/MovementControlComponent.hpp
	include/ECS/Components/RenderableMeshComponent.hpp
	include/ECS/Components/TransformComponent.hpp
	include/ECS/Systems/ECSMovementControlSystem.hpp
	include/ECS/ECSComponent.hpp
	include/ECS/ECSSystem.hpp
	include/ECS/EntityComponentSystem.hpp
	
	#EVENTS
	include/Events/Action.hpp
	include/Events/ActionDispatcher.hpp
	include/Events/ActionSubscriber.hpp
	include/Events/ApplicationEvent.hpp
	include/Events/Event.hpp
	include/Events/KeyEvent.hpp
	include/Events/MouseEvent.hpp
	
	#IMGUI
	include/IMGUI/IMGUILayer.hpp
	
	#Input
	include/Input/InputAxisBinder.hpp
	include/Input/InputEngine.hpp
	include/Input/InputMappings.hpp
	
	#Interfaces
	include/Interfaces/IInputSubscriber.hpp
	
	#LObject
	include/LObjects/Camera.hpp
	
	#Package Manager
	include/PackageManager/Generic/cmwc4096.hpp
	include/PackageManager/Generic/GenericMath.hpp
	include/PackageManager/Generic/GenericMemory.hpp
	include/PackageManager/Generic/GenericVectorMath.hpp
	include/PackageManager/OpenGL/GLInputEngine.hpp
	include/PackageManager/OpenGL/GLRenderengine.hpp
	include/PackageManager/OpenGL/GLWindow.hpp
	include/PackageManager/OpenGL/GLIMGUI.hpp
	include/PackageManager/SSE/SSEVectorMath.hpp
	include/PackageManager/PAMInputEngine.hpp
	include/PackageManager/PAMMath.hpp
	include/PackageManager/PAMMemory.hpp
	include/PackageManager/PAMRenderEngine.hpp
	include/PackageManager/PAMSIMD.hpp
	include/PackageManager/PAMVectorMath.hpp
	include/PackageManager/PAMWindow.hpp
	
	#Rendering
	include/Rendering/ArrayBitmap.hpp
	include/Rendering/DDSTexture.hpp
	include/Rendering/RenderEngine.hpp
	include/Rendering/Shader.hpp
	include/Rendering/Texture.hpp
	include/Rendering/Vertex.hpp
	include/Rendering/Window.hpp
	
	#Utility
	include/Utility/Math/Color.hpp
	include/Utility/Math/Math.hpp
	include/Utility/Math/Matrix.hpp
	include/Utility/Math/Quaternion.hpp
	include/Utility/Math/Transformation.hpp
	include/Utility/Math/Vector.hpp
	include/Utility/Math/VectorMath.hpp
	include/Utility/Log.hpp
	include/Utility/ResourceConstants.hpp
	
	# SPDLOG
	include/Utility/spdlog/spdlog.h
	include/Utility/spdlog/async.h
	include/Utility/spdlog/async_logger.h
	include/Utility/spdlog/common.h
	include/Utility/spdlog/formatter.h
	include/Utility/spdlog/logger.h
	include/Utility/spdlog/spdlog.h
	include/Utility/spdlog/tolib.c
	include/Utility/spdlog/tweakme.h
	include/Utility/spdlog/version.h
	include/Utility/spdlog/sinks/stdout_color_sinks.h
	include/Utility/spdlog/sinks/android_sink.h
	include/Utility/spdlog/sinks/ansicolor_sink.h
	include/Utility/spdlog/sinks/base_sink.h
	include/Utility/spdlog/sinks/basic_file_sink.h
	include/Utility/spdlog/sinks/daily_file_sink.h
	include/Utility/spdlog/sinks/dist_sink.h
	include/Utility/spdlog/sinks/msvc_sink.h
	include/Utility/spdlog/sinks/null_sink.h
	include/Utility/spdlog/sinks/ostream_sink.h
	include/Utility/spdlog/sinks/rotating_file_sink.h
	include/Utility/spdlog/sinks/sink.h
	include/Utility/spdlog/sinks/stdout_sinks.h
	include/Utility/spdlog/sinks/syslog_sink.h
	include/Utility/spdlog/sinks/systemd_sink.h
	include/Utility/spdlog/sinks/wincolor_sink.h
	include/Utility/spdlog/details/async_logger_impl.h
	include/Utility/spdlog/details/circular_q.h
	include/Utility/spdlog/details/console_globals.h
	include/Utility/spdlog/details/file_helper.h
	include/Utility/spdlog/details/fmt_helper.h
	include/Utility/spdlog/details/log_msg.h
	include/Utility/spdlog/details/logger_impl.h
	include/Utility/spdlog/details/mpmc_blocking_q.h
	include/Utility/spdlog/details/null_mutex.h
	include/Utility/spdlog/details/os.h
	include/Utility/spdlog/details/pattern_formatter.h
	include/Utility/spdlog/details/periodic_worker.h
	include/Utility/spdlog/details/registry.h
	include/Utility/spdlog/details/thread_pool.h
	include/Utility/spdlog/fmt/bin_to_hex.h
	include/Utility/spdlog/fmt/fmt.h
	include/Utility/spdlog/fmt/ostr.h
	include/Utility/spdlog/fmt/bundled/chrono.h
	include/Utility/spdlog/fmt/bundled/color.h
	include/Utility/spdlog/fmt/bundled/core.h
	include/Utility/spdlog/fmt/bundled/format.h
	include/Utility/spdlog/fmt/bundled/format-inl.h
	include/Utility/spdlog/fmt/bundled/locale.h
	include/Utility/spdlog/fmt/bundled/ostream.h
	include/Utility/spdlog/fmt/bundled/posix.h
	include/Utility/spdlog/fmt/bundled/printf.h
	include/Utility/spdlog/fmt/bundled/ranges.h
	include/Utility/spdlog/fmt/bundled/time.h

	#stb
	include/Utility/stb/stb.h
	include/Utility/stb/stb_c_lexer.h
	include/Utility/stb/stb_connected_components.h
	include/Utility/stb/stb_divide.h
	include/Utility/stb/stb_ds.h
	include/Utility/stb/stb_dxt.h
	include/Utility/stb/stb_easy_font.h
	include/Utility/stb/stb_herringbone_wang_tile.h
	include/Utility/stb/stb_image.h
	include/Utility/stb/stb_image_resize.h
	include/Utility/stb/stb_image_write.h
	include/Utility/stb/stb_leakcheck.h
	include/Utility/stb/stb_perlin.h
	include/Utility/stb/stb_rect_pack.h
	include/Utility/stb/stb_sprintf.h
	include/Utility/stb/stb_textedit.h
	include/Utility/stb/stb_tilemap_editor.h
	include/Utility/stb/stb_truetype.h
	include/Utility/stb/stb_vorbis.c
	include/Utility/stb/stb_voxel_render.h
	include/Utility/stb/stretchy_buffer.h
	
	#imgui
	include/Utility/imgui/imconfig.h
	include/Utility/imgui/imgui.cpp
	include/Utility/imgui/imgui_demo.cpp
	include/Utility/imgui/imgui_draw.cpp
	include/Utility/imgui/imgui_internal.h
	include/Utility/imgui/imgui_widgets.cpp
	include/Utility/imgui/imstb_rectpack.h
	include/Utility/imgui/imstb_textedit.h
	include/Utility/imgui/imstb_truetype.h
	
	#API
	include/Lina.hpp
	
	
	#Others
	include/EntryPoint.hpp
	include/LinaPch.hpp
	

	
)

#--------------------------------------------------------------------
# Define shared library & create an alias
#--------------------------------------------------------------------
add_library(${PROJECT_NAME} SHARED ${LINAENGINE_SOURCES} ${LINAENGINE_HEADERS})
add_library(Lina::Engine ALIAS ${PROJECT_NAME}) 

#--------------------------------------------------------------------
# Config & Options & Compile Definitions
#--------------------------------------------------------------------

set(LINAENGINE_DLL_DIR ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.dll)

option(LINA_ENABLE_LOGGING "Enables console logging" ON)
# option(LINA_GRAPHICS_OPENGL "Graphics: Use OpenGL" ON)
## FORCE OPENGL FOR NOW
set(LINA_GRAPHICS_OPENGL 1)
target_compile_definitions(${PROJECT_NAME} PUBLIC LINA_GRAPHICS_OPENGL=1)
target_compile_definitions(${PROJECT_NAME} PRIVATE LINA_BUILD_DLL=1)
target_compile_definitions(${PROJECT_NAME} PUBLIC STB_IMAGE_IMPLEMENTATION=1)

#
# if(LINA_GRAPHICS_OPENGL)
#	target_compile_definitions(${PROJECT_NAME} PUBLIC LINA_GRAPHICS_OPENGL=1)
# endif()

if(LINA_ENABLE_LOGGING)
	target_compile_definitions(${PROJECT_NAME} PRIVATE LINA_ENABLE_LOGGING=1)
endif()

if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC LINA_PLATFORM_WINDOWS=1)
endif()
if(APPLE)
    # for MacOS X or iOS, watchOS, tvOS (since 3.10.3)
    target_compile_definitions(${PROJECT_NAME} PUBLIC LINA_PLATFORM_APPLE=1)
endif()
if(UNIX AND NOT APPLE)
    # for Linux, BSD, Solaris, Minix
    target_compile_definitions(${PROJECT_NAME} PUBLIC LINA_PLATFORM_UNIX=1)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
   target_compile_definitions(${PROJECT_NAME} PUBLIC LINA_COMPILER_CLANG=1)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
   target_compile_definitions(${PROJECT_NAME} PUBLIC LINA_COMPILER_GNU=1)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
   target_compile_definitions(${PROJECT_NAME} PUBLIC LINA_COMPILER_MSVC=1)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
   target_compile_definitions(${PROJECT_NAME} PUBLIC LINA_COMPILER_INTEL=1)
else()
   target_compile_definitions(${PROJECT_NAME} PUBLIC LINA_COMPILER_OTHER=1)
endif()

#--------------------------------------------------------------------
# Build Type Config
#--------------------------------------------------------------------

if ( CMAKE_BUILD_TYPE STREQUAL "" )
	# CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
	# differentiation between debug and release builds.
	set(
		CMAKE_BUILD_TYPE
			"Debug"
		CACHE STRING
			"Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) \"Debug\" \"Release\" \"Distribution\"."
		FORCE
	)
endif ( CMAKE_BUILD_TYPE STREQUAL "" )

if ( CMAKE_BUILD_TYPE STREQUAL "Release" )
    target_compile_definitions(${PROJECT_NAME} PUBLIC LINA_RELEASE=1)
endif ( CMAKE_BUILD_TYPE STREQUAL "Release" )

if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    target_compile_definitions(${PROJECT_NAME} PUBLIC LINA_DEBUG=1)
endif ( CMAKE_BUILD_TYPE STREQUAL "Debug" )

#--------------------------------------------------------------------
# Subdirectory setup
#--------------------------------------------------------------------

set(GLAD_EXPORT OFF CACHE BOOL "" FORCE)
set(GLAD_INSTALL OFF CACHE BOOL "" FORCE)
set(GLAD_NO_LOADER OFF CACHE BOOL "" FORCE)
set(GLAD_REPRODUCIBLE OFF CACHE BOOL "" FORCE)
set(GLAD_EXTENSIONS "GL_EXT_texture_compression_s3tc" CACHE STRING "" FORCE)

set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


#--------------------------------------------------------------------
# Set include directories
#--------------------------------------------------------------------

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/vendor/glfw_submodule/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/vendor/glad_submodule/include)

# Language standard
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

#--------------------------------------------------------------------
# Subdirectories & linking
#--------------------------------------------------------------------

if(LINA_GRAPHICS_OPENGL)

	add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glfw_submodule)
	add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glad_submodule)

	# set_target_properties(glfw glad glad-generate-files PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)

	# Link libraries (e.g. logging)
	target_link_libraries(${PROJECT_NAME} 
		# ${CMAKE_THREAD_LIBS_INIT}     # Needed for unix builds to link to pthread
		# LOGGING
		PRIVATE glfw
		PRIVATE glad
	)
	
endif()
	

#--------------------------------------------------------------------
# Packages
#--------------------------------------------------------------------

if(LINA_GRAPHICS_OPENGL)
	find_package(OpenGL REQUIRED)
endif()

#--------------------------------------------------------------------
# Generate export header for this dll project 
#--------------------------------------------------------------------

include (GenerateExportHeader)
GENERATE_EXPORT_HEADER (LinaEngine
    BASE_NAME LinaEngine
    EXPORT_MACRO_NAME LINA_API
    EXPORT_FILE_NAME LinaCore.hpp
)

#--------------------------------------------------------------------
# Folder structuring in visual studio
#--------------------------------------------------------------------
if(MSVC_IDE)
	foreach(source IN LISTS LINAENGINE_HEADERS LINAENGINE_SOURCES)
		get_filename_component(source_path "${source}" PATH)
		string(REPLACE "${LinaEngine_SOURCE_DIR}" "" relative_source_path "${source_path}")
		string(REPLACE "/" "\\" source_path_msvc "${relative_source_path}")
				source_group("${source_path_msvc}" FILES "${source}")
	endforeach()
endif()



