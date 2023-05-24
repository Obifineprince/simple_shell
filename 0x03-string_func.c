#include "shell.h"

/**
 * long_to_string - Converts a number to a string.
 * @number: The number to be converted into a string.
 * @string: The buffer used to store the number as a string.
 * @base: The base used for the number conversion.
 *
 * Return: This function does not return a value.
 */
void long_to_string(long number, char *string, int base)
{
	int index = 0, inNegative = 0;
	long cociente = number;
	char letters[] = {"0123456789abcdef"};

	if (cociente == 0)
		string[index++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (cociente)
	{
		if (cociente < 0)
			string[index++] = letters[-(cociente % base)];
		else
			string[index++] = letters[cociente % base];
		cociente /= base;
	}
	if (inNegative)
		string[index++] = '-';

	string[index] = '\0';
	str_reverse(string);
}

/**
 * _atoi - this function Converts a string to an integer.
 * @s: Pointer to the input string.
 *
 * Return: The converted integer, or 0 if no valid integer found.
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;
	/*1- analisys sign*/
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}

	/*2 - extract the number */
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}
/**
 * count_characters - Counts the occurrences of a character in a string.
 *
 * @string: Pointer to the original string.
 * @character: Character to be counted.
 *
 * Return: Number of occurrences of the character.
 */

int count_characters(char *string, char *character)
{
	int i = 0, counter = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character[0])
			counter++;
	}
	return (counter);
}
