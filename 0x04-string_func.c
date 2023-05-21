#include "shell.h"

/**
 * str_leng - calc the length of a string.
 * @str: Pointer points  to the string.
 *
 * Return: The length of the string.
 */

int str_leng(char *str)
{
	int leng = 0;

	if (str == NULL)
		return (0);

	while (str[leng++] != '\0')
	{
	}
	return (--leng);
}

/**
 * str_duplic -function Duplicate a string.
 * @str: String to be duplicated.
 *
 * Return: Pointer to the duplicated string.
 */

char *str_duplic(char *str)
{
	char *output;
	int leng, c;

	if (str == NULL)
		return (NULL);

	leng = str_leng(str) + 1;

	output = malloc(sizeof(char) * leng);

	if (output == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (c = 0; c < leng ; c++)
	{
		output[c] = str[c];
	}

	return (output);
}

/**
 * compare_str - function  Comps two strings.
 * @str1: First string.
 * @str2: Second string.
 * @num_chars: Number of characters to compare.
 * Set to 0 for unlimited comparison.
 *
 * Return: if equal 1, 0 if the strings are different.
 */

int compare_str(char *str1, char *str2, int num_chars)
{
	int intercess;

	if (str1 == NULL && str2 == NULL)
		return (1);

	if (str1 == NULL || str2 == NULL)
		return (0);

	if (num_chars == 0) /* infinite longitud */
	{
		if (str_leng(str1) != str_leng(str2))
			return (0);
		for (intercess = 0; str1[intercess]; intercess++)
		{
			if (str1[intercess] != str2[intercess])
				return (0);
		}
		return (1);
	}
	else /* if there is a number of chars to be compared */
	{
		for (intercess = 0; intercess < num_chars ; intercess++)
		{
			if (str1[intercess] != str2[intercess])
			return (0);
		}
		return (1);
	}
}

/**
 * concat_str -  function Concatenates two strings.
 * @str1: First string.
 * @str2: Second string.
 *
 * Return: Pointer to the concatenated string.
 */

char *concat_str(char *str1, char *str2)
{
	char *output;
	int leng1 = 0, leng2 = 0;

	if (str1 == NULL)
		str1 = "";
	leng1 = str_leng(str1);

	if (str2 == NULL)
		str2 = "";
	leng2 = str_leng(str2);

	output = malloc(sizeof(char) * (leng1 + leng2 + 1));
	if (output == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* copy of string1 */
	for (leng1 = 0; str1[leng1] != '\0'; leng1++)
		output[leng1] = str1[leng1];
	free(str1);

	/* copy of string2 */
	for (leng2 = 0; str2[leng2] != '\0'; leng2++)
	{
		output[leng1] = str2[leng2];
		leng1++;
	}

	output[leng1] = '\0';
	return (output);
}


/**
 * rever_str - function  Reverses a given string.
 *
 * @str: Pointer to the string to be reversed.
 * Return: void.
 */


void rever_str(char *str)
{

	int c = 0, leng = str_leng(str) - 1;
	char hold;

	while (c < leng)
	{
		hold = str[c];
		str[c++] = str[leng];
		str[leng--] = hold;
	}
}

