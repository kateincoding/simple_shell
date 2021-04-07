#include "shell.h"

/**
 * handle_builtins - Executes the builtin funtions in case the command is one
 * @buff: Command as a string given by the user
 *
 * Return: 1 if the commad is a builtin, 0 otherwise
*/
int handle_builtins(char *buff)
{
	int i = 0;

	/* Avoid all first spaces */
	while (buff[i] != '\0' && buff[i] == ' ')
		i++;

	if (strncmp(&buff[i], "env", 3) == 0)
	{
		env();
		return (1);
	}

	return (0);
}