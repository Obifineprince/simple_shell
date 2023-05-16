#ifndef HELPERS_H
#define HELPERS_H

 /* Print the prompt */
#define PROMPT_MSG "dali<3 " /* Required for signal handling */

/* Proceed from the unused attribute */
#define UNUSED __attribute__((unused))

/* Size of the buffer used for each read call in _getline */
#define BUFFER_SIZE 1024

/************* Formatted string for the help built-in command. **************/

#define HELP_CD_MSG "cd=\n"\

"cd:\tcd [dir]\n\n"\
"	Changes the shell's working directory.\n\n"\
"	If no argument is provided, the command will be interpreted as cd $HOME.\n"\
"	If the argument is 'cd-', the command will be interpreted as cd $OLDPWD.\n\n"

#define HELP_EXIT_MSG "exit=\n"\

"exit:\texit [STATUS]\n\n"\
"	Exits the simple shell.\n\n"\
" 	Exits the shell with a status of N. If N is not provided, the exit status\n"\
" 	will be the same as that of the last executed command.\n\n"\

#define HELP_ENV_MSG "env=\n"\
"	env:\tenv \n\n"
"	Prints the environment.\n\n"
"	The env command displays a complete list of environment variables.\n\n"

#define HELP_SETENV_MSG "setenv=\n"\

"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	Changes or adds an environment variable.\n\n"\
"	Initializes a new environment variable or modifies the  existing one.\n"\
"	Prints an error message when the correct number of arguments is not provided.\n\n"

#define HELP_UNSETENV_MSG "unsetenv=\n"\

"unsetenv:\tunsetenv VARIABLE\n\n"\
"	The unsetenv function deletes a variable from the environment.\n\n"\
"	Prints an error message when the correct number of arguments is not provided.\n\n"


#define HELP_MSG "help=\n"\
help:\thelp [BUILTIN_NAME]\n\n
	Display information about builtin commands.\n
	Displays brief summaries of builtin commands. If BUILTIN_NAME is specified, 
	gives detailed help on the builtin command matching BUILTIN_NAME. If no argument
	is provided, prints the list of available builtin commands.\n\n
	Arguments:\n
	BUILTIN_NAME: specifying a help topic.\n\n
	Builtin commands:\n
	- cd [dir]\n
	- exit [status]\n
	- env\n
	- setenv [variable value]\n
	- unsetenv [variable]\n
	- help [builtin_name]\n\n



#endif

