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

LIBDIR=../lib
SRC=src
INCL=include

SRC_FILES=$(wildcard $(SRC)/*.c??)
INCL_FILES=$(wildcard $(INCL)/*.h??)

CFLAGS=-I $(INCL) -fpic

CC=g++

all: $(LIBDIR)/libxsens.so

$(LIBDIR)/libxsens.so: $(patsubst %.cpp,%.o, $(SRC_FILES)) 
	ld -shared -o $@ $^

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm -rf $(SRC)/*.o