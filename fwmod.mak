# fwmod.mak
# Created by IBM WorkFrame/2 MakeMake at 15:38:31 on 8 Jan 1996
#
# The actions included in this make file are:
#  Compile::C++ Compiler
#  Link::Linker

.SUFFIXES: .c .obj 

.all: \
    .\fwmod.exe

.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /Ss /Oc /C %s

.\fwmod.exe: \
    .\fwmod.obj \
    {$(LIB)}fwmod.def
    @echo " Link::Linker "
    icc.exe @<<
     /B" /exepack:2"
     /Fefwmod.exe 
     fwmod.def
     .\fwmod.obj
<<

.\fwmod.obj: \
    "H:\Nils.C++\FWMod\fwmod.c" \
    {"H:\Nils.C++\FWMod;$(INCLUDE);"}fwmod.h
