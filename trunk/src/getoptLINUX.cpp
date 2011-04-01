#include <getoptLINUX.h>

char* optarg;
int optind, opterr, optopt;

int getopt(int argc, char *argv[], const char *in_optstring, int* in_optind, char** out_optarg) {

  int c = getopt(argc,argv,in_optstring);
  *out_optarg = optarg;

  return c;
  
}
