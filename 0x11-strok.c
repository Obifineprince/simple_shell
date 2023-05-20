#include "shell.h"
/**
 * _strtok - Separates strings with delimiters
 * @line: Pointer to the array we receive in getline
 * @delim: Characters we mark off the string in parts
 *
 * Return: A pointer to the created token
 */
char *_strtok(char *line, char *delim)
{
	int p;
	static char *string;
	char *stringcpy;

	if (line != NULL)
		string = line;

	for (; *string != '\0'; string++)
	{
		for (p = 0; delim[p] != '\0'; p++)
		{
			if (*string == delim[p])
				break;
		}
		if (delim[p] == '\0')
			break;
	}

	stringcpy = string;

	if (*stringcpy == '\0')
		return (NULL);

	for (; *string != '\0'; string++)
	{
		for (p = 0; delim[p] != '\0'; p++)
		{
			if (*string == delim[p])
			{
				*string = '\0';
				string++;
				return (stringcpy);
			}
		}
	}

	return (stringcpy);
}
