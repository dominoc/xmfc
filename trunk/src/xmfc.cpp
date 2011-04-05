#include <xmfc.h>

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

using namespace xsens;

int			g_userQuit = 0;
xsens::Cmt3             cmt3;
FILE *			g_outputFile = NULL;
XMFCDataOptions		g_dataOptions;
XMFCProcessOptions	g_processOptions;

int main(int argc, char * argv[]) {
  int			l_retMain = 0;
  XsensResultValue	l_res;
  int			l_nDevices = 0;
  Packet*		l_packet = NULL;
  bool			l_reportRaw = false;
  bool			l_outBinary = false;

  CmtVector		l_acc, l_mag, l_rot;
  CmtShortVector	l_accR, l_magR, l_rotR;
  CmtEuler		l_eul;
  CmtQuat		l_quat;
  CmtRawData		l_raw;
  uint64_t              l_timeStamp;
  uint32_t*             l_devIDs;

  // Set exit function
  atexit(exitFunc);

  if(argc < 2) {
    usage();
    l_retMain = -1;
    goto end;
  }

  init(argc, argv, &g_dataOptions, &g_processOptions);

  report_tasks(&g_dataOptions, &g_processOptions);

  l_outBinary = g_processOptions.get_binaryMode();

  l_res = cmt3.openLogFile(g_processOptions.get_infile().c_str());

  if(l_res != XRV_OK) {
    printf("Error opening file '%s'!\n",g_processOptions.get_infile().c_str());
    l_retMain = -1;
    goto end;
  }

  if(g_processOptions.get_outfile().length() > 0) {
    g_outputFile = fopen(g_processOptions.get_outfile().c_str(),"w");
  } else {
    g_outputFile = fopen("output.ascii","w");
  }
	
  if(g_outputFile == NULL) {
    printf("Error opening output file '%s'!\n",g_processOptions.get_outfile().c_str());
    l_retMain = -1;
    goto end;
  }

  // see how many devices were present..
  l_nDevices = cmt3.getMtCount();

  // initialize the packet structure
  l_packet = new Packet((unsigned short)l_nDevices,cmt3.isXm());

  // make room for the dev ids
  l_devIDs = (uint32_t*)calloc(l_nDevices,sizeof(uint32_t));

  for(int d = 0; d < l_nDevices; d++) {
    cmt3.getMtDeviceId(d,l_devIDs[d]);    
  }
  
  // check if there is raw data...
  cmt3.readDataPacket(l_packet);

  if(g_dataOptions.use_raw && !l_packet->containsRawData()) {
    warning("[WARNING]: Data does not contain raw data!\n");
    g_dataOptions.use_raw = false;
  }
  cmt3.resetLogFileReadPos();
  
  write_header(g_outputFile,l_nDevices,l_devIDs,g_dataOptions.get_options(), g_processOptions.get_options());

  l_reportRaw = g_dataOptions.use_raw;

  while(l_res == XRV_OK) {

    l_res = cmt3.readDataPacket(l_packet);

    for(int dev = 0; dev < l_nDevices; dev++) {

      if(l_reportRaw) {
	l_raw = l_packet->getRawData();
      }

      // report the time stamp
      if(g_dataOptions.use_tim) {
	l_timeStamp = l_packet->getRtc(dev);
	write_1vec(g_outputFile,&l_timeStamp,&g_processOptions);
      }

      if(g_dataOptions.use_acc) {

	l_acc = l_packet->getCalAcc(dev);
	write_3vec(g_outputFile,l_acc.m_data,&g_processOptions);
				
	if(l_reportRaw) {
	  l_accR = l_raw.m_acc;
	  write_3vec(g_outputFile,l_accR.m_data,&g_processOptions);
	}
      }

      if(g_dataOptions.use_gyr) {
	l_rot = l_packet->getCalGyr(dev);

	write_3vec(g_outputFile,l_rot.m_data,&g_processOptions);

	if(l_reportRaw) {
	  l_rotR = l_raw.m_gyr;
	  write_3vec(g_outputFile,l_rotR.m_data,&g_processOptions);
	}
      }

      if(g_dataOptions.use_mag) {
	l_mag = l_packet->getCalMag(dev);	
	write_3vec(g_outputFile,l_mag.m_data,&g_processOptions);

	if(l_reportRaw) {
	  l_magR = l_raw.m_mag;
	  write_3vec(g_outputFile,l_mag.m_data,&g_processOptions);
	}
      }

      if(g_dataOptions.use_eul) {
	l_eul = l_packet->getOriEuler(dev);
	write_3vec(g_outputFile,l_eul.m_roll, l_eul.m_pitch, l_eul.m_yaw,&g_processOptions);
      }

      if(g_dataOptions.use_qua) {
	l_quat = l_packet->getOriQuat(dev);
	write_4vec(g_outputFile,l_quat.m_data,&g_processOptions);
      }
    }

    if(l_outBinary == false) {
      fprintf(g_outputFile,"\n");
    }
  }

  free(l_devIDs);

  fclose(g_outputFile);

  g_outputFile = NULL;

 end:
  return l_retMain;
}

