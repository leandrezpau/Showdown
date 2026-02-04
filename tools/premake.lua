workspace "TestSDL"
    configurations { "Debug", "Release" }
    architecture "x64"

    -- Aquí forzamos que TODO se genere en /build
    location "../build"

project "TestSDL"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir "../bin"
    objdir "../build/obj"

    files { "../src/*.cc" }

    includedirs { "../include" }

    libdirs { "../lib/x64" }

    links { "SDL3.lib" }

    postbuildcommands {
        "{COPY} ../bin/SDL3.dll %{cfg.targetdir}"
    }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"
