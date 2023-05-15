#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* header for printf*/
#include <unistd.h> /* header for execve*/
#include <stdlib.h>
#include <string.h> /* header for  strtok*/
#include <stddef.h>
#include <errno.h> /* header for errno and perror */
#include <sys/types.h> /* header for pid */
#include <sys/wait.h> /* header for wait */
#include <sys/stat.h> /*header  for use of stat function */
#include <signal.h> /*  header for signal management */
#include <fcntl.h> /*header  for open files*/

/************* MACROS **************/

#include "macros.h" /* for msg help and prompt */

/************* STRUCTURES **************/

/**
 * struct info - Structure for program data
 * @program_name: Name of the executable
 * @input_line: Pointer to input read by _getline
 * @command_name: Pointer to first user-typed command
 * @exec_counter: Number of executed commands
 * @file_descriptor: File descriptor for command input
 * @tokens: Pointer to array of tokenized input
 * @env: Copy of the environ variable
 * @alias_list: Array of pointers to aliases
 * Description: The `info` struct holds various data related to the program's execution and user input.
 * `program_name` stores the name of the executable program.
 * `input_line` is a pointer to the input read by the `_getline` function.
 * `command_name` is a pointer to the first command typed by the user.
 * `exec_counter` keeps track of the number of executed commands.
 * `file_descriptor` is the file descriptor for the input of commands.
 * `tokens` is a pointer to an array of tokenized input.
 * `env` is a copy of the `environ` environment variable.
 * `alias_list` is an array of pointers that holds aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;

} shell_program;
/**
 * struct builtins - Structure for built-in commands
 * @builtin: Name of the built-in command
 * @function: Associated function to be called for each built-in command
 *
 * Description: The `builtins` struct is used to define and store information about built-in commands.
 * The `builtin` member represents the name of the built-in command.
 * The `function` member holds the associated function that should be called for each specific built-in command.
 */

typedef struct builtins
{
	char *builtin;
	int (*function)(shell_program *input);
} builtins;


/************* MAIN FUNCTIONS *************/


/*========  shell.c  ========*/

/* Initialize the struct with program information. */
void inicialize_data(shell_program *input, int arc, char *argv[], char **env);

/* Create an infinite loop that displays the prompt repeatedly.*/
void sisifo(char *prompt, shell_program *input);

/* print the prompt and start a new line */
void handle_ctrl_c(int opr UNUSED);


/*========  _getline.c  ========*/

/* Read a single line from standard input.t*/
int _getline(shell_program *input);

/*Separate each line by logical operators, if they exist */
int check_logic_ops(char *array_commands[], int i, char array_operators[]);


/*======== expansions.c function ========*/

/* resolve  variables */
void expand_variables(shell_program *input);

/* resolve alias */
void expand_alias(shell_program *input);

/*"Add the string to the end of the buffer"*/
int buffer_add(char *buffer, char *str_to_add);


/*======== str_tok.c ========*/

/* Split the string into tokens using a specified delimiter*/
void tokenize(shell__program *input);

/* function creates a pointer to a string */
char *_strtok(char *line, char *delim);


/*======== execute.c  function ========*/

/* function Executes a command with its entire path */
int execute(shell_program *input);


/*======== builtins_list.c ========*/

/* function identifies builtin match and , executes it */
int builtins_list(shell_program *input);


/*======== find_in_path.c ========*/

/* function that Creates an array of the path directories */
char **tokenize_path(shell_program *input);

/*function to source for program in path */
int find_program(shell_program *input);


/************** Help to check memory leak **************/


/*======== helpers_free.c ========*/

/* function to Free  memory for DIR */
void free_array_of_pointers(char **directories);

/*function to Free the fields needed for each loop */
void free_recurrent_data(shell_program *input);

/* function to Free the field for data */
void free_all_data(shell_program *input);


/************** BUILTINS **************/


/*======== builtins_more.c functions  ========*/

/* exit function for the shell */
int builtin_exit(shell_program *input);

/* function for changing  current directory */
int builtin_cd(shell_program *input);

/* function to set the working  directory */
int set_work_directory(shell_program *input, char *new_dir);

/* function to show help information */
int builtin_help(shell_program *input);

/* function for set, unset and showing  alias */
int builtin_alias(shell_program *input);


/*======== builtins_env.c functions  ========*/

/* function displays the shell environ */
int builtin_env(shell_program *input);

/*  function creates or override the  variable of environ */
int builtin_set_env(shell_program *input);

/* function deletes the  variable of environ */
int builtin_unset_env(shell_program *input);


/************** HELP FOR ENVIRON_VARIABLES MANAGEMENT **************/


/*======== env_management.c functions  ========*/

/* function retrieves the value of an environ_variable */
char *env_get_key(char *name, shell_program *input);

/* function overrides the value of the environ_variable */
int env_set_key(char *key, char *value, shell_program *input);

/* function removes key from the environ */
int env_remove_key(char *key, shell_program *input);

/* function prints current environ */
void print_environ(shell_program *input);


/************** HELP_FOR_PRINTING**************/


/*======== help_print.c ========*/

/* function prints string to the standard output */
int _print(char *string);

/* function prints string to the  standard error */
int _printe(char *string);

/* function prints string to the  standard error */
int _print_error(int errorcode,shell_program *input);


/************** help for string management **************/


/*======== helpers_string.c ========*/

/* function counts  num of char of a string */
int str_length(char *string);

/* function duplicates a string */
char *str_duplicate(char *string);

/* function compares  strings */
int str_compare(char *string1, char *string2, int number);

/* function concatenates 2 strings */
char *str_concat(char *string1, char *string2);

/* function reverses a string  */
void str_reverse(char *string);


/*==helpers_num.c==*/

/* function cast int form string  */
void long_to_string(long number, char *string, int base);

/* conversion of string to num */
int _atoi(char *s);

/* identify and count the num of coincidence in string char */
int count_characters(char *string, char *character);


/*==aliac.c functions==*/

/* function prints alias list */
int print_alias(shell_program *input, char *alias);

/* function provide alias  */
char *get_alias(shell_program *input, char *alias);

/* function to set alias name  */
int set_alias(char *alias_string, shell_program *input);


#endif /* SHELL_H  project*/
