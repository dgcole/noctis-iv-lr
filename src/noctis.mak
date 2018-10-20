#
# Borland C++ IDE generated makefile
# Generated 10/19/2018 at 9:43:52 PM 
#
.AUTODEPEND


#
# Borland C++ tools
#
IMPLIB  = Implib
BCCDOS  = Bcc +BccDos.cfg 
TLINK   = TLink
TLIB    = TLib
TASM    = Tasm
#
# IDE macros
#


#
# Options
#
IDE_LinkFLAGSDOS =  -LC:\BC5\LIB
IDE_BFLAGS = 
LinkerLocalOptsAtDOS_noctisdexe =  -c -Tde
ResLocalOptsAtDOS_noctisdexe = 
BLocalOptsAtDOS_noctisdexe = 
CompInheritOptsAt_noctisdexe = -IC:\BC5\INCLUDE;C:\DOCUMENTS AND SETTINGS\ADMINISTRATOR\DESKTOP\NOCTIS\SRC 
LinkerInheritOptsAt_noctisdexe = -x
LinkerOptsAt_noctisdexe = $(LinkerLocalOptsAtDOS_noctisdexe)
ResOptsAt_noctisdexe = $(ResLocalOptsAtDOS_noctisdexe)
BOptsAt_noctisdexe = $(BLocalOptsAtDOS_noctisdexe)

#
# Dependency List
#
Dep_noctis = \
   noctis.exe

noctis : BccDos.cfg $(Dep_noctis)
  echo MakeNode

Dep_noctisdexe = \
   text3d.h\
   tdpolygs.h\
   noctis-d.h\
   noctis-0.h\
   gfx.h\
   fast3d.h\
   assembly.h\
   noctis-1.obj\
   noctis-0.obj\
   noctis.obj

noctis.exe : $(Dep_noctisdexe)
  $(TLINK)   @&&|
 /v $(IDE_LinkFLAGSDOS) $(LinkerOptsAt_noctisdexe) $(LinkerInheritOptsAt_noctisdexe) +
C:\BC5\LIB\c0l.obj+
noctis-1.obj+
noctis-0.obj+
noctis.obj
$<,$*
C:\BC5\LIB\bidsl.lib+
C:\BC5\LIB\fp87.lib+
C:\BC5\LIB\mathl.lib+
C:\BC5\LIB\cl.lib



|
noctis-1.obj :  noctis-1.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_noctisdexe) $(CompInheritOptsAt_noctisdexe) -o$@ noctis-1.cpp
|

noctis-0.obj :  noctis-0.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_noctisdexe) $(CompInheritOptsAt_noctisdexe) -o$@ noctis-0.cpp
|

noctis.obj :  noctis.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_noctisdexe) $(CompInheritOptsAt_noctisdexe) -o$@ noctis.cpp
|

# Compiler configuration file
BccDos.cfg : 
   Copy &&|
-W-
-w
-R
-v
-vi
-H
-H=noctis.csm
-ml
-f287
-g255
-2
-Og
-Oi
-Ov
-Z
-O
-Oe
-Ol
-Ob
-OW
-Oa
-Om
-Op
| $@


