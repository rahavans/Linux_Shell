#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>
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
int removeDirectoryContents(char *input); // rm -r
int moveDirectory(char* source, char* destination); // mvdir (CUSTOM COMMAND)
int copyFile(char *source, char *destination); // cp (FILES ONLY)
int renameFile(char *source, char* destination); // mv (FILES ONLY)
int deleteFile(char *input); // rm (FILES ONLY)
int changeFileorDirectoryPermissions(char *permission, char *input); // chmod
int changeFileorDirectoryOwnership(char* user, char* group, char *input); // chown
void displayFileContents(char *filepath); // cat
void displayFirstFewLines(char *filepath); // head
void displayLastFewLines(char *filepath); // tail
int killProcess(int pid); // kill
void displayUserName(); // whoami
void displaySystemInfo(); // uname
void displayCommandHistory(); // history
void exitShell(); // exit

#endif