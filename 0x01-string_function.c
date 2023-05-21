#include "shell.h"

/**
 * _print - writes an array of characters to the standard output
 * @string: pointer to the array of characters
 *
 * Return: the number of bytes written
 * or -1 on error with errno set appropriately.
 */

int _print(char *string)
{
	return (write(STDOUT_FILENO, string, str_leng(string)));
}
/**
 * _printe - writes an array of characters to the standard error
 * @string: pointer to the array of characters to be written
 *
 * Return: the number of bytes written.
 *         On error, -1 is returned, and errno is set appropriately.
 */

int _printe(char *string)
{
	return (write(STDERR_FILENO, string, str_leng(string)));
}

/**
 * _printerror - writes an array of characters to the standard error
 * @input: a pointer to the program's data
 * @error: error code to print
 *
 * Return: the number of bytes written.
 *         On error, -1 is returned, and errno is set appropriately.
 */

int _printerror(int error, shell_program *input)
{
	char n_as_string[10] = {'\0'};

	long_string((long) input->exec_counter, n_as_string, 10);

	if (error == 2 || error == 3)
	{
		_printe(input->program_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(input->tokens[0]);
		if (error == 2)
			_printe(": Illegal number: ");
		else
			_printe(": can't cd to ");
		_printe(input->tokens[1]);
		_printe("\n");
	}
	else if (error == 127)
	{
		_printe(input->program_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(input->command_name);
		_printe(": not found\n");
	}
	else if (error == 126)
	{
		_printe(input->program_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(input->command_name);
		_printe(": Permission denied\n");
	}
	return (0);
}
