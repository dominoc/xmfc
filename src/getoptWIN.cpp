#ifdef _WIN32
#include <getoptWIN.h>
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

int getopt(int argc, char *argv[], char *in_optstring, int* in_optind, char** out_optarg) {
	char  l_c;
	char* l_cp;
	static char *l_next	= NULL;
	
	if (0 == (*in_optind)){
		l_next = NULL;
	}

	if (NULL == l_next || '\0' == *l_next) {
		if ((*in_optind) == 0)
			(*in_optind)++;

		if ((*in_optind) >= argc || '-' != argv[(*in_optind)][0] || '\0' == argv[(*in_optind)][1]) {
			(*out_optarg) = NULL;
			if ((*in_optind) < argc) {
				(*out_optarg) = argv[(*in_optind)];
			}
			return -1;
		}

		// end of options
		if (0 == strcmp(argv[(*in_optind)], "--")) {

			(*in_optind)++;
			(*out_optarg) = NULL;
 
			if ((*in_optind) < argc) {
				(*out_optarg) = argv[(*in_optind)];
			}
			return -1;
		}

		l_next = argv[(*in_optind)];
		l_next++;
		(*in_optind)++;
	}

	l_c = *l_next++;
	l_cp = strchr(in_optstring, l_c);

	if (NULL == l_cp || ':' == l_c){
		return '?';
	}

	l_cp++;

	if (':' == *l_cp ) {

		if ('\0' != *l_next ) {

			(*out_optarg) = l_next;
			l_next = NULL;

		} else if ((*in_optind) < argc) {

			(*out_optarg) = argv[(*in_optind)];
			(*in_optind)++;

		} else {
			return '?';
		}
	}

	return l_c;
}
#endif
