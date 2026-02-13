workspace "ShowDown"
    configurations { "Debug", "Release" }
    architecture "x64"

    -- La solución se genera en /build
    location "../build"

project "ShowDown"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    -- El exe se genera directamente en /bin
    targetdir "../bin"
    objdir "../build/obj"

    -- Archivos del proyecto
    files { "../src/*.cc", 
            "../src/*.h", 
            "../src/sqlfuncs/*.cc",
            "../src/sqlfuncs/*.h",
            "../include/sqlite/sqlite3.c" }

  includedirs {
    "../include",
    "../include/SDL3",
    "../include/SDL3_image",
    "../include/sqlite/**",
  }

  filter "system:macosx"
    architecture "ARM64"
    libdirs { "../lib/x64" }
    links { "SDL3", "SDL3_image" }
    
    linkoptions { 
      "-Wl,-rpath,@loader_path/../lib/x64" 
    }

  filter "system:windows"
    architecture "x64"
    libdirs { "../lib/x64" }
    links { "SDL3.lib", "SDL3_image.lib" }

  filter "configurations:Debug"
    symbols "On"
  filter "configurations:Release"
    optimize "On"