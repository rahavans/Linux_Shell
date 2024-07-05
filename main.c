#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

int main(){
  char *inputBuffer = malloc(1024*sizeof(char));
  char **parsedInputBuffer = malloc(1024*sizeof(char*));
  if(inputBuffer == NULL){
    fprintf(stderr, "Insufficient memory!");
  }
  clearScreen();
  startProgram();
  readCommandLine(inputBuffer);
  while(1){
    parseInput(inputBuffer, parsedInputBuffer);
    if(strcmp(parsedInputBuffer[0], "cd") == 0){
      changeDirectories(parsedInputBuffer[1]);
    }
    else if(strcmp(parsedInputBuffer[0], "ls") == 0){
      printDirectoryContents();
    }
    else if(strcmp(parsedInputBuffer[0], "pwd") == 0){
      printDirectoryPath();
    }
    else if(strcmp(parsedInputBuffer[0], "rmdir") == 0){
      removeDirectory(parsedInputBuffer[1]);
    }
    else if(strcmp(parsedInputBuffer[0], "mkdir") == 0){
      makeDirectory(parsedInputBuffer[1]);
    }
    else if(strcmp(parsedInputBuffer[0], "cp") == 0){
      copyFile(parsedInputBuffer[1], parsedInputBuffer[2]);
    }
    else if(strcmp(parsedInputBuffer[0], "rm") == 0){
      deleteFile(parsedInputBuffer[1]);
    }
    else if(strcmp(parsedInputBuffer[0], "cat") == 0){
      displayFileContents(parsedInputBuffer[1]);
    }
    else if(strcmp(parsedInputBuffer[0], "head") == 0){
      displayFirstFewLines(parsedInputBuffer[1]);
    }
    else if(strcmp(parsedInputBuffer[0], "clear") == 0){
      clearScreen();
    }
    readCommandLine(inputBuffer);
  }
  return 0;
}