#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "support.h"

int isDelim(int character, int *lines){
  if(character == ' '){
    return 1;
  }else if(character == '\n'){
    *lines = *lines + 1;//?
    return 1;
  }else if(character == '\t'){
    return 1;
  }
  return 0;
}


/*
 * wc_file() - count characters, words, and lines
 */
void wc_file(char *filename) {
    /* TODO: Complete this function */
  FILE *file = fopen(filename, "r");
  int curChar;

  //null check for the file
  if(!file){
    return;
  }

  int lines = 0;
  int words = 0;
  int characters = 0;
  while((curChar = fgetc(file)) != EOF){
    int validWord = 0;
    //will read a single word
    while((curChar != EOF) && !isDelim(curChar, &lines)){
      //need to check for valid word character
      if(isalnum(curChar)){
	validWord = 1;
      }
      curChar = fgetc(file);
      characters++;
    }
    if(curChar != EOF){
      curChar = fgetc(file);
      characters++;
    }
   
    //checks if a word was found
    if(validWord){
      words++;
    }

    //will eat up repeated deliminators
    while((curChar != EOF) && isDelim(curChar, &lines)){
      curChar = fgetc(file);
      characters++;
    }
    characters++;
  }
  characters--; //accounts for the end of file character
  //prints the output
  printf("%i %i %i %s\n", lines, words, characters, filename);
  fclose(file);
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s [FILE]\n", progname);
    printf("Print newline, word, and byte counts for FILE\n");
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

    /* error if we don't have a file, else call wc_file */
    if (argc != 2) {
        printf("Error: no file given\n");
        exit(1);
    }
    wc_file(argv[1]);
}
