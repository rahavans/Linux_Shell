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
    else if(strcmp(parsedInputBuffer[0], "cp") == 0){
      copyFiles(parsedInputBuffer[1], parsedInputBuffer[2]);
    }
    readCommandLine(inputBuffer);
  }
  return 0;
}