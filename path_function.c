#include "shell.h"

int check_file(char *full_path);
/**
 * seek_program - Search for a program in the specified path directories.
 *
 * @input: Pointer to the program's data structure.
 *
 * Return: 0 on success (program found and accessible), error code otherwise.
 */
int seek_program(shell_program *input)
{
	int i = 0, ret_code = 0;
	char **directories;

	if (!input->command_name)
		return (2);

	/**if is a full_path or an executable in the same path */
	if (input->command_name[0] == '/' || input->command_name[0] == '.')
		return (check_file(input->command_name));

	free(input->tokens[0]);
	input->tokens[0] = str_concatenate(str_duplicate("/"), input->command_name);
	if (!input->tokens[0])
		return (2);

	directories = tokenize_path(input);/* search in the PATH */

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; directories[i]; i++)
	{/* appends the function_name to path */
		directories[i] = str_concatenate(directories[i], input->tokens[0]);
		ret_code = check_file(directories[i]);
		if (ret_code == 0 || ret_code == 126)
		{/* the file was found, is not a directory and has execute permisions*/
			errno = 0;
			free(input->tokens[0]);
			input->tokens[0] = str_duplicate(directories[i]);
			free_array_of_pointers(directories);
			return (ret_code);
		}
	}
	free(input->tokens[0]);
	input->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (ret_code);
}
/**
 * tokenize_path - Split the path string into individual directory tokens.
 *
 * @input: Pointer to the program's data structure.
 *
 * Description: This function takes a path string and splits it into individual
 *              directory tokens. It returns an array of path directories.
 *
 * Return: An array of path directories.
 */

char **tokenize_path(shell_program *input)
{
	int i = 0;
	int counter_directories = 2;
	char **tokens = NULL;
	char *PATH;

	/* get the PATH value*/
	PATH = env_get_key("PATH", input);
	if ((PATH == NULL) || PATH[0] == '\0')
	{/*path not found*/
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	/* find the number of directories in the PATH */
	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			counter_directories++;
	}

	/* reserve space for the array of pointers */
	tokens = malloc(sizeof(char *) * counter_directories);

	/*tokenize and duplicate each token of path*/
	i = 0;
	tokens[i] = str_duplicate(_strtok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = str_duplicate(_strtok(NULL, ":"));
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
