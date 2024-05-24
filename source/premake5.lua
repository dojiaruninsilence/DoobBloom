-- DoobBloom premake

project "DoobBloom"
    kind "StaticLib"
    language "C++"
	cppdialect "C++17"
	staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}")

    pchheader "dbpch.h"
    pchsource "dUtils/dbpch.cpp"

    files
    {
        "**.h",
        "**.cpp"
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

    includedirs
    {
        "%{wks.location}/source",
        "%{wks.location}/source/dUtils",
        "%{wks.location}/vendor/spdlog/include",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.portAudio}"
    }

    links
    {
        "glfw",
        "glad",
        "imgui",
        "portAudio",
        "opengl32.lib",
        "dwmapi.lib"
    } 

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "DB_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "DB_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "DB_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "DB_DIST"
        runtime "Release"
        optimize "on"
