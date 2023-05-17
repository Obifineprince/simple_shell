#include "shell.h"
/**
 * builtin_env - displays the environment in which the shell is running
 * @input: struct containing program's data
 * Return: zero if successful, or non-zero if specified in the arguments
 */

int builtin_env(shell_program *input)
{
	int j;
	char spname[50] = {'\0'};
	char *var_copy = NULL;

	/* if not arguments */
	if (input->tokens[1] == NULL)
		print_environ(input);
	else
	{
		for (j = 0; input->tokens[1][j]; j++)
		{/* Checks if a character '=' exists */
			if (input->tokens[1][j] == '=')
		{
/* Checks if a variable with same name exists &temporarily changes its value */
				var_copy = str_duplicate(env_get_key(spname, input));
				if (var_copy != NULL)
					env_set_key(spname, input->tokens[1] + j + 1, input);

				/* display the environ */
				print_environ(input);
				if (env_get_key(spname, input) == NULL)
				{/* Prints the variable if it doesn’t exist in the environment */
					_print(input->tokens[1]);
					_print("\n");
				}
				else
				{/* Returns the previous value of the variable */
					env_set_key(spname, var_copy, input);
					free(var_copy);
				}
				return (0);
			}
			spname[j] = input->tokens[1][j];
		}
		errno = 2;
		perror(input->command_name);
		errno = 127;
	}
	return (0);
}
/**
 * builtin_set_env - Function to perform a specific task.
 * @input: Pointer to the struct holding program data.
 * Return: Integer indicating success (zero) or failure (non-zero).
 */

int builtin_set_env(shell_program *input)
{
	/* Validate argument */
	if (input->tokens[1] == NULL || input->tokens[2] == NULL)
		return (0);
	if (input->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(input->command_name);
		return (5);
	}

	env_set_key(input->tokens[1], input->tokens[2], input);

	return (0);
}

/**
 * builtin_unset_env - Function to perform a specific task.
 * @input: Pointer to the struct holding program data.
 * Return: Integer indicating success (zero) or failure (non-zero).
 */

int builtin_unset_env(shell_program *input)
{
	/* Validate Arguments */
	if (input->tokens[1] == NULL)
		return (0);
	if (input->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(input->command_name);
		return (5);
	}
	env_remove_key(input->tokens[1], input);

	return (0);
}
