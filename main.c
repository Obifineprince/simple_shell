#include "shell.h"

/**
 * execute - command execution using its complete path and variables.
 * @input: this input points to the program's data structure.
 * Return: Returns zero on success, otherwise returns -1.
 */

int execute(shell_program *input)
{
    int retval = 0, status;
    pid_t pidd;

    retval = builtins_list(input);
    if (retval != -1) /* if program was found in built-ins */
        return (retval);

    retval = seek_program(input);
    if (retval)
    {   /* if the program is not found */
        return (retval);
    }
    else
    {   /* if program is found */
        pidd = fork(); /* produce a child process */
        if (pidd == -1)
        {   /* if the fork operation was unsuccessful */
            perror(input->command_name);
            exit(EXIT_FAILURE);
        }
        if (pidd == 0)
        {   /* this is the child process, it executes programs */
            retval = execve(input->tokens[0], input->tokens, input->env);
            perror(input->command_name);
            exit(EXIT_FAILURE);
        }
        else
        {   /* parent process, checks child process exit status */
            wait(&status);
            if (WIFEXITED(status))
                errno = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                errno = 128 + WTERMSIG(status);
        }
    }
    return (0);
}
