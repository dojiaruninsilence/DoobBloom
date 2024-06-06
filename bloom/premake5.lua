-- main premake
project "bloom"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}")

    files
	{
		"src/**.h",
		"src/**.cpp"
	}

    includedirs
    {
        "%{wks.location}/bloom/src",
        "%{wks.location}/source",
        "%{wks.location}/source/dUtils",
        "%{wks.location}/vendor",
        "%{wks.location}/vendor/spdlog/include"
    }

    links
    {
        "DoobBloom"
    }

    libdirs
    {
        "%{wks.location}/bin/" .. outputdir .. "/DoobBloom"
    }

    filter "system:windows"
		systemversion "latest"

        links { "winmm", "ole32" }

	filter "configurations:Debug"
		defines { "DB_DEBUG", "__RTAUDIO_DEBUG__" }
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