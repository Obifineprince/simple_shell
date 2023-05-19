
#include "shell.h"

/**
 * free_recurrent - This function frees the fields that are needed for each loop
 *
 * @input: A struct containing the program's data
 *
 * Return: void
 */


void free_recurrent(shell_program *input)
{
	if (input->tokens)
		free_pointers(input->tokens);
	if (input->input_line)
		free(input->input_line);
	if (input->command_name)
		free(input->command_name);

	input->input_line = NULL;
	input->command_name = NULL;
	input->tokens = NULL;
}
/**
 * free_data - This function frees all fields of the program's data
 *
 * @input: A struct containing the program's data
 *
 * Return: void
 */


void free_data(shell_program *input)
{
	if (input->file_descriptor != 0)
	{
		if (close(input->file_descriptor))
			perror(input->program_name);
	}
	free_data(input);
	free_pointers(input->env);
	free_pointers(input->alias_list);
}

/**
 * free_pointers - This function frees each pointer of an array of pointers and the array itself
 *
 * @directory: An array of pointers
 *
 * Return: void
 */


void free_pointers(char **directory)
{
	int c;

	if (directory != NULL)
	{
		for (c = 0; directory[c]; c++)
			free(directory[c]);

		free(directory);
		directory = NULL;
	}
}

