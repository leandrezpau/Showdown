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
    files { "../src/**" }

    -- Rutas de SDL3
    includedirs { "../include" }
    libdirs { "../lib/x64" }

    -- Librerías
    links { "SDL3.lib" }

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
