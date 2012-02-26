solution("bitplanes")
    configurations {"Debug", "Release"}

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
            "allegro_audio",
            "allegro_acodec",
            "boost_system",
            "boost_filesystem"
        }
        files {
            "src/**.h",
            "src/**.cpp"
        }
        configuration { "gmake" }
            buildoptions { "-std=c++0x" }

