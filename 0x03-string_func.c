#include "shell.h"

/**
 * long_string - Converts a number to a string.
 * @numb: The number to be converted into a string.
 * @str: The buffer used to store the number as a string.
 * @base: The base used for the number conversion.
 *
 * Return: This function does not return a value.
 */


void long_string(long numb, char *str, int base)
{
    int index = 0, inNegative = 0;
    long cociente = numb;
    char letters[] = {"0123456789abcdef"};

    if (cociente == 0)
        str[index++] = '0';

    if (str[0] == '-')
        inNegative = 1;

    while (cociente)
    {
        if (cociente < 0)
            str[index++] = letters[-(cociente % base)];
        else
            str[index++] = letters[cociente % base];
        cociente /= base;
    }
    if (inNegative)
        str[index++] = '-';

    str[index] = '\0';
   rever_str(str);
}


/**
 * _atoi - Converts a string to an integer.
 *
 * @p: Pointer to the original string.
 * Return: Integer value of the string or 0 if conversion fails.
 */

/*
int _atoi(char *p)
{
    int sign = 1;
    unsigned int numb = 0;

    while (!('0' <= *p && *p <= '9') && *p != '\0')
    {
        if (*p == '-')
            sign *= -1;
        if (*p == '+')
            sign *= +1;
        p++;
    }

    while ('0' <= *p && *p <= '9' && *p != '\0')
    {
        numb = (numb * 10) + (*p - '0');
        p++;
    }
    return (numb * sign);
}
*/

/**
 * count_char - count the occurrences of a character in a string.
 *
 * @str: pointer to the original string.
 * @character: character to be counted.
 * Return: number of occurrences of the character.
 */
int count_char(char *str, char *character)
{
    int c = 0, count = 0;

    for (; str[c]; c++)
    {
        if (str[c] == character[0])
            count++;
    }
    return (count);
}

