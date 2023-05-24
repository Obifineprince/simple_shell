#include "shell.h"
/**
 * print_alias - Function for managing aliases
 * (add, remove, or show)
 * @input: Pointer to the program's data struct
 * @alias: Name of the alias to be printed
 *
 * This function handles and manages the aliases in the program.
 * It can add, remove, or show aliases based on the provided arguments.
 *
 * Return: Returns zero if it is successful,
 * or a non-zero number if there
 *  is an error or if the specified alias is not found.
 */

int print_func_alias(shell_program *input, char *alias)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (input->alias_list)
	{
		alias_length = str_length(alias);
		for (i = 0; input->alias_list[i]; i++)
		{
			if (!alias || (str_compare(input->alias_list[i], alias, alias_length)
				&&	input->alias_list[i][alias_length] == '='))
			{
				for (j = 0; input->alias_list[i][j]; j++)
				{
					buffer[j] = input->alias_list[i][j];
					if (input->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, input->alias_list[i] + j + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}
/**
 * get_alias - Function for retrieving aliases
 * @input: Pointer to the program's data struct
 * @name: Name of the requested alias
 *
 * This function is responsible for retrieving aliases
 * based on the provided name.
 * It searches for the specified alias in the program's
 * data and returns it if found.
 *
 * Return: Returns 0 if the alias is found,
 * or a non-zero number if the alias
 * is not found or if there is an error.
 */

char *get_func_alias(shell_program *input, char *name)
{
	int i, alias_length;

	/* validate the arguments */
	if (name == NULL || input->alias_list == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (i = 0; input->alias_list[i]; i++)
	{/* Iterates through the environ and check for coincidence of the varname */
		if (str_compare(name, input->alias_list[i], alias_length) &&
			input->alias_list[i][alias_length] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (input->alias_list[i] + alias_length + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);

}

/**
 * set_alias - Function for adding or overriding an alias
 * @alias_string: Alias to be set in the form (name='value')
 * @input: Pointer to the program's data struct
 *
 * This function is responsible for adding
 * or overriding an alias as provided string.
 * The alias string should be in the format "name='value'".
 * It adds the alias to the program's data.
 *
 * Return: Returns zero if the alias is successfully set,
 * or a non-zero number if there is an error
 * or if the alias string is not in the correct format.
 */
int set_func_alias(char *alias_string, shell_program *input)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	/* validate the arguments */
	if (alias_string == NULL ||  input->alias_list == NULL)
		return (1);
	/* Iterates alias to find = char */
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{/* search if the value of the alias is another alias */
			temp = get_alias(input, alias_string + i + 1);
			break;
		}

	/* Iterates through the alias list and check for coincidence of the varname */
	for (j = 0; input->alias_list[j]; j++)
		if (str_compare(buffer, input->alias_list[j], i) &&
			input->alias_list[j][i] == '=')
		{/* if the alias alredy exist */
			free(input->alias_list[j]);
			break;
		}

	/* add the alias */
	if (temp)
	{/* if the alias already exist */
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		input->alias_list[j] = str_duplicate(buffer);
	}
	else /* if the alias does not exist */
		input->alias_list[j] = str_duplicate(alias_string);
	return (0);
}
