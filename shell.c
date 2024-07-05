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
    for (int i = 0; i < 1024; i++) { 
        parsedInput[i] = strsep(&input, " "); 
  
        if (parsedInput[i] == NULL) 
            break; 
        if (strlen(parsedInput[i]) == 0) 
            i--; 
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
    if(chdir(input) == -1){
        fprintf(stderr, "Could not change directories!\n");
        return -1;
    }
    printf("Current working directory: ");
    printDirectoryPath();
    return 0;
}

int makeDirectory(char *input){
    if(mkdir(input, 0777) == -1){
        fprintf(stderr, "Could not make directory in specified path\n");
        return -1;
    }
    printf("Successfully made directory! Located at: ");
    printDirectoryPath();
    return 0;
}

int removeDirectory(char *input){
    if(rmdir(input) == -1){
        fprintf(stderr, "Cannot remove specified directory\n");
        return -1;
    }
    printf("Successfully removed directory: %s", input);
    return 0;
}

int copyFile(char *source, char *destination){
    FILE *sourceFile = fopen(source, "r");
    FILE *destinationFile = fopen(destination, "w");
    if(sourceFile == NULL || destinationFile == NULL){
        fprintf(stderr, "Error opening source or destination file\n");
        return -1;
    }
    char buffer[1024];
    size_t bytesRead;

    while(((bytesRead = fread(buffer, 1, 1024, sourceFile)) > 0)){
        if(fwrite(buffer, 1, bytesRead, destinationFile) != bytesRead){
            fprintf(stderr, "Error writing to destination file/n");
            fclose(sourceFile);
            fclose(destinationFile);
            return -1;
        }
    }

    if(ferror(sourceFile)){
        fprintf(stderr, "Error reading from source file after copying destination file\n");
        return -1;
    }

    fclose(sourceFile);
    fclose(destinationFile);
    printf("Successfully copied from %s to %s\n", source, destination);
    return 0;
}

int deleteFile(char *input){
    if(remove(input) != 0){
        fprintf(stderr, "Cannot delete file from directory\n");
        return -1;
    }
    printf("Successfully deleted %s\n", input);
    return 0;
}

void displayFileContents(char *filepath){
    FILE *fp = fopen(filepath, "r");
    char buffer[1024];
    size_t bytesRead;

    while(((bytesRead = fread(buffer, 1, 1024, fp)) > 0)){
        fwrite(buffer, 1, bytesRead, stdout);
    }
    fclose(fp);
}

void displayFirstFewLines(char *filepath){
    FILE *fp = fopen(filepath, "r");
    char buffer[1024];
    size_t bytesRead;
    int lines = 4;
    int count = 0;

    while(lines > count && fgets(buffer, sizeof(buffer), fp) != NULL){
        fputs(buffer, stdout);
        count++;
    }
    
    fclose(fp);
}