#include <kbhit.h>

int kbhit(void) {
  struct termios term, oterm;
  int fd, c;


  fd = 0;
  c = 0;

  tcgetattr(fd, &oterm);
  memcpy(&term, &oterm, sizeof(term));
  
  term.c_lflag = term.c_lflag & (!ICANON);
  term.c_cc[VMIN] = 0;
  term.c_cc[VTIME] = 1;
  tcsetattr(fd, TCSANOW, &term);
  
  c = getchar();
  
  tcsetattr(fd, TCSANOW, &oterm);

  if (c != -1) {
    ungetc(c, stdin);
  }

  return ((c != -1) ? 1 : 0); 
}
