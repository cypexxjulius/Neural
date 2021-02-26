workspace "Neural"
	architecture "x64"

	startproject "Sandbox"
	
	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include dirs

IncludeDirs = {}
IncludeDirs["GLFW"] = "Neural/vendor/GLFW/include"
IncludeDirs["Glad"] = "Neural/vendor/Glad/include"
IncludeDirs["ImGui"] = "Neural/vendor/imgui"
IncludeDirs["glm"] = "Neural/vendor/glm"


include "Neural/vendor/GLFW"
include "Neural/vendor/Glad"
include "Neural/vendor/imgui"

project "Neural"
	location "Neural"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("binInt/" .. outputdir .. "/%{prj.name}")

	pchheader "nlpch.h"
	pchsource "Neural/src/nlpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/Platform/**/**.h",
		"%{prj.name}/Platform/**/**.cpp"

	}

	includedirs 
	{ 
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.Glad}",
		"%{IncludeDirs.ImGui}",
		"%{IncludeDirs.glm}"

	}
	
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		systemversion "latest"

		defines 
		{
			"NL_PLATFORM_WINDOWS",
			"NL_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"NL_ENABLE_ASSERTS",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		defines "NL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "NL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "NL_DIST"
		runtime "Release"
		optimize "on"



		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("binInt/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{ 
		"Neural/vendor/spdlog/include",
		"%{IncludeDirs.glm}",
		"%{IncludeDirs.ImGui}",
		"Neural/src"	
	}
	
	links
	{
		"Neural"
	}
	
	filter "system:windows"
		systemversion "latest"

		defines {
			"NL_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "NL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "NL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "NL_DIST"
		runtime "Release"
		optimize "on"