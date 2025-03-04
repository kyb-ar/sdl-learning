workspace "sdl_learning"
  configurations { "Debug", "Release" }

project "sdl_learning"

  kind "ConsoleApp"
  language "C++"
  targetdir "bin"

  files {
    "src/**.h",
    "src/**.cpp"
  }

  includedirs {
    "include",
  }

  links {
    "SDL2",
    "gtest"
  }

  defines {
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
  }
