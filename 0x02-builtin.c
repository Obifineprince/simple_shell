#include "shell.h"

/**
 * builtin_env - displays the environment in which the shell is running
 * @input: struct containing program's data
 * Return: 0 if successful, or non-zero if specified in the arguments
 */
int builtin_env(shell_program *input)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	/* if not arguments */
	if (input->tokens[1] == NULL)
		print_environ(input);
	else
	{
		for (i = 0; input->tokens[1][i]; i++)
		{/* checks if exists a char = */
			if (input->tokens[1][i] == '=')
			{/* checks if exists a var with the same name and change its value*/
			/* temporally */
				var_copy = str_duplicate(env_get_key(cpname, input));
				if (var_copy != NULL)
					env_set_key(cpname, input->tokens[1] + i + 1, input);

				/* print the environ */
				print_environ(input);
				if (env_get_key(cpname, input) == NULL)
				{/* print the variable if it does not exist in the environ */
					_print(input->tokens[1]);
					_print("\n");
				}
				else
				{/* returns the old value of the var*/
					env_set_key(cpname, var_copy, input);
					free(var_copy);
				}
				return (0);
			}
			cpname[i] = input->tokens[1][i];
		}
		errno = 2;
		perror(input->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - Function to perform a specific task in the shell
 * @input: Pointer to the struct holding program data.
 * Return: Integer indicating success (zero) or failure (non-zero).
 */
int builtin_set_env(shell_program *input)
{
	/* validate args */
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
 * builtin_unset_env - Function to perform a specific task in the shell.
 * @input: Pointer to the struct holding program data.
 * Return: Integer indicating success (zero) or failure (non-zero).
 */
int builtin_unset_env(shell_program *input)
{
	/* validate args */
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
