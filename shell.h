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

void data_initialize(shell_program *input, int argc, char *argv[], char **env);
void process_input(char *prompt, shell_program *input);
void ctrl_c_handle(int opr);

int _getline(shell_program *input);
int check_logic(char *command_arrays[], int i, char opera_arr[]);

void expand_variables(shell_program *input);
void expand_alias(shell_program *input);
int buffer_add(char *buffer, char *str_to_add);

void custom_tokenize(shell_program *input);
char *_strtok(char *line, char *delim);
void **tokenize(shell_program *input);

int execute(shell_program *input);

int builtins_list(shell_program *input);

char **path(shell_program *input);
int seek_program(shell_program *input);

void free_pointers(char **directory);
void free_recurrent(shell_program *input);
void free_data(shell_program *input);

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
int _printerror(int error, shell_program *input);

int str_leng(char *str);
char *str_duplic(char *str);
int compare_str(char *str1, char *str2, int num_chars);
char *concat_str(char *str1, char *str2);
void rever_str(char *str);

void long_string(long numb, char *str, int base);
int _atoi(char *p);
int count_char(char *str, char *character);

int print_alias(shell_program *input, char *alias);
char *get_alias(shell_program *input, char *alias);
int set_alias(char *alias_string, shell_program *input);

int interactive(shell_program *info);
int _delim(char c, char *delim);
int _alpha(int c);

#endif /* SHELL_H */

