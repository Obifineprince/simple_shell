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

int print_alias(shell_program *input, char *alias)
{
	int c, p, length_of_alias;
	char buffer[250] = {'\0'};

	if (input->alias_list)
	{
		length_of_alias = str_leng(alias);
		for (c = 0; input->alias_list[c]; c++)
		{
			if (!alias || (compare_str(input->alias_list[c], alias, length_of_alias)
				&&	input->alias_list[c][length_of_alias] == '='))
			{
				for (p = 0; input->alias_list[c][p]; p++)
				{
					buffer[p] = input->alias_list[c][p];
					if (input->alias_list[c][p] == '=')
						break;
				}
				buffer[p + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, input->alias_list[c] + p + 1);
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

char *get_alias(shell_program *input, char *name)
{
	int c, length_of_alias;

	if (name == NULL || input->alias_list == NULL)
		return (NULL);

	length_of_alias = str_leng(name);

	for (c = 0; input->alias_list[c]; c++)
	{
		if (compare_str(name, input->alias_list[c], length_of_alias) &&
			input->alias_list[c][length_of_alias] == '=')
		{
			return (input->alias_list[c] + length_of_alias + 1);
		}
	}
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

int set_alias(char *alias_string, shell_program *input)
{
	int c, p;
	char buffer[250] = {'0'}, *temp = NULL;

	if (alias_string == NULL ||  input->alias_list == NULL)
		return (1);
	for (c = 0; alias_string[c]; c++)
		if (alias_string[c] != '=')
			buffer[c] = alias_string[c];
		else
		{
/* search if the value of the alias is another alias */
			temp = get_alias(input, alias_string + c + 1);
			break;
		}
	for (p = 0; input->alias_list[p]; p++)
		if (compare_str(buffer, input->alias_list[p], c) &&
			input->alias_list[p][c] == '=')
		{
	/* if the alias alredy exist */
			free(input->alias_list[p]);
			break;
		}

	if (temp)
	{
/* if the alias already exist */
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		input->alias_list[p] = str_duplic(buffer);
	}
	else
	/* if the alias does not exist */
		input->alias_list[p] = str_duplic(alias_string);
	return (0);
}
