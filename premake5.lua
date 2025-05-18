workspace "sdl_learning"
configurations {"Debug", "Release"}

project "sdl_learning"

kind "ConsoleApp"
language "C++"
cppdialect "C++11"
targetdir "bin"

files {"src/**.h", "src/**.cpp"}

includedirs {"include", "/opt/homebrew/Cellar/sdl2/2.32.2/include"}

libdirs {"/opt/homebrew/Cellar/sdl2/2.32.2/lib"}

links {"SDL2", "SDL2_image", "SDL2_ttf"}

defines {"_CRT_SECURE_NO_WARNINGS", "GLFW_INCLUDE_NONE"}
