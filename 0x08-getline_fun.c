#include "shell.h"
/**
*_getline - Read a line of input from the user.
*
*
*@input: Pointer to a struct containing program data.
*
*
*Return: The number of bytes read.
*/

int _getline(shell_program *input)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *command_array[10] = {NULL};
	static char opera_arr[10] = {'\0'};
	ssize_t bytes_read, c = 0;

/* Check if there are no more commands in the array and logical operators */
	if (!command_array[0] || (opera_arr[0] == '&' && errno != 0) ||
		(opera_arr[0] == '|' && errno == 0))
	{
		/*free memory allocated in the array of commands */
		for (c = 0; command_array[c]; c++)
		{
			free(command_array[c]);
			command_array[c] = NULL;
		}

		/* read from the file descriptor int to buff */
		bytes_read = read(input->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		/* split lines for \n or ; */
		i = 0;
		do {
			command_arrays[c] = str_duplicate(_strtok(c ? NULL : buff, "\n;"));
			/*checks and split for && and || operators*/
			c = check_logic_ops(command_arrays, c, opera_arr);
		} while (command_arrays[c++]);
	}

	/*obtains the next command (command 0) and remove it for the array*/
	input->input_line = command_arrays[0];
	for (c = 0; command_arrays[c]; c++)
	{
		command_arrays[c] = array_commands[i + 1];
		opera_arr[c] = opera_arr[c + 1];
	}

	return (str_length(input->input_line));
}


/**
*check_logic_ops - checks and splits for && and || operators
*@command_arrays: array of commands
*@c: index in the array_commands to be checked
*@opera_arr: array of logical operators for each previous command
*
*
*Return: index of the last command in the command_arrays
*/


int check_logic_ops(char *command_array[], int c, char opera_arr[])
{
	char *temp = NULL;
	int p;

	/* checks for the '&' character in the command line */
	for (p = 0; command_arrays[c] != NULL  && command_arrays[c][p]; p++)
	{
		if (command_arrays[c][p] == '&' && command_arrays[c][p + 1] == '&')
		{
			/* splits the line when the "&&" characters are found */
			temp = command_arrays[c];
			command_arrays[c][p] = '\0';
			command_arrays[p] = str_duplicate(command_arrays[c]);
			command_arrays[c + 1] = str_duplicate(temp + p + 2);
			c++;
			opera_arr[c] = '&';
			free(temp);
			p = 0;
		}
		if (command_arrays[c][p] == '|' && command_arrays[c][p + 1] == '|')
		{
			/* split command line if “||” character is encountered */
			temp = command_arrays[c];
			command_arrays[c][p] = '\0';
			command_arrays[c] = str_duplicate(command_arrays[c]);
			command_arrays[c + 1] = str_duplicate(temp + p + 2);
			c++;
			opera_arr[c] = '|';
			free(temp);
			p = 0;
		}
	}
	return (c);
}
