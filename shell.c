#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include "shell.h"

void clearScreen(){
    printf("\033[H\033[J");
}

void startProgram(){
    struct utsname systemInfo;
    clearScreen();
    char *username =(malloc(1024*sizeof(char)));
    if(username == NULL){
        fprintf(stderr, "Insufficient memory!\n");
    }
    username = getenv("USER");
    printf("Welcome to the Shell!\n");
    if(uname(&systemInfo)!= 0){
        fprintf(stderr, "Error: cannot get system information!\n");
    }
    printf("%s@%s: ", username, systemInfo.nodename);
}

int readCommandLine(char* input){
    char* inputBuffer;
    inputBuffer = readline("% ");
    if(strlen(inputBuffer) != 0){
        add_history(inputBuffer);
        strcpy(input, inputBuffer);
        return 0;
    }
    else{
        printf("No command provided\n");
        return -1;
    }
}

int parseInput(char *input, char** parsedInput){
    if(strlen(input) == 0){
        printf("Command not found\n");
        return -1;
    }
    for(int i = 0; i < sizeof(input); i++){
        parsedInput[i] = strsep(&input, " ");
        if(parsedInput[i] == NULL){
            break;
        }
        if(strlen(parsedInput[i]) == 0){
            i--;
        }
    }
    return 0;
}

void printDirectoryPath(){
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) == NULL){
        fprintf(stderr, "Cannot retrieve currrent directory path!\n");
    }
    printf("%s\n", cwd);
}

void printDirectoryContents(){
    struct dirent *dirContent;
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) == NULL){
        fprintf(stderr, "Cannot retrieve currrent directory path!\n");
    }

    DIR *directory = opendir(cwd);
    if(directory == NULL){
        fprintf(stderr, "Cannot open current directory path\n");
    }

    while((dirContent = readdir(directory))){
        if((strcmp(dirContent->d_name, ".") == 0) || (strcmp(dirContent->d_name, "..") == 0)){
            continue;
        }
        else{
            printf("%s\n", dirContent->d_name);
        }
    }
    closedir(directory);
}

int changeDirectories(char *input){
    char** parsedBuffer = malloc(1024*sizeof(char));
    if(parsedBuffer == NULL){
        fprintf(stderr, "Insufficient memory!\n");
        return -1;
    }
    if(parseInput(input, parsedBuffer) == -1){
        fprintf(stderr, "Could not process command\n");
        return -1;
    }
    if(chdir(parsedBuffer[1]) == -1){
        fprintf(stderr, "Could not change directories!\n");
        return -1;
    }
    printf("Current working directory: ");
    printDirectoryPath();
    free(parsedBuffer);
    return 0;
}

int makeDirectory(char *input){
    char** parsedBuffer = malloc(1024*sizeof(char));
    if(parsedBuffer == NULL){
        fprintf(stderr, "Insufficient memory!\n");
        return -1;
    }
    if(parseInput(input, parsedBuffer) == -1){
        fprintf(stderr, "Could not process command\n");
        return -1;
    }
    if(mkdir(parsedBuffer[1], 0777) == -1){
        fprintf(stderr, "Could not make directory in specified path\n");
        return -1;
    }
    printf("Successfully made directory! Located at: ");
    printDirectoryPath();
    free(parsedBuffer);
    return 0;
}

int removeDirectory(char *input){
    char** parsedBuffer = malloc(1024*sizeof(char*));
    if(parsedBuffer == NULL){
        fprintf(stderr, "Insufficient memory!\n");
        return -1;
    }
    if(parseInput(input, parsedBuffer) == -1){
        fprintf(stderr, "Could not process command\n");
        return -1;
    }
    if(rmdir(parsedBuffer[1]) == -1){
        fprintf(stderr, "Cannot remove specified directory");
        return -1;
    }
    printf("Successfully removed directory: %s", parsedBuffer[1]);
    free(parsedBuffer);
    return 0;
}









