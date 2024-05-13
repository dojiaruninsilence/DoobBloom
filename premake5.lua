-- main premake
workspace "DoobBloom"
    architecture "x64"
    startproject "DoobBloom"

    configurations
    {
        "Debug", 
        "Release",
        "Dist"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    -- include directories relative to the root folder (main solution folder)
    IncludeDir = {}
    IncludeDir["glfw"] = "%{wks.location}/vendor/glfw/include"
    IncludeDir["glad"] = "%{wks.location}/vendor/glad/include"
    IncludeDir["imgui"] = "%{wks.location}/vendor/imgui"

    include "vendor/glfw"
    include "vendor/glad"
    include "vendor/imgui"

    include "source"
