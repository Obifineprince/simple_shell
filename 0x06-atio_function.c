#include "shell.h"
#include <unistd.h>

/**
 * interactive - checks if the shell is running in interactive mode
 * @info: pointer to the shell_program struct
 *
 * Return: 1 if running in interactive mode, 0 otherwise
 */

int interactive(shell_program *info)
{
	if (isatty(STDIN_FILENO) && info != NULL)
		return (1);

	return (0);
}
/**
 * _delim - checks if a character is a delimiter
 * @c: the character to check
 * @delim: the delimiter string
 *
 * Return: 1 if the character is a delimiter, 0 otherwise
 */

int _delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _alpha - checks if a character is alphabetic
 * @c: the character to check
 *
 * Return: 1 if the character is alphabetic, 0 otherwise
 */

int _alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
