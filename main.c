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

	/* check for program in built ins */
	retval = builtins_list(input);
	if (retval != -1)/* if program was found in built ins */
		return (retval);

	/* check for program file system */
	retval = seek_program(input);
	if (retval)
	{/* if program not found */
		return (retval);
	}
	else
	{/* if program was found */
		pidd = fork(); /* create a child process */
		if (pidd == -1)
		{ /* if the fork call failed */
			perror(input->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{/* I am the child process, I execute the program*/
			retval = execve(input->tokens[0], input->tokens, input->env);
			if (retval == -1) /* if error when execve*/
				perror(input->command_name), exit(EXIT_FAILURE);
		}
		else
		{/* I am the father, I wait and check the exit status of the child */
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
