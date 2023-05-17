
#include "shell.h"

/**
 * expand_variables - Expands variables
 * @input: Pointer to a struct containing the program's data
 *
 * Return: None, but sets errno
 */

void expand_variables(shell_program *input)
{
	int s, p;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (input->input_line == NULL)
		return;
	buffer_add(line, input->input_line);
	for (s = 0; line[s]; s++)
		if (line[s] == '#')
			line[s--] = '\0';
		else if (line[s] == '$' && line[s + 1] == '?')
		{
			line[s] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, input->input_line + s + 2);
		}
		else if (line[s] == '$' && line[s + 1] == '$')
		{
			line[s] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, input->input_line + s + 2);
		}
		else if (line[s] == '$' && (line[s + 1] == ' ' || line[s + 1] == '\0'))
			continue;
		else if (line[s] == '$')
		{
			for (p = 1; line[s + p] && line[s + p] != ' '; p++)
				expansion[p - 1] = line[s + p];
			temp = env_get_key(expansion, input);
			line[s] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + s + p);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, expansion);
		}
	if (!str_compare(input->input_line, line, 0))
	{
		free(input->input_line);
		input->input_line = str_duplicate(line);
	}
}

/**
 * expand_alias - expand alias
 * @input: pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno
 */


void expand_alias(shell_program *input)
{
	int s, p, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (input->input_line == NULL)
		return;

	buffer_add(line, input->input_line);

	for (s = 0; line[s]; s++)
	{
		for (p = 0; line[s + p] && line[s + p] != ' '; p++)
			expansion[p] = line[s + p];
		expansion[p] = '\0';

		temp = get_alias(input, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + s + p);
			line[s] = '\0';
			buffer_add(line, temp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(input->input_line);
		input->input_line = str_duplicate(line);
	}
}

/**
 * buffer_add - Appends a string at the end of the buffer.
 * @buffer: The buffer to be filled.
 * @str_to_add: The string to be copied into the buffer.
 *
 * Description: This function appends the string @str_to_add at the end of
 *       the buffer @buffer. It does not return a value, but it may
 *      set the errno variable.
 * Return: retuurns the (length + c)
 */


int buffer_add(char *buffer, char *str_to_add)
{
	int len, c;

	len = str_length(buffer);
	for (c = 0; str_to_add[c]; c++)
	{
		buffer[leng + c] = str_to_add[c];
	}
	buffer[len + c] = '\0';
	return (len + c);
}

