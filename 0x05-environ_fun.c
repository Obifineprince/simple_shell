#include "shell.h"

/**
 * env_get_key - retrieves the value of an environment variable
 * @key: the name of the environment variable
 * @input: struct for the program's data
 * Return: a pointer to the value of the variable,
 * or NULL if it doesn't exist
 */

char *env_get_key(char *key, shell_program *input)
{
	int sp, length_of_key = 0;

	/* Validates the arguments. */
	if (key == NULL || input->env == NULL)
		return (NULL);

	/* Retrieves the length of the requested variable. */
	length_of_key = str_length(key);

	for (sp = 0; input->env[sp]; sp++)
	{
/* Iterates through the environment variables 
 * and checks for a match with the specified name. */
		if (str_compare(key, input->env[sp], length_of_key) &&
		 input->env[sp][length_of_key] == '=')
		{
/* Retrieves the value of the environment variable
 * with the specified key (NAME=) and returns it.
 */

			return (input->env[sp] + length_of_key + 1);
		}
	}
	/* Returns NULL if it is not found. */
	return (NULL);
}

/**
 * env_set_key - set the value of an environment
 * variable or create it if it doesn't exist
 * @key: name of the variable to set
 * @value: new value to assign
 * @input: struct for the program's data
 * Return: 1 if any parameter is NULL,
 * 2 if there is an error, or 0 if successful
 */



int env_set_key(char *key, char *value, input_program *input)
{
	int c, length_of_key = 0, new_key = 1;

	/* validate all arguments */
	if (key == NULL || value == NULL || input->env == NULL)
		return (1);

/* Obtain the length of the requested variable */
	length_of _key = str_length(key);

	for (c = 0; input->env[c]; c++)
	{
/* Iterate through the environ and check for a matching name */
		if (str_compare(key, input->env[c], length_of_key) &&
		 input->env[c][key_length_of_key] == '=')
		{/* If existing */
			new_key = 0;
/* Free the entire variable, which was newly created */
			free(input>env[c]);
			break;
		}
	}
	/* Create a string in the format "key=value" */
	input->env[c] = str_concat(str_duplicate(key), "=");
	input->env[c] = str_concat(input->env[c], value);

	if (new_key)
	{
/* If the variable is new, it is created at the end of
 * current list and we need to put the NULl
 *
 * value in the next position. */
		input->env[c + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - remove a key from the environment
 * @key: the key to remove
 * @input: the structure of the program's data
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int env_remove_key(char *key, shell_program *input)
{
	int c, length_of_key = 0;

	/* validate all args */
	if (key == NULL || input->env == NULL)
		return (0);

/*Retrieve the length of the requested variable*/
	length_of_key = str_length(key);

	for (c = 0; input->env[c]; c++)
	{
/*Scan through the environ and look for matches wit specified key*/
		if (str_compare(key, input->env[c], length_of_key) &&
		 input->env[c][length_of_key] == '=')
		{
/* If the key already exists, remove it before setting*/
			free(input->env[c]);

/* Shift the remaining keys one position down in the list */
			c++;
			for (; input->env[c]; c++)
			{
				input->env[c - 1] = input->env[c];
			}
/* Place the NULL value at the end of the list setting new value */
			input->env[ - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environ - prints the current environ
 * @input: struct for the program's data
 * Return: nothing
 */
void print_environ(shell_program *input)
{
	int p;

	for (p = 0; input->env[p]; p++)
	{
		_print(input->env[p]);
		_print("\n");
	}
}
