#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "support.h"

/*
 * sed_file() - modify lines of filename based on pattern, and print result
 *              to STDOUT
 */

char* searchAndDestroy(char * line, char * target, char * replacement, int found){
  char * startReplace = strstr(line, target);
  if(startReplace != NULL){
    int targetIndex = (startReplace - line);
    
    *startReplace = '\0';
    printf("%s", line);
   
    printf("%s", replacement);
    int targetLength = strlen(target);
    
    return (line + (targetIndex + targetLength));
  }else{
    if(found){
      printf("%s", line);
    }
    return NULL;
  }
}

void sed_file(char *filename, char *pattern) {
    /* TODO: Complete this function */

  FILE *file = fopen(filename, "r");
  if(!file){
    return;
  }

  char * target = pattern;
  char * replacement = "TODO";
  
  int i = 0;
  char * curTok = strtok(pattern, "/");
  while(curTok != NULL){
      switch(i){
      case 0:
	if(*curTok != 's'){
	  //Problem
	  printf("Expected s found %s\n", curTok);
	  return;
	}
	break;
      case 1:
	target = curTok;
	break;
      case 2:
	replacement = curTok;
	break;
      case 3:
	if(*curTok != 'g'){
	  //Problem
	  printf("Expected g found %s\n", curTok);
	  return;
	}
	break;
      default:
	printf("Token %s not recognized\n", curTok);
	return;
      }
      curTok = strtok(NULL, "/");
      i++;
    }
  
  char line[1024];
  while(fgets(line, 1024, file)){
    char * remaining = line;
    int found = 0;
    while((remaining = searchAndDestroy(remaining, target, replacement, found)) != NULL){
      found = 1;
    }
  }
  fclose(file);
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s [FILE]\n", progname);
    printf("Print the contents of FILE to STDOUT\n");
    printf("With no FILE, read standard input\n");
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

    /* TODO: fix this invocation */
    sed_file(argv[1], argv[2]);
}
