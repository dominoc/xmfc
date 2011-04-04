#include <xmfcDataOptions.h>
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
XMFCDataOptions::XMFCDataOptions() {
  use_tim = false; // report time stamps (ms)
  use_acc = false; // save accelerator data
  use_gyr = false; // save gyroscope data
  use_mag = false; // save magnetometer data
  
  use_eul = false; // report euler angles
  use_qua = false; // report orientation quaternion
  use_raw = false; // report raw data
}


bool XMFCDataOptions::set_options(unsigned long in_optionMask) {

	use_tim = (in_optionMask & XMFC_USE_TIM) != 0;

	use_acc = (in_optionMask & XMFC_USE_ACC) != 0;
	use_gyr = (in_optionMask & XMFC_USE_GYR) != 0;
	use_mag = (in_optionMask & XMFC_USE_MAG) != 0;

	use_eul = (in_optionMask & XMFC_USE_EUL) != 0;
	use_qua = (in_optionMask & XMFC_USE_QUA) != 0;
	use_raw = (in_optionMask & XMFC_USE_RAW) != 0;

	return true;

}

unsigned long XMFCDataOptions::get_options() {
	unsigned long l_ret = 0;

	l_ret |= (use_tim)?XMFC_USE_TIM:0;

	l_ret |= (use_acc)?XMFC_USE_ACC:0;
	l_ret |= (use_gyr)?XMFC_USE_GYR:0;
	l_ret |= (use_mag)?XMFC_USE_MAG:0;

	l_ret |= (use_eul)?XMFC_USE_EUL:0;
	l_ret |= (use_qua)?XMFC_USE_QUA:0;
	l_ret |= (use_raw)?XMFC_USE_RAW:0;

	return l_ret;
};

std::string XMFCDataOptions::toString() {

	std::stringstream ss;

	ss << "\n<Options>\n";

	if(use_tim) 
		ss<< "\tuse TIME\n";

	if(use_acc) 
		ss<< "\tuse ACCELEROMETER\n";

	if(use_gyr) 
		ss<< "\tuse GYROSCOPE\n";

	if(use_mag) 
		ss<< "\tuse MAGNETOMETER\n";

	if(use_raw) 
		ss<< "\treport RAW data\n";

	if(use_eul) 
		ss<< "\treport EULER angles\n";

	if(use_qua)
		ss << "\treport QUATERNION data\n";

	ss << "</Options>";


	return ss.str();
}
