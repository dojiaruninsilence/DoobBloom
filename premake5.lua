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

    include "source"