workspace "TestSDL"
    configurations { "Debug", "Release" }
    architecture "x64"

    -- La solución se genera en /build
    location "../build"

project "TestSDL"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    -- El exe se genera directamente en /bin
    targetdir "../bin"
    objdir "../build/obj"

    -- Archivos del proyecto
    files { "../src/*.cc", "../src/*.h" }

    -- Rutas de SDL3
    includedirs {
        "../include",
        "../include/SDL3",
        "../include/SDL3_image",
    }
    libdirs { "../lib/x64" }

    -- Librerías
    links {
        "SDL3.lib",
        "SDL3_image.lib"
    }

    -- Configuración MSVC recomendada
    filter "system:windows"
        systemversion "latest"
        defines { "_CRT_SECURE_NO_WARNINGS" }

    filter "configurations:Debug"
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        optimize "On"
        runtime "Release"
