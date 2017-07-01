#include "simple_shell.h" ///> contains all functions, e.g. read(), show(), shell_commands()

int main(){

    struct Files *currentDirectory = malloc(sizeof(struct Files));
    currentDirectory->nextFile = NULL;
    char command[G_MAX_LENGTH];

    while(G_STARTED != 3){
        if(G_STARTED == 2){
            printf("\nWrite your command: ");
            fgets(command, sizeof(command), stdin);
            shell_command(currentDirectory, command);
        }
        if(G_STARTED == 1){
            printf("\nType \"start\", without quotes for program to start: ");
            fgets(command, sizeof(command), stdin);
            if(strcmp(command, "start\n") == 0){
                read_directory(currentDirectory);
                printf("\nAll files from current directory have been successfully read.");
                G_STARTED = 2;
            } else {
                printf("\nInvalid command. Program needs to be started first.");
            }
        }
    }
}
