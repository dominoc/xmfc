#ifndef _PROFILE_H
#define _PROFILE_H
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

#define XMFC_OPTION(X) (1<<X)

// Data Options:
// =============
// use the time
#define XMFC_USE_TIM XMFC_OPTION(0)
// use accelerometer
#define XMFC_USE_ACC XMFC_OPTION(1)
// use gyroscope
#define XMFC_USE_GYR XMFC_OPTION(2)
// use magnetometer
#define XMFC_USE_MAG XMFC_OPTION(3)
// output euler angles
#define XMFC_USE_EUL XMFC_OPTION(4)
// output quaternion data
#define XMFC_USE_QUA XMFC_OPTION(5)
// include also raw data
#define XMFC_USE_RAW XMFC_OPTION(6)

// Processing Options
// ==================
#define XMFC_OUT_BINARY XMFC_OPTION(0)

#define OPTION_STRING "abgmeqrtf:o:"


#define FORMAT_STRING_3VEC "%.15f %.15f %.15f "
#define FORMAT_STRING_4VEC "%.15f %.15f %.15f %.15f"


#endif
