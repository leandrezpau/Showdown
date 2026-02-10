workspace "TestSDL"
  configurations { "Debug", "Release" }
  location "../build"

project "TestSDL"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  targetdir "../bin"
  objdir "../build/obj"
  files { "../src/*.cc", "../src/*.h" }

  includedirs {
    "../include",
    "../include/SDL3",
    "../include/SDL3_image"
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