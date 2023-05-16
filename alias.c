#include "shell.h"

/**
 * print_alias - Function for managing aliases (add, remove, or show)
 * @input: Pointer to the program's data struct
 * @alias: Name of the alias to be printed
 *
 * This function handles and manage the aliases in the program.
 * It can add, remove, or show aliases based on the provided arguments.
 *
 * Return: Returns zero if it is successful, or a non-zero number if there
 *         is an error or if the specified alias is not found.
 */

int print_alias(shellf_program *input, char *alias)
{
	int c, j, length_of_alias;
	char buffer[250] = {'\0'};

	if (input->alias_list)
	{
		length_of_alias = str_length(alias);
		for (c = 0; input->alias_list[c]; i++)
		{
			if (!alias || (str_compare(input->alias_list[c], alias, length_of_alias)
				&&	input->alias_list[c][length_of_alias] == '='))
			{
				for (j = 0; input->alias_list[c][j]; j++)
				{
					buffer[j] = input->alias_list[c][j];
					if (input->alias_list[c][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, input->alias_list[c] + j + 1);
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
 * This function is respon* for retrieving aliases based on the provided name.
 * It searches for specified alias in the program's data & returns it if found.
 *
 * Return: Returns 0 if the alias is found, or a non-zero number if the alias
 *         is not found or if there is an error.
 */

char *get_alias(shell_program *input, char *name)
{
	int c, length_of_alias;

	/* validate the arguments */
	if (name == NULL || input->alias_list == NULL)
		return (NULL);

	length_of_alias = str_length(name);

	for (c = 0; input->alias_list[c]; i++)

/*Iterates from environ variables & checksfor match of spec* variable name */
	{
		if (str_compare(name, input->alias_list[c], length_of_alias) &&
			input->alias_list[c][length_of_alias] == '=')
 /* Returns the value of the key "NAME=" when it is found */
		{
			return (input->alias_list[i] + length_of_alias + 1);
		}
	}

	return (NULL);

}
/**
 * set_alias - Function for adding or overriding an alias
 * @alias_string: Alias to be set in the form (name='value')
 * @input: Pointer to the program's data struct
 *
 * This function is respon* for adding or
 * overriding an alias asprovided  string.
 * The alias string should be in the format "name='value'".
 *  It adds the alias to the program's data.
 *
 * Return: Returns zero if the alias is successfully set,
 * or a non-zero number if there is an error
 *         or if the alias string is not in the correct format.
 */

int set_alias(char *alias_string, shell_program *input)
{
	int c, j;
	char buffer[250] = {'0'}, *temp = NULL;

	/* Performs argument validation */
	if (alias_string == NULL ||  input->alias_list == NULL)
		return (1);
	/* Iterates through aliases to find the '=' character */
	for (c = 0; alias_string[c]; i++)
		if (alias_string[c] != '=')
			buffer[c] = alias_string[c];
		else
		/* Searches if the value of the alias is another alias */
			temp = get_alias(input, alias_string + c + 1);
			break;
		}

/* Iterates through the alias list & checks for match with variable name */
	for (j = 0; input->alias_list[j]; j++)
		if (str_compare(buffer, input->alias_list[j], c) &&
			input->alias_list[j][c] == '=')
		{/* checks alias existence */
			free(input->alias_list[j]);
			break;
		}

	/* add the alias */
	if (temp)
	{/* checks if is  alias in existence */
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		input->alias_list[j] = str_duplicate(buffer);
	}
	else /* checks if alias is not existence */
		input->alias_list[j] = str_duplicate(alias_string);
	return (0);
}
