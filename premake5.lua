workspace "sdl_learning"
configurations {"Debug", "Release"}

project "sdl_learning"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  targetdir "bin"

files {"src/**.h", "src/**.cpp"}

links {"SDL2", "SDL2_image", "SDL2_ttf", "SDL2_net", "SDL2_mixer", "SDL2_gfx"}

defines {"_CRT_SECURE_NO_WARNINGS", "GLFW_INCLUDE_NONE"}
