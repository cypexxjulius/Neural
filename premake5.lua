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

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("binInt/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs { 
		"Neural/vendor/spdlog/include",
		"%{IncludeDirs.glm}",
		"Neural/src"	
	}
	
	links{
		"Neural"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"NL_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "NL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "NL_DIST"
		optimize "On"

project "Neural"
	location "Neural"
	kind "SharedLib"
	language "C++"
	
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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"NL_PLATFORM_WINDOWS",
			"NL_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"NL_ENABLE_ASSERTS"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "NL_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "NL_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "NL_DIST"
		buildoptions "/MD"
		optimize "On"


