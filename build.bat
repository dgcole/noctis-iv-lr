:: NOTE: This bat file is meant to be run in a DOSBox environment with BCC on the path.
@echo off
:: Compile and link, targetting the 386 and using the large memory model.
bcc -ml -3 -ISRC\ SRC\NOCTIS.CPP SRC\NOCTIS-0.CPP SRC\NOCTIS-1.CPP
:: Clean up linker files.
del *.OBJ