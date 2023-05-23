#include "shell.h"

/**
 * custom_tokenize - splits a string into tokens using a specified delimiter
 * @input: a pointer to the program's data
 * Return: an array of the different parts of the string
 */
void custom_tokenize(shell_program *input)
{
	char *delimiter = " \t";
	int c, j, counter = 2, length;

	length = str_leng(input->input_line);
	if (length && input->input_line[length - 1] == '\n')
		input->input_line[length - 1] = '\0';

	for (c = 0; input->input_line[c]; c++)
	{
		for (j = 0; delimiter[j]; j++)
		{
			if (input->input_line[c] == delimiter[j])
				counter++;
		}
	}

	input->tokens = malloc(counter * sizeof(char *));
	if (input->tokens == NULL)
	{
		perror(input->program_name);
		exit(errno);
	}

	c = 0;
	input->tokens[c] = str_duplic(_strtok(input->input_line, delimiter));
	input->command_name = str_duplic(input->tokens[0]);

	while (input->tokens[c])
	{
		c++;
		input->tokens[c] = str_duplic(_strtok(NULL, delimiter));
	}
}
