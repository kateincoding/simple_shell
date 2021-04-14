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
	int read, exec_file = 0;
	char *buff = NULL;
	int fd = STDIN_FILENO;

	if (ac > 2)
	{
		char *err_msg = "Error: more than one argument\n";

		write(STDERR_FILENO, err_msg, strlen(err_msg));
		return (errno);
	}
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		exec_file = 1;
	}
	if (fd == -1)
	{
		perror(av[0]);
		return (errno);
	}
	update_count_lines();
	while (1)
	{
		/* Print console symbol only if it is interactive*/
		if (isatty(STDIN_FILENO) == 1 && exec_file == 0)
			write(STDOUT_FILENO, "#cisfun$ ", 9);
		/* Read commands from console */
		read = read_line(fd, &buff);
		/* Remove comments & '\n' char from buffer */
		handle_history(buff);
		buff = handle_comment(buff);
		_strtok(buff, "\n");
		/* Handling_semicolon, ||, && and executes inside of the function */
		handling_semicolon_and_operators(buff, read, av[0]);
	}
	/* Free buffer memory */
	free(buff);
	if (exec_file)
		close(fd);
	return (0);
}
