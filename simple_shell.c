///\file simple_shell.c
///\brief Here we can find the functions that we call in the main file.
#include "simple_shell.h"

unsigned int G_STARTED = 1; /**< unsigned int value that checks if the user started the program, is typing commands or wants to close it. */  
char aux_cp[] = "tcp"; /**< Find out yourself. */  

/*! \fn void read_directory(struct Files *currentDirectory)
    \brief Search in the current directory and saves all information about a file.
    \param currentDirectory is our linked list where we will save information about all files we find inside.
*/
void read_directory(struct Files *currentDirectory){

    struct Files *iterator = currentDirectory;

    DIR *dp;
    struct dirent *ep;
    dp = opendir ("./");

    if (dp != NULL){
        while (ep = readdir (dp)){
            if(strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0){
                while(iterator->nextFile != NULL)
                    iterator = iterator->nextFile;
                struct stat st;
                struct Files *newValue = malloc(sizeof(struct Files));
                stat(ep->d_name, &st);
                iterator->nextFile = newValue;
                strcpy(newValue->name, ep->d_name);
                newValue->size = st.st_size;
				newValue->number_of_lines = 0;
				newValue->number_of_words = 0;
                newValue->nextFile = NULL;
                read_file(currentDirectory, newValue->name);
            }

        }

        (void) closedir (dp);
    }
    else
    perror ("\nCouldn't open the directory");

    return;


}

/*! \fn void read_file(struct Files *currentFile, char file[G_MAX_LENGTH])
    \brief Reads a file and stores the content of the file.
    \param currentFile is our linked list where we saves the content of the file.
    \param file the name of the file we want to read.
*/
void read_file(struct Files *currentFile, char file[G_MAX_LENGTH]){

	struct Files *iterator = currentFile;
    unsigned int counter = 0;
    int i = 0;
    char ch;
	char aux[G_MAX_LENGTH];
    FILE *f = fopen(file, "r");
	FILE *g = fopen(file, "r");
	FILE *file_r = fopen(file, "r");

	while(iterator->nextFile != NULL){
		if(strcmp(iterator->nextFile->name, file) == 0)
			break;
		iterator = iterator->nextFile;
	}
	
    if (f == NULL)
    {
        printf("\nError opening file! Possibly directory.");
		return;
    }


    while (fscanf(file_r, " %999s", aux) != EOF) {
        counter++;
    }

	fclose(file_r);
	fclose(f);
    iterator->nextFile->number_of_words = counter;

    while(!feof(g)){
        ch = fgetc(g);
        if(ch == '\n'){
            iterator->nextFile->number_of_lines++;
        }
    }

    fclose(g); 
	return;
}

/*! \fn void check_file(struct Files *currentFile, char file_to_check[G_MAX_LENGTH])
    \brief Checks if a file exists, if yes print information about it.
    \param currentFile is our linked list where we search information about our file.
    \param file_to_check is the name of the file we want information for.
*/
void check_file(struct Files *currentFile, char file_to_check[G_MAX_LENGTH]){

    struct Files *iterator = currentFile;
    char aux[G_MAX_LENGTH];
    file_to_check[strcspn(file_to_check, "\n")] = 0;
    while(iterator->nextFile != NULL){
        if(strcmp(iterator->nextFile->name, file_to_check) == 0){
            printf("\nFile was found.\n");
            printf("\n----------------------------------------------------\n");
            printf("|%-20s|%-20s|%-10s|%-10s|\n", "Name", "Size", "Nr. words", "Nr. lines");
            printf("|%-20s|%-20.0f|%-10d|%-10d|", iterator->nextFile->name, iterator->nextFile->size, iterator->nextFile->number_of_words, iterator->nextFile->number_of_lines);
            printf("\n----------------------------------------------------\n");
            return;
        }
        iterator = iterator->nextFile;
    }

    if(iterator->nextFile == NULL)
        printf("\nFile was not found.\n");
    return;

}

/*! \fn void show_content(struct Files *currentFile, char file_to_show[G_MAX_LENGTH])
    \brief Shows the content of a file.
    \param currentFile is our linked list where we can find the content of our file.
    \param file_to_show is the name of the file we want to show content for.
*/
void show_content(struct Files *currentFile, char file_to_show[G_MAX_LENGTH]){

    struct Files *iterator = currentFile;
	unsigned int counter;
	char aux;
	file_to_show[strcspn(file_to_show, "\n")] = 0;
	FILE *f = fopen(file_to_show, "r");

    while(iterator->nextFile != NULL){
        if(strcmp(iterator->nextFile->name, file_to_show) == 0){
            printf("\nContent of your file: \n");
             while ((aux = getc(f)) != EOF)
				putchar(aux);
			fclose(f);
            printf("\n");
            return;
        }
        iterator = iterator->nextFile;
    }

    if(iterator->nextFile == NULL)
        printf("\nFile not found.\n");
    return;
}

