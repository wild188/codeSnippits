#include <getopt.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "support.h"
#include <unistd.h>

/*
 * alive() - install some signal handlers, set an alarm, and wait...
 */
volatile int completeFlag = 0;
volatile int denyFlag = 0;


void alarmHandeler(int sig){
  completeFlag = 1;
}

void interuptBlocker(int sig){
  denyFlag = 1;
  signal(SIGINT, interuptBlocker);
}

void killhandeler(int sig){
  completeFlag = 1;
}

void alive(void) {
    /* TODO: Complete this function */
    /* Note: you will probably need to implement some other functions */

  //Setting the alarm handeler to trip the competeFlag to end the
  //program and print the elapsed time
  signal(SIGALRM, alarmHandeler); 
  signal(SIGINT, interuptBlocker); //Denies the interupst and prints 'No!'

  //I think this is what the instructions want
  //signal(SIGKILL, killhandeler);
  
  struct timeval start, end;
  gettimeofday(&start, 0);
  //setting an alarm signal in 10 seconds
  alarm(10);
  //volatile int lastDenyFlag = denyFlag

  while(!completeFlag){
    //denyFlag used to print 'No!' on SIGINT
    if(denyFlag){
      printf("No!\n");
      denyFlag = 0;
    }
  }

  //After complete record the time and print the elapsed time
  gettimeofday(&end, 0);
  printf("Waited %d\n", (int)(end.tv_sec - start.tv_sec));
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s\n", progname);
    printf("Swallow SIGINT, exit on SIGALARM\n");
}

/*
 * main() - The main routine parses arguments and dispatches to the
 *          task-specific code.
 */
int main(int argc, char **argv) {
    /* for getopt */
    long opt;

    /* run a student name check */
    //check_student(argv[0]);

    /* parse the command-line options.  For this program, we only support  */
    /* the parameterless 'h' option, for getting help on program usage. */
    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch(opt) {
          case 'h': help(argv[0]); break;
        }
    }

    /* no need to look at arguments before calling the code */
    alive();
}
