solution("bitplanes")
    configurations {"Debug", "Release"}

    location("build")
    targetdir("bin")

    configuration "Debug"
        defines { "DEBUG" }
        flags { "Symbols" }
    configuration "Release"
        defines { "NDEBUG" }
        flags { "Optimize" }

    project("bitplanes")
        kind("WindowedApp")
        language("C++")
        links {
            "allegro",
            "allegro_image",
            "allegro_acodec",
            "allegro_ttf",
            "allegro_font",
            "boost_system",
            "boost_filesystem"
        }
        files {
            "src/**.h",
            "src/**.cpp"
        }
        configuration { "gmake" }
            buildoptions { "-std=c++0x" }

