#include "shell.h"

/**
 * custom_tokenize - splits a string into tokens using a specified delimiter
 * @input: a pointer to the program's data
 * Return: an array of the different parts of the string
 */
void custom_tokenize(shell_program *input)
{
    char *delimiter = " \t";
    int c, j, counter = 2, length;

    length = str_length(input->input_str);
    if (length && input->input_str[length - 1] == '\n')
        input->input_str[length - 1] = '\0';

    for (c = 0; input->input_str[c]; c++)
    {
        for (j = 0; delimiter[j]; j++)
        {
            if (input->input_str[c] == delimiter[j])
                counter++;
        }
    }

    input->tokens = malloc(counter * sizeof(char *));
    if (input->tokens == NULL)
    {
        perror(input->program_name);
        exit(errno);
    }

    c = 0;
    input->tokens[i] = str_duplicate(_strtok(input->input_str, delimiter));
    input->command_name = str_duplicate(input->tokens[0]);

    while (input->tokens[c++])
    {
        input->tokens[i] = str_duplicate(_strtok(NULL, delimiter));
    }
}
