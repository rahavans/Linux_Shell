#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

int main(){
  char *inputBuffer = malloc(1024*sizeof(char));
  if(inputBuffer == NULL){
    fprintf(stderr, "Insufficient memory!");
  }
  clearScreen();
  startProgram();
  readCommandLine(inputBuffer);
  while(1){
    makeDirectory(inputBuffer);
    readCommandLine(inputBuffer);
  }
  return 0;
}