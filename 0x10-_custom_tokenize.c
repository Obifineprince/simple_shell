#include "shell.h"

/**
 * tokenize - splits a string into tokens using a specified delimiter
 * @input: a pointer to the program's data
 * Return: an array of the different parts of the string
 */

void tokenize(shell_program *input)
{
	char *delimiter = " \t";
	int i, j, counter = 2, length;

	length = str_length(input->input_line);
	if (length)
	{
		if (input->input_line[length - 1] == '\n')
			input->input_line[length - 1] = '\0';
	}

	for (i = 0; input->input_line[i]; i++)
	{
		for (j = 0; delimiter[j]; j++)
		{
			if (input->input_line[i] == delimiter[j])
				counter++;
		}
	}

	input->tokens = malloc(counter * sizeof(char *));
	if (input->tokens == NULL)
	{
		perror(input->program_name);
		exit(errno);
	}
	i = 0;
	input->tokens[i] = str_duplicate(_strtok(input->input_line, delimiter));
	input->command_name = str_duplicate(input->tokens[0]);
	while (input->tokens[i++])
	{
		input->tokens[i] = str_duplicate(_strtok(NULL, delimiter));
	}
}
