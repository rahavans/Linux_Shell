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
#include "shell.h"

void clearScreen(){
    printf("\033[H\033[J");
}

void startProgram(){
    clearScreen();
    printf("Welcome to the Shell!\n");
    using_history();
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
        return;
    }
    DIR *directory = opendir(cwd);
    if(directory == NULL){
        fprintf(stderr, "Cannot open current directory path\n");
        return;
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
    printf("Successfully removed directory: %s\n", input);
    return 0;
}

int removeDirectoryContents(char *input){
    DIR* directory = opendir(input);
    if(directory == NULL){
        fprintf(stderr, "Cannot open current directory path\n");
        return -1;
    }
    struct dirent* dirContent;
    char filePath[1024];
    while ((dirContent = readdir(directory)) != NULL){
        if((strcmp(dirContent->d_name, ".") == 0) || (strcmp(dirContent->d_name, "..") == 0)){
            continue;
        }
        snprintf(filePath, sizeof(filePath), "%s/%s", input, dirContent->d_name);
        struct stat fileInfo;
        if(stat(filePath, &fileInfo) == -1){
            fprintf(stderr, "Could not create stat struct\n");
            closedir(directory);
            return -1;
        }
        if(S_ISDIR(fileInfo.st_mode)){
            if(removeDirectoryContents(filePath) == -1){
            closedir(directory);
            return -1;
            }
        }
        else{
            if(deleteFile(filePath) == -1){
                fprintf(stderr, "Could not delete file\n");
                closedir(directory);
                return -1;
                }
            }
        }
    closedir(directory);
    if(removeDirectory(input) == -1){
        fprintf(stderr, "Could not delete now empty directory\n");
        return -1;
    }
    printf("Successfully deleted directory at: %s\n", input);
    return 0;
}

int moveDirectory(char* source, char* destination){
    char* directoryName = strrchr(source, '/');
    if (directoryName != NULL) {
        directoryName++;
    } 
    else{
        directoryName = source;
    }
    strcat(destination, "/");
    strcat(destination, directoryName);

    if(rename(source, destination) != 0){
        fprintf(stderr, "Could not move file to specified destination\n");
        return -1;
    }
    printf("Successfully moved directory %s to %s\n", source, destination);
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

int renameFile(char *source, char *destination){
    char* fileName = strrchr(source, '/');
    if (fileName != NULL) {
        fileName++;
    } 
    else{
        fileName = source;
    }
    strcat(destination, "/");
    strcat(destination, fileName);

    if(rename(source, destination) != 0){
        fprintf(stderr, "Could not move file to specified destination\n");
        return -1;
    }
    printf("Successfully moved %s to %s\n", source, destination);
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
    if(fp == NULL){
        fprintf(stderr, "Error opening file\n");
        return;
    }
    char buffer[1024];
    size_t bytesRead;
    while(((bytesRead = fread(buffer, 1, 1024, fp)) > 0)){
        fwrite(buffer, 1, bytesRead, stdout);
    }
    fclose(fp);
}

void displayFirstFewLines(char *filepath){
    FILE *fp = fopen(filepath, "r");
    if(fp == NULL){
        fprintf(stderr, "Error opening file\n");
        return;
    }
    char buffer[1024];
    size_t bytesRead;
    int lines = 4;
    int count = 0;
    while(lines > count && fgets(buffer, sizeof(buffer), fp) != NULL){
        if(fputs(buffer, stdout) == EOF){
            fprintf(stderr, "Error printing file content to console");
            break;
        }
        count++;
    }
    printf("\n");
    fclose(fp);
}

void displayLastFewLines(char *filepath){
    FILE *fp = fopen(filepath, "r");
    if(fp == NULL){
        fprintf(stderr, "Error opening file\n");
        return;
    }
    char linesRead[4][1024];
    int lineCount = 0;
    while(fgets(linesRead[lineCount % 4], 1024, fp) != NULL){
        lineCount++;
    }
    int start = lineCount > 4 ? lineCount % 4 : 0;
    int count = lineCount < 4 ? lineCount : 4;
    for(int i = 0; i < count; i++){
        fputs(linesRead[(start + i) % 4], stdout);
    }
    printf("\n");
}

void displayUserName(){
    char username[1024];
    char* userEnv = getenv("USER");
    if(userEnv == NULL){
        fprintf(stderr, "Error finding username\n");
        return;
    }
    strcpy(username, userEnv);
    printf("%s\n", username);
}

void displaySystemInfo(){
    struct utsname systemInfo;
    if(uname(&systemInfo) == -1){
        fprintf(stderr, "Cannpot retrieve system information\n");
        return;
    }
    printf("%s\n", systemInfo.sysname);
}

int killProcess(int pid){
    if(kill(pid, SIGKILL) == -1){
        fprintf(stderr, "Error killing process\n");
        return -1;
    }
    printf("Killed process: %d\n", pid);
    return 0;
}

void displayCommandHistory(){
    HIST_ENTRY *commandHistory;
    int i = 1;
    while((commandHistory = history_get(i)) != NULL){
        printf("%s\n", commandHistory->line);
        i++;
    }
}

int changeFileorDirectoryPerms(int perm, char* input){}

int changeFileorDirectoryOwnership(char *filePath, int user, int group){}

void exitShell(){
    exit(1);
}