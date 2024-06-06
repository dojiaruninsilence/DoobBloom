project "rtAudio"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
    staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/**.cpp",
		"include/**.h",
		"RtAudio.cpp",
		"RtAudio.h",
		"rtaudio_c.cpp",
		"rtaudio_c.h"
	}

	includedirs 
	{
		".",
		"include"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"RTAUDIO_API_WASAPI",
			"__WINDOWS_WASAPI__"
		}

		links { "winmm", "ole32", "ksuser", "mfplat", "mfuuid", "wmcodecdspuuid" }

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"

		defines { "RTAUDIO_API_ALSA" }
        links { "asound", "pthread" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

    filter "configurations:Dist"
		runtime "Release"
		optimize "on"
        symbols "off"
