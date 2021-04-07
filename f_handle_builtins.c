#include "shell.h"

/**
 * handle_builtins - Executes the builtin funtions in case the command is one
 * @commands: User's input parsed as an array of commads
 *
 * Return: 1 if the command is a builtin, 0 otherwise
*/
int handle_builtins(char **commands)
{
	if (commands[0] == NULL)
		return (0);

	if (commands[1] == NULL && strncmp(commands[0], "env", 3) == 0)
	{
		env();
		return (1);
	}

	return (0);
}