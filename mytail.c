#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "support.h"

/*
 * tail_file() - display the last numlines lines of a file or stdin
 */
void tail_file(char *filename, int numlines) {
  /* TODO: Complete this function */
  if(numlines <= 0){
    printf("Please enter a number greater than 0\n");
    return;
  }

  FILE *file = fopen(filename, "r");
  int currentLine = 1;
  int charIndex = 0;
  char curChar;
  char lines[numlines][1024];

  //if no file is given we switch to read from stdin
  if(!file){
    file = stdin;
  }
  
  while((curChar = fgetc(file)) != EOF){
    //if the line is longer than 1024 characters we will start
    //overwriting the initial characters of the line
    if(charIndex > 1023){
      charIndex = 0;
    }
    
    lines[currentLine % numlines][charIndex] = curChar;

    //checks for a new line
    if(curChar == '\n'){
      //printf("Read in: %s\n", lines[currentLine % numlines]);
      charIndex = 0;
      currentLine++;
    }else{
      charIndex++;
    }
  }

  //sets the line to start printing at
  int printLine = 1;
  if(currentLine > numlines){
    printLine = currentLine - numlines;
  }
  
  int i = numlines;
  while(currentLine > 0 && i > 0){
    // iterates through the circular buffer
    int line = printLine % numlines;
    int j = 0;

    //prints each line
    while(lines[line][j] && ((curChar = lines[line][j]) != '\n')){
      putchar(curChar);
      j++;
    }
    //prints the newline character after each line
    putchar('\n');

    i--;
    printLine++;
    currentLine--;
  }
  fclose(file);
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s [FILE]\n", progname);
    printf("Print the last 10 lines  of FILE to STDOUT\n");
    printf("With no FILE, read from STDIN\n");
    printf("  -nK    print the last K lines instead of the last 10\n");
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
    /* the parameterless 'h' option, for getting help on program usage, */
    /* and the parametered 'n' option, for getting the number of lines. */
    /* TODO: parse the arguments correctly */
    //int linenumArg = 0;
    int lines = 10;
    int nFlag = 0;
    while ((opt = getopt(argc, argv, "hn:")) != -1) {
        switch(opt) {
          case 'h': help(argv[0]); break;
	case 'n': lines = atoi(optarg); nFlag = 1; break;
        }
    }

    /*
    while ((opt = getopt(argc, argv, "n")) != -1) {
      switch(opt) {
      case 'n': lines = atoi(optarg);; break;
      }
    }
    */

    /*
    if(linenumArg){
      lines = atoi(argv[argc-2]);
    }
    */
    
    //printf("%i\n", linenumArg);
    /* TODO: fix this invocation */

    if(argc > (1 + nFlag)){
      tail_file(argv[argc - 1], lines);
    }else{
      tail_file(NULL, lines);
    }
}
