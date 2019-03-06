workspace "LinaEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
IncludeDir = {}
IncludeDir["SDL"] = "LinaEngine/vendor/SDL2-2.0.9/include"
IncludeDir["SPDLOG"] = "LinaEngine/vendor/spdlog/include"
IncludeDir["GLM"] = "LinaEngine/vendor/glm"
IncludeDir["GLAD"] = "LinaEngine/vendor/glad/include"
IncludeDir["GLFW"] = "LinaEngine/vendor/GLFW/include"

DLLDir = {}
DLLDir["SDL"] = "LinaEngine/vendor/SDL2-2.0.9/lib/x64"
DLLDir["LinaEngine"] = "bin/" .. outputdir .. "/LinaEngine"

LibDir = {}
LibDir["SDL"] = "LinaEngine/vendor/SDL2-2.0.9/lib/x64"

include "LinaEngine/vendor/glad"
include "LinaEngine/vendor/GLFW"

project "LinaEngine"
	location "LinaEngine"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")
	
	pchheader "LinaPch.hpp"
	pchsource "LinaEngine/src/LinaPch.cpp"
	
	files
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.SPDLOG}",
		"%{IncludeDir.SDL}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.GLFW}"
	}
	
	libdirs
	{
		"%{LibDir.SDL}"
	}
	
	links
	{
		"SDL2.lib",
		"SDL2main.lib",
		"glad",
		"opengl32.lib",
		"GLFW"
	}
			
		filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"LINA_PLATFORM_WINDOWS",
			"LINA_BUILD_DLL",
			"LINA_ENABLE_ASSERTS",
			"LINA_ENABLE_LOGGING",
			"LLF_INPUTANDWINDOW_GLFW",
			"LLF_GRAPHICS_OPENGL",
			"IMGUI_IMPL_OPENGL_LOADER_GLAD",
			"STB_IMAGE_IMPLEMENTATION"
		}

	
		
	filter "configurations:Debug"
		defines "LINA_DEBUG"
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "LINA_RELEASE"
		buildoptions "/MD"
		optimize "On"
		
	filter "configurations:Dist"
		defines "LINA_DIST"
		buildoptions "/MD"
		optimize "On"

	--[[
	filters {"system:windows", "configurations:Release"}
		buildoptions "/MT"
	--]]
	

project "Sandbox"

	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"LinaEngine/vendor/spdlog/include",
		"LinaEngine/src"
	}
	
	links
	{
		"LinaEngine"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"LINA_PLATFORM_WINDOWS",
			"LINA_ENABLE_LOGGING",
		}
		
		postbuildcommands
		{	
			
			("{COPY}  ../%{DLLDir.LinaEngine}/LinaEngine.dll  ../bin/" .. outputdir .. "/Sandbox"),
			("{COPY} ../%{DLLDir.SDL}/SDL2.dll ../bin/" .. outputdir .. "/Sandbox"),
			("{COPY} ../Sandbox/Resources ../bin/" .. outputdir .. "/Sandbox/Resources")
			--- ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"),	
			--- ("{COPY} ../%{DLLDir.SDL}/SDL2.dll ../bin/" .. outputdir .. "/Sandbox")
		}

		
	filter "configurations:Debug"
		defines "LINA_DEBUG"
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "LINA_RELEASE"
		buildoptions "/MD"
		optimize "On"
		
	filter "configurations:Dist"
		defines "LINA_DIST"
		buildoptions "/MD"
		optimize "On"
		
				

	
project "LinaEditor"

	location "LinaEditor"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"LinaEngine/vendor/spdlog/include",
		"LinaEngine/src"
	}
	
	links
	{
		"LinaEngine"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"LINA_PLATFORM_WINDOWS",
			"LINA_ENABLE_LOGGING",
		}
		
		postbuildcommands
		{	
			
			("{COPY}  ../%{DLLDir.LinaEngine}/LinaEngine.dll  ../bin/" .. outputdir .. "/LinaEditor"),
			("{COPY} ../%{DLLDir.SDL}/SDL2.dll ../bin/" .. outputdir .. "/LinaEditor"),
			("{COPY} ../Sandbox/Resources ../bin/" .. outputdir .. "/LinaEditor/Resources")
			--- ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/LinaEditor"),	
			--- ("{COPY} ../%{DLLDir.SDL}/SDL2.dll ../bin/" .. outputdir .. "/LinaEditor")
		}

		
	filter "configurations:Debug"
		defines "LINA_DEBUG"
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "LINA_RELEASE"
		buildoptions "/MD"
		optimize "On"
		
	filter "configurations:Dist"
		defines "LINA_DIST"
		buildoptions "/MD"
		optimize "On"