void init(int argc, char* argv[],XMFCDataOptions* in_opts,XMFCProcessOptions* in_procOpts) {

  int		l_code;
  int		l_optind = 0;
  char*	l_optarg;

  while((l_code = getopt(argc,argv,OPTION_STRING,&l_optind,&l_optarg)) != -1) {
    switch(l_code) {
		  
    case 'a':
      // use accel
      in_opts->use_acc = true;
      break;
				
    case 'b':
      // use accel
      in_procOpts->set_binaryMode(true);
      break;

    case 'g':
      // use gyro
      in_opts->use_gyr = true;
      break;

    case 'm':
      // use magno
      in_opts->use_mag = true;
      break;

    case 'e':
      // output euler angles
      in_opts->use_eul = true;
      break;

    case 'q':
      // output quaternions
      in_opts->use_qua = true;
      break;

    case 'r':
      // report raw data
      in_opts->use_raw = true;
      break;

    case 't':
      // report raw data
      in_opts->use_tim = true;
      break;

    case 'f':
      in_procOpts->set_infile(l_optarg);
      break;

    case 'o':
      in_procOpts->set_outfile(l_optarg);
      break;

    default:
      break;
    }
  }
}


void write_header(FILE* in_fp, int in_nDev, uint32_t* in_devID, int in_dataFlags, int in_processFlags) {
  if(in_processFlags && XMFC_OUT_BINARY) {

    int buff[3];

    buff[0] = in_nDev;
    buff[1] = in_dataFlags;
    buff[2] = in_processFlags;
    fwrite(buff,sizeof(int),3,in_fp);
    fwrite(in_devID,sizeof(uint32_t),in_nDev,in_fp);
     
  } else {
    fprintf(in_fp,
	    "// #NDevices\n"
	    "// Data Flags\n"
	    "// Process Flags\n"
	    "// DeviceID[0] DeviceID[1]...\n "
	    "// TIME[0] ACC[0] ACC_r[0] ROT[0] ROT_r[0] MAG[0] MAG_r[0] EUL[0] QUAT[0] TIME[1] ACC[1] ... ACC[NDevices-1]...\n"
	    "%d\n"
	    "%d\n"
	    "%d\n",
	    in_nDev,
	    in_dataFlags,
	    in_processFlags);

    for(int d = 0; d < in_nDev; d++) {
      fprintf(in_fp,
	      "%d ",
	      in_devID[d]);
    }

    fprintf(in_fp,"\n");
  }
}

void write_1vec(FILE* in_fp, uint64_t* in_tuple, XMFCProcessOptions* in_procOpts) {
  if(in_procOpts->get_binaryMode()) {
    fwrite(in_tuple,
	   sizeof(uint64_t),
	   1,
	   in_fp);
  } else {
    fprintf(in_fp,
	    "%lld ",
	    in_tuple[0]);
  }
}

void write_4vec(FILE* in_fp, double* in_tuple, XMFCProcessOptions* in_procOpts) {
  if(in_procOpts->get_binaryMode()) {
    fwrite(in_tuple,
	   sizeof(double),
	   4,
	   in_fp);
  } else {
    fprintf(in_fp,
	    "%.15f %.15f %.15f %.15f ",
	    in_tuple[0],in_tuple[1],in_tuple[2],in_tuple[3]);
  }
}

void write_3vec(FILE* in_fp, double a, double b, double c, XMFCProcessOptions* in_procOpts) {
  double v[3];
  v[0] = a;
  v[1] = b;
  v[2] = c;
  write_3vec(in_fp,v,in_procOpts);
}

void write_3vec(FILE* in_fp, unsigned short* in_tuple, XMFCProcessOptions* in_procOpts) {
  if(in_procOpts->get_binaryMode()) {
    fwrite(in_tuple,
	   sizeof(unsigned short),
	   3,
	   in_fp);
  } else {
    fprintf(in_fp,
	    "%d %d %d ",
	    in_tuple[0],in_tuple[1],in_tuple[2]);
  }
}

void write_3vec(FILE* in_fp, double* in_tuple, XMFCProcessOptions* in_procOpts) {
  if(in_procOpts->get_binaryMode()) {
    fwrite(in_tuple,
	   sizeof(double),
	   3,
	   in_fp);
  } else {
    fprintf(in_fp,
	    "%.15f %.15f %.15f ",
	    in_tuple[0],in_tuple[1],in_tuple[2]);
  }
}


void exitFunc(void) {
  // Close any open COM ports
  cmt3.closePort();

  // get rid of keystrokes before we post our message

  while (_kbhit()) {
    _getch();
  }

  // wait for a keypress
  if (!g_userQuit) {
    printf("Press a key to exit\n");
    _getch();
  }

  if(g_outputFile != NULL) {
    fclose(g_outputFile);
  }
}


void usage() {
  printf("./xmfc '[-%s]' <in_file> <out_file>\n", OPTION_STRING);
}

void report_tasks(XMFCDataOptions* dataOptions, XMFCProcessOptions* processOptions) {
	
  printf("Process Options:\n"
	 "----------------\n"
	 "%s\n"
	 "\n"
	 "Data Options:\n"
	 "-------------\n"
	 "%s\n",
	 processOptions->toString().c_str(),
	 dataOptions->toString().c_str());
}

void warning(const char* in_str) {
  printf("\n%s\n",in_str);
}


