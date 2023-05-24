#include "shell.h"

/**
 * builtin_exit - Terminates the program with a specific status
 * @input: Pointer to the program's data structure
 * Return: Returns zero if successful,
 * or a non-zero value if specified in the arguments
 */
int builtin_exit(shell_program *input)
{
	int i;

	if (input->tokens[1] != NULL)
	{/*if exists arg for exit, check if is a number*/
		for (i = 0; input->tokens[1][i]; i++)
			if ((input->tokens[1][i] < '0' || input->tokens[1][i] > '9')
				&& input->tokens[1][i] != '+')
			{/*if is not a number*/
				errno = 2;
				return (2);
			}
		errno = _atoi(input->tokens[1]);
	}
	free_all_data(input);
	exit(errno);
}

/**
 * builtin_cd - change the current directory
 * @input: struct for the program's data
 * Return: Returns zero if successful,
 * or a non-zero number if an error occurs
 */
int builtin_cd(shell_program *input)
{
	char *dir_home = env_get_key("HOME", input), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (input->tokens[1])
	{
		if (str_compare(input->tokens[1], "-", 0))
		{
			dir_old = env_get_key("OLDPWD", input);
			if (dir_old)
				error_code = set_work_directory(input, dir_old);
			_print(env_get_key("PWD", input));
			_print("\n");

			return (error_code);
		}
		else
		{
			return (set_work_directory(input, input->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (set_work_directory(input, dir_home));
	}
	return (0);
}

/**
 * set_work_directory - set the working directory
 * @input: struct for the program's data
 * @new_dir: path to be set as the working directory
 * Return: Returns zero if successful,
 * or a non-zero number if an error occurs
 */
int set_work_directory(shell_program *input, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_compare(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, input);
	}
	env_set_key("OLDPWD", old_dir, input);
	return (0);
}

/**
 * builtin_help - display the help information for the shell
 * @input: struct for the program's data
 * Return: Returns zero if successful,
 * or a non-zero number if an error occurs
 */
int builtin_help(shell_program *input)
{
	int i, length = 0;
	char *mensajes[6] = {NULL};

	mensajes[0] = HELP_MSG;

	/* validate args */
	if (input->tokens[1] == NULL)
	{
		_print(mensajes[0] + 6);
		return (1);
	}
	if (input->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(input->command_name);
		return (5);
	}
	mensajes[1] = HELP_EXIT_MSG;
	mensajes[2] = HELP_ENV_MSG;
	mensajes[3] = HELP_SETENV_MSG;
	mensajes[4] = HELP_UNSETENV_MSG;
	mensajes[5] = HELP_CD_MSG;

	for (i = 0; mensajes[i]; i++)
	{
		/*print the length of string */
		length = str_length(input->tokens[1]);
		if (str_compare(input->tokens[1], mensajes[i], length))
		{
			_print(mensajes[i] + length + 1);
			return (1);
		}
	}
	/*if there is no match, print error and return -1 */
	errno = EINVAL;
	perror(input->command_name);
	return (0);
}

/**
 * builtin_alias - manage aliases (add, remove, or show)
 * @input: struct for the program's data
 * Return: Returns zero if successful.
 * or a non-zero number if an error occurs
 */
int builtin_alias(shell_program *input)
{
	int i = 0;

	/* if there are no arguments, print all environment */
	if (input->tokens[1] == NULL)
		return (print_func_alias(input, NULL));

	while (input->tokens[++i])
	{/* if there are arguments, set or print each env variable*/
		if (count_characters(input->tokens[i], "="))
			set_func_alias(input->tokens[i], input);
		else
			print_func_alias(input, input->tokens[i]);
	}

	return (0);
}
