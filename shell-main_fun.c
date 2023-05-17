#include "shell.h"

/**
 * execute - execute a command using its complete path and variables.
 * @input: a pointer to the program's data structure.
 * Return: Returns zero on success, otherwise returns -1.
 */

int execute(shell_program *input)
{
	int retval = 0, status;
	pid_t pidd;

/* Check if the program is a built-in command */
	retval = builtins_list(input);
	if (retval != -1)/* if program was found in built ins */
		return (retval);

	/* Verify the existence of the program in the file system */
	retval = find_program(input);
	if (retval)
	{/* if the program is not found */
		return (retval);
	}
	else
	{/* if program is found */
		pidd = fork();/* produce a child process */
		if (pidd == -1)
		{ /* if the fork operation was unsuccessful */
			perror(input->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{/* this is child process, it execute  programs*/
			retval = execve(input->tokens[0], input->tokens, input->env);
			if (retval == -1) /* if  an error occurs */
				perror(input->command_name), exit(EXIT_FAILURE);
		}
		else
		{
/* parent process,  checks child process exit status. */
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
