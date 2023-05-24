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
	int i, key_length = 0;

	/* validate the arguments */
	if (key == NULL || input->env == NULL)
		return (NULL);

<<<<<<< HEAD
	/* Retrieves the length of the requested variable. */
	length_of_key = str_length(key);

	for (sp = 0; input->env[sp]; sp++)
	{
		if (str_compare(key, input->env[sp], length_of_key) &&
			input->env[sp][length_of_key] == '=')
		{
			return (input->env[sp] + length_of_key + 1);
=======
	/* obtains the leng of the variable requested */
	key_length = str_length(key);

	for (i = 0; input->env[i]; i++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_compare(key, input->env[i], key_length) &&
		 input->env[i][key_length] == '=')
		{/* returns the value of the key NAME=  when find it*/
			return (input->env[i] + key_length + 1);
>>>>>>> 50257b058fc8c88d070cdc981e3331de38958e86
		}
	}
	/* returns NULL if did not find it */
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

int env_set_key(char *key, char *value, shell_program *input)
{
	int i, key_length = 0, is_new_key = 1;

	/* validate the arguments */
	if (key == NULL || value == NULL || input->env == NULL)
		return (1);

<<<<<<< HEAD
	/* Obtain the length of the requested variable */
	length_of_key = str_length(key);

	for (c = 0; input->env[c]; c++)
	{
		/* Iterate through the environ and check for a matching name */
		if (str_compare(key, input->env[c], length_of_key) &&
			input->env[c][length_of_key] == '=')
		{
			/* If existing */
			new_key = 0;
			/* Free the entire variable, which was newly created */
			free(input->env[c]);
			break;
		}
	}
	/* Create a string in the format "key=value" */
	input->env[c] = str_concatenate(str_duplicate(key), "=");
	input->env[c] = str_concatenate(input->env[c], value);

	if (new_key)
	{
		input->env[c + 1] = NULL;
=======
	/* obtains the leng of the variable requested */
	key_length = str_length(key);

	for (i = 0; input->env[i]; i++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_compare(key, input->env[i], key_length) &&
		 input->env[i][key_length] == '=')
		{/* If key already exists */
			is_new_key = 0;
			/* free the entire variable, it is new created below */
			free(input->env[i]);
			break;
		}
	}
	/* make an string of the form key=value */
	input->env[i] = str_concat(str_duplicate(key), "=");
	input->env[i] = str_concat(input->env[i], value);

	if (is_new_key)
	{/* if the variable is new, it is create at end of actual list and we need*/
	/* to put the NULL value in the next position */
		input->env[i + 1] = NULL;
>>>>>>> 50257b058fc8c88d070cdc981e3331de38958e86
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
	int i, key_length = 0;

	/* validate the arguments */
	if (key == NULL || input->env == NULL)
		return (0);

<<<<<<< HEAD
	/* Retrieve the length of the requested variable */
	length_of_key = str_length(key);

	for (c = 0; input->env[c]; c++)
	{
/* Scan through the environ and look for matches with specified key */
		if (str_compare(key, input->env[c], length_of_key) &&
			input->env[c][length_of_key] == '=')
		{
		/* If the key already exists, remove it before setting */
			free(input->env[c]);

/* Shift the remaining keys one position down in the list */
			c++;
			for (; input->env[c]; c++)
=======
	/* obtains the leng of the variable requested */
	key_length = str_length(key);

	for (i = 0; input->env[i]; i++)
	{/* iterates through the environ and checks for coincidences */
		if (str_compare(key, input->env[i], key_length) &&
		 input->env[i][key_length] == '=')
		{/* if key already exists, remove them */
			free(input->env[i]);

			/* move the others keys one position down */
			i++;
			for (; input->env[i]; i++)
>>>>>>> 50257b058fc8c88d070cdc981e3331de38958e86
			{
				input->env[i - 1] = input->env[i];
			}
			/* put the NULL value at the new end of the list */
			input->env[i - 1] = NULL;
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
	int j;

	for (j = 0; input->env[j]; j++)
	{
		_print(input->env[j]);
		_print("\n");
	}
}
