@echo off
bcc -ml -4 -Isrc\ src\noctis.cpp src\noctis-0.cpp src\noctis-1.cpp
copy /b noctis.exe+res\supports.nct=noctis.exe
del noctis-0.obj noctis-1.obj noctis.obj