/*! \fn void create_file(struct Files *currentFile, char file_to_create[G_MAX_LENGTH])
    \brief Checks if a file already exists, if not it will create it.
    \param currentFile is our linked list where we search if our given name for the name file already exists.
    \param file_to_create is the name of the file we want to create.
*/
void create_file(struct Files *currentFile, char file_to_create[G_MAX_LENGTH]){

    FILE *check_file = fopen(file_to_create, "r"), *new_file;
    file_to_create[strcspn(file_to_create, "\n")] = 0;
    
    struct Files *iterator = currentFile;

    if (check_file == NULL)
    {
        printf("\nFile does not exists, creating it.");
        new_file = fopen(file_to_create, "w");
        printf("\nFile \"%s\" was successfully created.\n", file_to_create);
        while(iterator->nextFile != NULL)
            iterator = iterator->nextFile;
        struct Files *newFile = malloc(sizeof(struct Files));
        iterator->nextFile = newFile;
        newFile->nextFile = NULL;
        newFile->number_of_lines = 0;
        newFile->number_of_words = 0;
        newFile->size = 0;
        strcpy(newFile->name, file_to_create);
        fclose(new_file);
        fclose(check_file);
        return;
    } else {
        printf("\nFile \"%s\" already exists.", file_to_create);
        return;
    }

}

/*! \fn void delete_file(struct File *currentFile, char file_to_delete[G_MAX_LENGTH])
    \brief Delete a given file from our directory.
    \param currentFile is our linked list where we can find all information about our file.
    \param file_to_delete is the name of the file we want to delete.
*/
void delete_file(struct Files *currentFile, char file_to_delete[G_MAX_LENGTH]){
    struct Files *iterator = currentFile;
    struct Files *delElement = malloc(sizeof(struct Files));
    file_to_delete[strcspn(file_to_delete, "\n")] = 0;
    unsigned int status;

    while(iterator->nextFile != NULL){
        if(strcmp(iterator->nextFile->name, file_to_delete) == 0){
            delElement = iterator->nextFile;
            iterator->nextFile = iterator->nextFile->nextFile;
            free(delElement);
            status = remove(file_to_delete);
            if( status == 0 ){
              printf("%s file deleted successfully.\n", file_to_delete);
            } else {
              printf("\nUnable to delete the file.");
              perror("\nError.\n");
            }

            return;
        }
        iterator = iterator->nextFile;
    }

    if(iterator->nextFile == NULL)
        printf("\nFile not found.\n");
    return;

}

/*! \fn void shell_command(struct Files *currentDirectory, char content[G_MAX_LENGTH])
    \brief After users enters a command it checks if the command is valid and execute it.
    \param currentDirectory is our linked list that we use to show, delete, store, create new files.
    \param content is the input string from our user.
*/
void shell_command(struct Files *currentDirectory, char content[G_MAX_LENGTH]){

    struct Files *iterator = currentDirectory;
    char aux[G_MAX_LENGTH];
    content[strcspn(content, "\n")] = 0;

    if(strcmp(content, "ls") == 0 || strcmp(content, "ls *") == 0){
        printf("\nFiles from current directory are: ");
        while(iterator->nextFile != NULL){
            printf("%s ", iterator->nextFile->name);
            iterator = iterator->nextFile;
        }
        return;
    }

    if(strcmp(content, "ls -l") == 0){
        printf("\n----------------------------------------------------\n");
        printf("|%-20s|%-20s|%-10s|%-10s|\n", "Name", "Size", "Nr. words", "Nr. lines");
        while(iterator->nextFile != NULL){
            printf("|%-20s|%-20.0f|%-10d|%-10d|", iterator->nextFile->name, iterator->nextFile->size, iterator->nextFile->number_of_words, iterator->nextFile->number_of_lines);
            iterator = iterator->nextFile;
            printf("\n");
        }
        printf("----------------------------------------------------\n");
        return;
    }

    if(strcmp(content, "makefile") == 0){
        printf("\nName the file you want to create: ");
        fgets(aux, sizeof(aux), stdin);
        create_file(currentDirectory, aux);
        return;
    }

    if(strcmp(content, "check") == 0){
        printf("\nWhich file do you want to check if exists in current read directory: ");
        fgets(aux, sizeof(aux), stdin);
        check_file(currentDirectory, aux);
        return;
    }

    if(strcmp(content, "cat") == 0 || strcmp(content, "content") == 0){
        printf("\nFrom which file do you want to check the content: ");
        fgets(aux, sizeof(aux), stdin);
        show_content(currentDirectory, aux);
        return;
    }

    if(strcmp(content, "delete") == 0){
        printf("\nWhich file do you want to delete: ");
        fgets(aux, sizeof(aux), stdin);
        delete_file(currentDirectory, aux);
        return;
    }



    if(strcmp(content, "copyright") == 0){
        printf("%cSirbu Jeanina-Maria %c 2017", 169, 64);
        return;
    }

    if(strcmp(content, "exit") == 0){
        G_STARTED = 3;
        return;
    }

    if(strcmp(content, "?") == 0 || strcmp(content, "/?") == 0 || strcmp(content, "help") == 0){
        printf("\nAvailable commands");
        printf("\nListing: ls, ls *, ls -l");
        printf("\nCreate: makefile");
        printf("\nChecking: check");
        printf("\nContent: content");
        printf("\nDeleting: delete");
        printf("\nInfo: copyright");
        printf("\nStop the program: exit");
        return;
    }

    if(strcmp(content, aux_cp) == 0){printf("\n%c%c%c%c%c%c", 77,46,65,46,71,46); return;}

    printf("\nInvalid command. For all commands available type \"help\".");
    return;


}