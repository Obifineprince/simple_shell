#include "shell.h"
/**
 * main - Entry point of the program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 * @env: Array of environment variable strings.
 *
 * Return: 0 on success.
 */
int main(int argc, char *argv[], char *env[])
{
	shell_program input_struct = {NULL}, *input = &input_struct;
	char *prompt = "";

	inicialize_data(input, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* We are in the terminal, interactive mode */
		errno = 2;/*???????*/
		prompt = PROMPT_MSG;
	}
	errno = 0;
	process_input(prompt, input);
	return (0);
}
/**
 * handle_ctrl_c - Handles the SIGINT signal
 * (Ctrl+C) by printing the prompt in a new line
 * @UNUSED: Unused parameter (can be removed)
 *
 * Return: None
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}
/**
 * inicialize_data - Initializes the program's
 * data structure with the provided information
 * @input: Pointer to the data structure to be initialized
 * @argv: Array of arguments passed to the program execution
 * @env: Environment variables passed to the program execution
 * @argc: Number of values received from the command line
 *
 * Return: None
 */
void inicialize_data(shell_program *input, int argc, char *argv[], char **env)
{
	int i = 0;

	input->program_name = argv[0];
	input->input_line = NULL;
	input->command_name = NULL;
	input->exec_counter = 0;
	/* define the file descriptor to be readed*/
	if (argc == 1)
		input->file_descriptor = STDIN_FILENO;
	else
	{
		input->file_descriptor = open(argv[1], O_RDONLY);
		if (input->file_descriptor == -1)
		{
			_printe(input->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	input->tokens = NULL;
	input->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			input->env[i] = str_duplicate(env[i]);
		}
	}
	input->env[i] = NULL;
	env = input->env;

	input->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		input->alias_list[i] = NULL;
	}
}
/**
 * process_input - Performs operations with
 * a given prompt and shell program input
 * @prompt: Pointer to a character array representing the prompt
 * @input: Pointer to a shell_program structure
 *
 * Return: None
 */
void process_input(char *prompt, shell_program *input)
{
	int error_code = 0, string_len = 0;

	while (++(input->exec_counter))
	{
		_print(prompt);
		error_code = string_len = _getline(input);

		if (error_code == EOF)
		{
			free_all_data(input);
			exit(errno); /* if EOF is the fisrt Char of string, exit*/
		}
		if (string_len >= 1)
		{
			alias_expansion(input);
			variables_expansion(input);
			tokenize(input);
			if (input->tokens[0])
			{ /* if a text is given to prompt, execute */
				error_code = execute(input);
				if (error_code != 0)
					_print_error(error_code, input);
			}
			free_recurrent_data(input);
		}
	}
}
