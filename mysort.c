#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "support.h"

/*
 * sort_file() - read a file, sort its lines, and output them.  reverse and
 *               unique parameters are booleans to affect how the lines are
 *               sorted, and which lines are output.
 */

int reverseF;

int compare(const void* lineA, const void* lineB){
  int out = (strcmp(*(char **)lineA, *(char **)lineB) * reverseF);

  //printf("%s, %s = %i\n", lineA, lineB, out);

  return out;
}

void copyLine(char * line, char * temp, int size){

  //printf("Received %s\n", temp);

  int i;
  for(i = 0; i < size; i++){
    line[i] = temp[i];
    //printf("Coppied character %c\n", line[i]);
  }
}

void sort_file(char *filename, int unique, int reverse) {
    /* TODO: Complete this function */
    /* Note: you will probably need to implement some other functions */

  if(unique){
    
  }
  
  if(reverse){
    reverseF = -1;
    //printf("Reversed\n");
  }else{
    reverseF = 1;
  }
  //reverseF = reverse; 
  
  char* lines[1000000];
  if(!filename){
    return;
  }
  FILE *file = fopen(filename, "r");

  
  if(!file){
    //file = stdin;
    return;
  }
  
  
  char curLine[1024];
  int numLines = 0;
  int curChar;
  int i = 0;
  while((curChar = fgetc(file)) != EOF){
    if(curChar != '\n'){
      curLine[i] = curChar;
      i++;
    }else{
      curLine[i] = curChar;

      //printf("Read in: %s\n", curLine);

      i++;
      curLine[i] = 0;
      lines[numLines] = (char *)malloc((i));

      //printf("allocated the space \n");

      copyLine(lines[numLines], curLine, i);

      //printf("Coppied the line \n");
      
      numLines++;
      i = 0;
    }
  }
  fclose(file);
  
  qsort(lines, numLines, sizeof(char *), compare);  

  char * lastLine;
  for(i = 0; i < numLines; i++){
    if(unique){
      if(i > 0 && !strcmp(lastLine, lines[i])){
	free(lines[i]);
	continue;
      }
      printf("%s", lines[i]);
      lastLine = lines[i];
    }else{
      printf("%s", lines[i]);
    }
    free(lines[i]);
  }
}

int compare2(char* lineA, int lineAlength, char* lineB, int lineBlength, int reverse){
  int length = lineAlength;
  if(lineBlength < length){
    length = lineBlength;
  }

  //qsort(lines, numLines, sizeof(char *), compare); 
  
  int i;
  for(i = 0; i < length; i++){
    int dif = lineA[i] - lineB[i];
    if(dif == 0){
      continue;
    }else{
      return (reverse * dif);
    }
  }

  return (lineAlength - lineBlength) * reverse;
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s [OPTIONS] FILE\n", progname);
    printf("Sort the lines of FILE and print them to STDOUT\n");
    printf("  -r    sort in reverse\n");
    printf("  -u    only print unique lines\n");
}

/*
 * main() - The main routine parses arguments and dispatches to the
 *          task-specific code.
 */
int main(int argc, char **argv) {
    /* for getopt */
    long opt;

    /* ensure the student name is filled out */
    check_student(argv[0]);

    /* parse the command-line options.  They are 'r' for reversing the */
    /* output, and 'u' for only printing unique strings.  'h' is also */
    /* supported. */
    /* TODO: parse the arguments correctly */
    int unique = 0;
    int reverse = 0;

    while ((opt = getopt(argc, argv, "huru:")) != -1) {
        switch(opt) {
          case 'h': help(argv[0]); break;
	case 'r': reverse = 1; break;
	case 'u': unique = 1; break;
	}
    }

    //printf("File: %s, argument %i\n",argv[argc-1], argc-1);
    
    /* TODO: fix this invocation */
    sort_file(argv[argc-1], unique, reverse);
}
