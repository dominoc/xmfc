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
#include <xmfcProcessOptions.h>

XMFCProcessOptions::XMFCProcessOptions() {
  m_infile		= std::string("");
  m_outfile		= std::string("");
  m_writeBinary	= false;
}

bool XMFCProcessOptions::set_options(unsigned long in_optionMask) {

  return true;
}

unsigned long XMFCProcessOptions::get_options() {

  unsigned long l_ret = 0;

  if(m_writeBinary) {
    l_ret |= XMFC_OUT_BINARY;
  }

  return l_ret;

}

void XMFCProcessOptions::set_infile(const char* in_name) {
  m_infile = std::string(in_name);
}

std::string XMFCProcessOptions::get_infile() {
  return m_infile;
}

void XMFCProcessOptions::set_outfile(const char* in_name) {
  m_outfile = std::string(in_name);
}

std::string XMFCProcessOptions::get_outfile() {
  return m_outfile;
}

void XMFCProcessOptions::set_binaryMode(bool in_mode) {
  m_writeBinary = in_mode;
}

bool XMFCProcessOptions::get_binaryMode() {
  return m_writeBinary;
}

std::string XMFCProcessOptions::toString() {
  if(m_outfile.length() == 0){
    if(m_writeBinary) {
      m_outfile = "output.bin";
    } else {
      m_outfile = "output.ascii";
    }
  }

  std::stringstream ss;
  ss << "\n<Options>\n";
  ss << "\n\tInfile: '" << m_infile << "'";
  ss << "\n\tOutfile: '" << m_outfile << "'";
  ss << "\n\tBinary: '" << ((m_writeBinary)?"true":"false") << "'";
  ss << "\n</Options>\n";

  return ss.str();
}

