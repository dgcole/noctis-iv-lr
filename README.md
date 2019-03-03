# Noctis IV LR

Noctis IV LR aims to eventually port Noctis IV to run on Linux and Modern Windows.
The starting point was the base Noctis IV source code. Neither NIV+ nor
NICE were used, because the added layer of cruft on top of both would have
made the work of porting it more difficult. The bugs fixed by NIV+, however, will
all also be fixed in Noctis IV LR before a stable release.

The goal for Noctis IV LR is to maintain compabitility with the original Noctis IV.
That means that stars should generate in the same positions, and planets should
look the same. Stars do currently generate in the correct positions, but there
will likely be problems with compatibility down the line. 

Currently, Noctis IV LR only runs on Linux and is using SDL2 for the windowing and
drawing. It will run on Windows down the line, I've just used some low level 
file I/O operations to make porting easier that are not available in Linux.

## Compiling
The CMake file is set up to use clang, but it probably works fine with GCC as well.
The only dependency is SDL2.
To build, run the following commands:
```
mkdir build && cd build && cmake .. && make && ln -sf ../res res
```

## Port Status

Currently, the vast majority of the rendering code still needs to be ported from
assembly. All of the non-planetary game logic has been ported. It's slow work
porting the rendering code, but it's entirely achievable given enough time.

## Differences from Vanilla
* SUPPORTS.NCT is loaded from the res/ folder instead of being appended to the binary.
* Fixed a bug with triads dexter above 1000. 
