# Noctis IV LR

[![pipeline status](https://gitlab.com/dgcole/noctis-iv-lr/badges/master/pipeline.svg)](https://gitlab.com/dgcole/noctis-iv-lr/commits/master)

Noctis IV LR aims to eventually port Noctis IV to run on modern Windows and
Linux. The starting point was the base Noctis IV source code. Neither NIV+ nor
NICE were used, because the added layer of cruft on top of both would have
made the work of porting it more difficult. The bugs fixed by NIV+, however, will
all also be fixed in Noctis IV LR before a stable release.

## Roadmap
1) Rewrite as much of the assembly as possible in C++.
2) Move from BorlandC++ to the Digital Mars C++ compiler.
3) Use DMC's DOS32 feature to transition Noctis to a 32-bit protected mode program, in order to simplify its usage of memory and refactor the codebase with less restrictions.
4) Transition Noctis to a Win32 program, still using DMC.
5) Move to Clang and get Noctis running as a 64-bit program on both Windows and Linux.
