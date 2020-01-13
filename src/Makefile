#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := rectangle.cpp sprite.cpp circle.cpp object.cpp hitbox.cpp
# header files in this project
HEADERS := json.hpp jsonsfml.hpp factory.hpp object.hpp rectangle.hpp circle.hpp sprite.hpp background_tile.hpp game.hpp player.hpp hitbox.hpp settings.hpp

# other places to look for files for this project
SEARCH  := objects . engine factory

# set REATIVE to the next higher directory 
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.native
