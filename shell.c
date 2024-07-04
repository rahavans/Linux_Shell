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
#include "shell.h"

void clearScreen(){
    printf("\033[H\033[J");
}

void startProgram(){
    struct utsname systemInfo;
    clearScreen();
    char *username =(char*)(malloc(1024*sizeof(char)));
    username = getenv("USER");
    printf("Welcome to the Shell!\n");
    if(uname(&systemInfo)!= 0){
        fprintf(stderr, "Error: cannot get system information!");
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
        free(inputBuffer);
        return 1;
    }
}

void parseInput(char *input, char** parsedInput){
    if(strlen(input) == 0){
        printf("Command not found");
    }
    for(int i = 0; i < strlen(input); i++){
        parsedInput[i] = strsep(&input, " ");
        if(parsedInput[i] == NULL){
            break;
        }
    }
}

void printDirectoryPath(){
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) == NULL){
        fprintf(stderr, "Cannot retrieve currrent directory path!");
    }
    printf("%s\n", cwd);
}

void printDirectoryContents(){
    struct dirent *content;
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) == NULL){
        fprintf(stderr, "Cannot retrieve currrent directory path!");
    }
    DIR *directory = opendir(cwd);
    if(directory == NULL){
        fprintf(stderr, "Cannot open current directory path");
    }
    while((content = readdir(directory))){
        if((strcmp(content->d_name, ".") == 0) || (strcmp(content->d_name, "..") == 0)){
            continue;
        }
        else{
            printf("%s\n",content->d_name);
        }
    }
    closedir(directory);
}

void changeDirectories(char *input){
    char workBuf[1024];
    parseInput(input, workBuf);
    printf("%s\n",workBuf);
    //chdir(&(workBuf[1]));
}

void commandSupport(){
    printf("\nCommands supported by my Shell:"
    "\nls"
    "\ncd"
    "\npwd"
    "\nexit"
    "\ncode compilation"
    "\n"

    
    
    
    );
}




