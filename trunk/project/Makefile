# This file is part of XMFC.

# Copyright (C) 2011	Rolf S. Adelsberger 
# 			mail: <[lastname]@gmail.com>

# XMFC is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# XMFC is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with XMFC.  If not, see <http://www.gnu.org/licenses/>.


ROOT=..
SRC_ROOT=$(ROOT)/src
SRC_INCL=$(SRC_ROOT)/include

XSENS=$(ROOT)/xsens

CFLAGS=-I $(SRC_INCL) -I $(XSENS)/include

LDFLAGS=-lcurses -lxsens -lrt

LIBS=-L$(ROOT)/lib

XSENS_LIB=libxsens.so

BIN=$(ROOT)/bin

XSENS_FILES=$(wildcard $(SRC_INCL)/*.h) $(wildcard $(SRC_ROOT)/*.c??)

CC=g++

all: xsens xmfc

xmfc: $(XSENS_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) $(filter %.c %.cpp,$^) -o $(ROOT)/bin/$@
	cp $(ROOT)/lib/$(XSENS_LIB) $(ROOT)/bin


xsens: lib/libxsens.so


lib/libxsens.so: $(XSENS)/Makefile
	$(MAKE) -C $(XSENS)


clean:
	@rm -rf $(BIN)/xmfc $(BIN)/$(XSENS_LIB)
	@$(MAKE) -C $(XSENS) clean
