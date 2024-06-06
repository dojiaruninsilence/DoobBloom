project "portAudio"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
    staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/common/**.c",
        "src/hostapi/wasapi/**.c",
        "src/hostapi/dsound**.c",
        "src/hostapi/asio**.c",
        "src/hostapi/wdmks**.c",
        "src/hostapi/wmme**.c",
        "src/os/win/**.c",
        "src/*.c",
		"src/**.h"
	}

	includedirs 
	{
		"include",
		"src/common",
		"src/hostapi/",
		"src/os/win"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"

	filter "configurations:Debug"
		defines { "PA_ENABLE_DEBUG_OUTPUT" }
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

    filter "configurations:Dist"
		runtime "Release"
		optimize "on"
        symbols "off"
