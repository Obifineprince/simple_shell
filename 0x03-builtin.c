#include "shell.h"

/**
 * builtins_list - Searches for a match and executes the
 * associated built-in command.
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
	int cursor;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

/* Traverse the structure */
	for (cursor = 0; options[cursor].builtin != NULL; cursor++)
	{
/* In case of a match between the provided command and a built-in function */
		if (str_compare(options[cursor].builtin, input->command_name, 0))
		{
/* Execute the associated function and return its return value */
			return (options[cursor].function(input));
		}
/* Return -1 if there is no match */
	}
	return (-1);
}
