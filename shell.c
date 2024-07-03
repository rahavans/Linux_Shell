#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "shell.h"

void clearScreen(){
    printf("\033[H\033[J");
}

void startProgram(){
    clearScreen();
    char *username =(char*)(malloc(256*sizeof(char)));
    char *hostname = (char*)(malloc(256*sizeof(char)));
    username = getenv("USER");
    printf("Welcome to the Shell!\n");
    if(gethostname(hostname, sizeof(hostname)) != 0){
        fprintf(stderr, "Error: cannot get host name!");
    }
    printf("%s@%s: ", username, hostname);
}





