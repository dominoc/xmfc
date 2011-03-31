#ifndef _XMFC_H
#define _XMFC_H

/*!
This file is part of XMFC.

Copyright (C) 2011	Rolf S. Adelsberger 
					mail: <[lastname]@gmail.com>

XMFC is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

XMFC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with XMFC.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <stdio.h>

#ifdef _WIN32
 #include <objbase.h>
 #include <conio.h>
#else
 #include <kbhit.h>
 #include <curses.h>
 #define _kbhit kbhit
 #define _getch getch
#endif

#include <cmt3.h>
#include <xsens_list.h>
#include <cmtscan.h>


#include <profile.h>
#include <IxmfcOptions.h>
#include <xmfcDataOptions.h>
#include <xmfcProcessOptions.h>

#ifdef WIN32
	#include <getoptWIN.h>
#else
	#include <getoptLINUX.h>

#endif

void write_header(FILE* in_fp, int in_nDev, int in_dataFlags = 0, int in_processFlags = 0);

void write_4vec(FILE* in_fp, double* in_tuple, XMFCProcessOptions* in_procOpts);

void write_3vec(FILE* in_fp, double* in_tuple, XMFCProcessOptions* in_procOpts);
void write_3vec(FILE* in_fp, unsigned short* in_tuple, XMFCProcessOptions* in_procOpts);
void write_3vec(FILE* in_fp, double a, double b, double c, XMFCProcessOptions* in_procOpts);

void exitFunc(void);

void usage(void);

void parse_commandLine(int argc, char * argv[]);

void init(int argc, char* argv[], XMFCDataOptions* dataOptions, XMFCProcessOptions* processOptions);

void report_tasks( XMFCDataOptions* dataOptions, XMFCProcessOptions* processOptions);

void warning(const char* in_str);

#endif
