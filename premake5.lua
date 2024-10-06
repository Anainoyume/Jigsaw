workspace "Jigsaw"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Jigsaw/vendor/GLFW/include"

include "Jigsaw/vendor/GLFW"

project "Jigsaw"
	location "Jigsaw"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "jspch.h"
	pchsource "Jigsaw/src/jspch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}"
	}

	links {
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines {
			"JS_PLATFORM_WINDOWS",
			"JS_BUILD_DLL"
		}

		postbuildcommands {
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "JS_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "JS_RELRASE"
		optimize "On"

	filter "configurations:Dist"
		defines "JS_DIST"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Jigsaw/vendor/spdlog/include",
		"Jigsaw/src"
	}

	links {
		"Jigsaw"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines {
			"JS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "JS_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "JS_RELRASE"
		optimize "On"

	filter "configurations:Dist"
		defines "JS_DIST"
		optimize "On"