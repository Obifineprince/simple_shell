#include "shell.h"

/**
 * free_recurrent_data - This function frees the
 * fields that are needed for each loop
 *
 * @input: A struct containing the program's data
 *
 * Return: void
 */

void free_recurrent_data(shell_program *input)
{
	if (input->tokens)
		free_array_of_pointers(input->tokens);
	if (input->input_line)
		free(input->input_line);
	if (input->command_name)
		free(input->command_name);

	input->input_line = NULL;
	input->command_name = NULL;
	input->tokens = NULL;
}
/**
 * free_all_data - This function frees all
 * fields of the program's data
 *
 * @input: A struct containing the program's data
 *
 * Return: void
 */

void free_all_data(shell_program *input)
{
	if (input->file_descriptor != 0)
	{
		if (close(input->file_descriptor))
			perror(input->program_name);
	}
	free_recurrent_data(input);
	free_array_of_pointers(input->env);
	free_array_of_pointers(input->alias_list);
}
/**
 * free_array_of_pointers - This function frees each pointer of
 * an array of pointers and the array itself
 *
 * @array: An array of pointers
 *
 * Return: void
 */


void free_array_of_pointers(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}
