#include "shell.h"

int check_file(char *full_path);

/**
 * seek_program - Searches for a program in the specified path.
 * @input: A pointer to the program's data.
 *
 * Return: 0 if the program is found, or an error code otherwise.
 */

int seek_program(shell_program *input)
{
	int i = 0, ret_code = 0;
	char **directory;

	if (!input->command_name)
		return (2);

	/**if is a full_path or an executable in the same path */
	if (input->command_name[0] == '/' || input->command_name[0] == '.')
		return (check_file(input->command_name));

	free(input->tokens[0]);
	input->tokens[0] = concat_str(str_duplic("/"), input->command_name);
	if (!input->tokens[0])
		return (2);

	directory = path(input);/* search in the PATH */

	if (!directory || !directory[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; directory[i]; i++)
	{/* appends the function_name to path */
		directory[i] = concat_str(directory[i], input->tokens[0]);
		ret_code = check_file(directory[i]);
		if (ret_code == 0 || ret_code == 126)
		{/* the file was found, is not a directory and has execute permisions*/
			errno = 0;
			free(input->tokens[0]);
			input->tokens[0] = str_duplic(directory[i]);
			free_pointers(directory);
			return (ret_code);
		}
	}
	free(input->tokens[0]);
	input->tokens[0] = NULL;
	free_pointers(directory);
	return (ret_code);
}

/**
 * path - Tokenizes the path string into individual directories.
 * @input: A pointer to the program's data.
 *
 * Return: An array of path directories.
 */

char **path(shell_program *input)
{
	int c = 0;
	int oppose_directory = 2;
	char **tokens = NULL;
	char *PATH;

	/* get the PATH value*/
	PATH = env_get_key("PATH", input);
	if ((PATH == NULL) || PATH[0] == '\0')
	{/*path not found*/
		return (NULL);
	}

	PATH = str_duplic(PATH);

	/* find the number of directories in the PATH */
	for (c = 0; PATH[c]; c++)
	{
		if (PATH[c] == ':')
			oppose_directory++;
	}

	/* reserve space for the array of pointers */
	tokens = malloc(sizeof(char *) * oppose_directory);

	/*tokenize and duplicate each token of path*/
	c = 0;
	tokens[c] = str_duplic(_strtok(PATH, ":"));
	while (tokens[c++])
	{
		tokens[c] = str_duplic(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * check_file - function checks availability of file,
 * is not a directory, and has execution permissions
 * @full_path: pointer to the full file name
 *
 * Return: an error code if it does not exist or lacks permissions.
 */


int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/*if not exist the file*/
	errno = 127;
	return (127);
}
