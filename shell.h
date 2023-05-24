#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

#include "macros.h"

/* Forward declaration of shell_program structure */
typedef struct shell_program {
    char *program_name;
    char *input_line;
    char *command_name;
    int exec_counter;
    int file_descriptor;
    char **tokens;
    char **env;
    char **alias_list;
} shell_program;

typedef struct builtins {
    char *builtin;
    int (*function)(shell_program *input);
} builtins;

void inicialize_data(shell_program *input, int argc, char *argv[], char **env);
void process_input(char *prompt, shell_program *input);
void handle_ctrl_c(int opr UNUSED);
int main(int argc, char *argv[], char *env[]);

int _getline(shell_program *input);
int check_logic_ops(char *array_commands[], int i, char array_operators[]);

void variables_expansion(shell_program *input);
void alias_expansion(shell_program *input);
int buffer_add(char *buffer, char *str_to_add);

void tokenize(shell_program *input);
char *_strtok(char *line, char *delim);

int execute(shell_program *input);

int builtins_list(shell_program *input);

int  check_file(char *full_path);
char **tokenize_path(shell_program *input);
int seek_program(shell_program *input);

void free_array_of_pointers(char **directory);
void free_recurrent_data(shell_program *input);
void free_all_data(shell_program *input);

int builtin_exit(shell_program *input);
int builtin_cd(shell_program *input);
int set_work_directory(shell_program *input, char *new_dir);
int builtin_help(shell_program *input);
int builtin_alias(shell_program *input);

int builtin_env(shell_program *input);
int builtin_set_env(shell_program *input);
int builtin_unset_env(shell_program *input);

char *env_get_key(char *name, shell_program *input);
int env_set_key(char *key, char *value, shell_program *input);
int env_remove_key(char *key, shell_program *input);
void print_environ(shell_program *input);

int _print(char *string);
int _printe(char *string);
int _print_error(int errorcode, shell_program *input);

int str_length(char *string);
char *str_duplicate(char *string);
int str_compare(char *string1, char *string2, int number);
char *str_concatenate(char *string1, char *string2);
void str_reverse(char *string);

void long_to_string(long number, char *string, int base);
int _atoi(char *s);
int count_characters(char *string, char *character);

int print_func_alias(shell_program *input, char *alias);
char *get_func_alias(shell_program *input, char *name);
int set_func_alias(char *alias_string, shell_program *input);

int interactive(shell_program *info);
int _delim(char c, char *delim);
int _alpha(int c);

#endif /* SHELL_H */

