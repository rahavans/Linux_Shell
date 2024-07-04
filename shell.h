#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>

void startProgram();
void clearScreen();
void parseInput(char* input, char** parsedInput);
int readCommandLine(char* input);
void printDirectoryPath();
void printDirectoryContents();
void changeDirectories(char *input);


#endif