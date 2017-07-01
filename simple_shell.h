///\file simple_shell.h
///\brief Header file of our Simple Shell
///
#ifndef _SIMPLE_SHELL_LIBRARY_H_
#define _SIMPLE_SHELL_LIBRARY_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <assert.h>


#define G_MAX_LENGTH 1000

extern unsigned int G_STARTED; /**< unsigned int value that checks if the user started the program, is typing commands or wants to close it. */  
extern char tcp[];/**< Find out yourself. */  

struct Files{
    char name[G_MAX_LENGTH]; /**< char value that stores the name of our file. */  
    float size; /**< float value that stores the size of our file. */  
    unsigned int number_of_lines; /**< unsigned int value that stores the number of lines from a file. */  
    unsigned int number_of_words;  /**< unsigned int value that stores the number of words from a file. */  
    struct Files *nextFile;  /**< struct value that stores the memory address of our next file. */  
};


void read_directory(struct Files *currentDirectory); //!< Function from reading the files from the current directory.
void read_file(struct Files *currentFile, char file[G_MAX_LENGTH]); //!< Function that reads the file.
void check_file(struct Files *currentFile, char file_to_check[G_MAX_LENGTH]); //!< Function that checks if a file exists.
void show_content(struct Files *currentFile, char file_to_show[G_MAX_LENGTH]); //!< Function that shows content of a file.
void create_file(struct Files *currentFile, char file_to_create[G_MAX_LENGTH]); //!< Function that creates a file.
void delete_file(struct Files *currentFile, char file_to_delete[G_MAX_LENGTH]); //!< Function that deletes a file.
void shell_command(struct Files *currentDirectory, char content[G_MAX_LENGTH]); //!< Function that is reading our input from console.

#endif