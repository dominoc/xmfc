#ifndef _XMFC_PROCESS_OPTIONS_H
#define _XMFC_PROCESS_OPTIONS_H
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
#include <profile.h>
#include <IxmfcOptions.h>
#include <string>
class XMFCProcessOptions: public IXMFCOptions {
private:
	std::string m_outfile;
	std::string m_infile;
	bool	    m_writeBinary;
public:
	XMFCProcessOptions();
	virtual bool set_options(unsigned long in_optionMask);
	virtual unsigned long get_options();
	virtual std::string toString();
	void set_infile(const char* in_name);
	std::string get_infile();

	void set_outfile(const char* in_name);
	std::string get_outfile();


	void set_binaryMode(bool in_mode);
	bool get_binaryMode();
};

#endif
