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
SOURCES := sensorlib.cpp pressure.cpp pulse.cpp

# header files in this project
HEADERS := library.hpp sensorlib.hpp pressure.cpp pulse.hpp

# other places to look for files for this project
SEARCH  := /home/user/Desktop/OOPC_OPDR/IPASS/library

# set RELATIVE to the next higher directory 
# and defer to the appropriate Makefile.* there
RELATIVE := ..
include $(RELATIVE)/Makefile.due
