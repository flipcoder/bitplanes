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
        uuid("72c2ca20-6128-11e1-b86c-0800200c9a66")
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
            "boost_filesystem",
            "lua5.1"
            --"luabind"
        }
        files {
            "src/**.h",
            "src/**.cpp"
        }

        configuration { "linux" }
            includedirs {
                "/usr/include/lua5.1",
            }
        configuration {}


        configuration { "gmake" }
            buildoptions { "-std=c++0x -pedantic" }
        configuration {}
        
