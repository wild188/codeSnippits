#define _BSD_SOURCE
#include <getopt.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include "support.h"

#include <unistd.h>

/*
 * host() - Print the hostname of the machine on which this program is
 *          running, formatted a few different ways
 */
void host(void) {
    /* TODO: Complete this function */

  char name[255];

  gethostname(name, 255);
  int len = strlen(name);
  
  //printf(" %s\n", strlwr(name));

  //printf(" %s\n", strupr(name));

  int i;

  for(i = 0; i < len; i++){
    putchar(tolower(name[i]));
  }
  putchar('\n');
  
  for(i = 0; i < len; i++){
    putchar(toupper(name[i]));
  }
  putchar('\n');
  
  for(i = 0; i < len; i++){
    if(i % 2){
      putchar(toupper(name[i]));
    }else{
      putchar(tolower(name[i]));
    }
  }
  putchar('\n');

  for(i = (len - 1); i >= 0; i--){
    putchar(name[i]);
  }
  putchar('\n');
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s\n", progname);
    printf("Display the hostname of the machine\n");
    printf("The name will be displayed four ways, in the following order, on "
           "four lines:\n");
    printf("  all lowercase\n");
    printf("  ALL UPPERCASE\n");
    printf("  mIxEd LoWeRaNdUpPeR\n");
    printf("  emantsoh (i.e., reversed)\n");
}

/*
 * main() - The main routine parses arguments and dispatches to the
 *          task-specific code.
 */
int main(int argc, char **argv) {
    /* for getopt */
    long opt;

    /* run a student name check */
    check_student(argv[0]);

    /* parse the command-line options.  For this program, we only support  */
    /* the parameterless 'h' option, for getting help on program usage. */
    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch(opt) {
          case 'h': help(argv[0]); break;
        }
    }

    /* no need to look at arguments before calling the code */
    host();
}
