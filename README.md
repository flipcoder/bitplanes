![bitplanes](https://raw.githubusercontent.com/flipcoder/bitplanes/af2593329cefd1f9d5fe390ae58deb4a92233fad/bin/data/interface/logo_a.png)

http://github.com/flipcoder/bitplanes

Copyright &copy; 2012 Grady O'Connell

See CREDITS for a list of all contributors
See LICENSE for more information

=====

## Gameplay Video ##

[![Gameplay Video](http://img.youtube.com/vi/NdNzup_Uz4Q/0.jpg)](http://www.youtube.com/watch?v=NdNzup_Uz4Q)

## Credits ##

### Programming
- Grady O'Connell (@flipcoder, flipcoder@gmail.com)

### Graphics
- Mark "Alfred" McDaniel (@AlfredAnonymous, alfred523@gmail.com)

### Music & Sound
- Grady O'Connell (@flipcoder, flipcoder@gmail.com)

## About ##

Bitplanes is a retro-styled vertical shooter written in C++ using the Allegro library and Lua for scripting.
It is temporarily limited to MSVC2010-compatible C++11 features, although I develop it in Linux so every once in
a while I'll add something incompatible by accident.

## Building ##

If you're on Ubuntu, run:
    chmod +x get_libs.sh && ./get_libs.sh

This will get most of the libraries you need, with the exception of Allegro5, which you can
build yourself using the instructions at the following link: http://wiki.allegro.cc/index.php?title=Ubuntu_and_Allegro_5

If you're on another distro or windows, you'll need allegro5, boost, and lua5.1.  For a list of libs you'll need, look at:
    third_party/lib_names.txt

Once you've gotten the libraries, build it with:
    make

For windows users, I recommend grabbing binary versions of the libraries, and adding them to c:/msvc/libs and c:/msvc/include (or something similar).
then add those directories into MSVC's search path.  Before you run the .exe, Make sure you have right the DLLs in your env path or in the bitplanes bin folder.

## Creating Maps ##

Bitplanes has a basic Lua API for spawning, hooking, and interfacing with objects and parts of the game engine.  For an example map and boss fight, look at:
    bin/data/maps/road.lua

Add custom maps by appending the name to data/maps/map.list

It does not take advantage of Lua's object system but instead uses IDs to refer to each "hooked" object in the system (see ScriptInterface.h/cpp)

Objects (including stats of players, weapons, and enemies) look at the .ini files under:
    bin/data/objects/

