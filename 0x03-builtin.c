#include "shell.h"

/**
 * builtins_list - Searches for a match and executes the
 * associated built-in command in the shell.
 * @input: Pointer to the struct containing the program's data.
 *
 * This function searches for a match between the command
 * entered by the user and the available built-in commands.
 * If a match is found, it executes the associated built-in command
 * and returns the return value of the executed command.
 * If no match is found, it returns -1.
 *
 * Return: The return value of the executed built-in command
 *  if there is a match,
 * otherwise -1.
 **/
int builtins_list(shell_program *input)
{
	int iterator;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
/*		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},*/
		{NULL, NULL}
	};

/*walk through the structure*/
	for (iterator = 0; options[iterator].builtin != NULL; iterator++)
	{
/*if there is a match between the given command and a builtin,*/
		if (str_compare(options[iterator].builtin, input->command_name, 0))
		{
/*execute the function, and return the return value of the function*/
			return (options[iterator].function(input));
		}
/*if there is no match return -1 */
	}
	return (-1);
}
