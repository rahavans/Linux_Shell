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
void clearScreen(); // clear
int parseInput(char* input, char** parsedInput);
int readCommandLine(char* input);
void printDirectoryPath(); // pwd
void printDirectoryContents(); // ls
int changeDirectories(char *input); // cd
int makeDirectory(char *input); // mkdir
int removeDirectory(char *input); // rmdir
int copyFiles(char *source, char *destination); // cp (FILES ONLY)
int moveFiles(char *source, char *destination); // mv (FILES ONLY)




#endif