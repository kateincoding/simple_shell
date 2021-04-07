#include "shell.h"

/**
 * main - Entry point
 * @ac: number of arguments
 * @av: Array of arguments
 *
 * Return: 0 on success
*/
int main(int __attribute__((unused))ac, char **av)
{
	int read;
	char *buff = NULL;
	size_t buff_len = 0;

	int child_pid;
	char **commands;

	while (1)
	{
		/* Print console symbol only if it is interactive*/
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "#cisfun$ ", 9);
		/* Read commands from console */
		read = getline(&buff, &buff_len, stdin);
		/* Remove '\n' char from buffer */
		_strtok(buff, "\n");
		/* Generate array of commands */
		commands = parse_user_input(buff);
		if (read == EOF)
		{
			free(buff);
			free_dbl_ptr(commands);
			exit(0);
		}

		/* Exit error, ENTER, and builtins */
		if (handle_exit(buff, commands) == -1 ||
				handle_enter(commands) == 1				||
				handle_builtins(buff) == 1)
		{
			free_dbl_ptr(commands);
			continue;
		}

		/* Fork parent process to execute the command */
		child_pid = fork();
		if (child_pid == -1)
			dispatch_error(av[0], 1);
		else if (child_pid == 0)
		{
			/* Search command using the PATH env variable */
			handle_PATH(commands);
			/* execute command */
			execve(commands[0], commands, NULL);
			/* free memory */
			free(buff);
			free_dbl_ptr(commands);
			/* handle errors */
			dispatch_error(av[0], 1);
		}
		else
			wait(NULL);

		free_dbl_ptr(commands);
	}
	/* Free buffer memory */
	free(buff);

	return (0);
}