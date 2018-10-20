@echo off
bcc -ml -2 -Isrc\ src\noctis.cpp src\noctis-0.cpp src\noctis-1.cpp
copy /b src\noctis.exe+res\supports.nct=src\noctis.exe