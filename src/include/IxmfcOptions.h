#ifndef _IXMFCOPTIONS_H
#define _IXMFCOPTIONS_H
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

#include <iostream>
#include <sstream>
#include <string>

class IXMFCOptions {
protected:
public:
	IXMFCOptions(){}
	virtual bool set_options(unsigned long in_optionMask) = 0;
	virtual unsigned long get_options() = 0;
	virtual std::string toString() {
		return std::string("");
	}
};

#endif