#include "shell.h"

int handle_arguments(int ac, char **av, int *exec_file);
void handle_signal(void);

/**
 * main - Entry point
 * @ac: number of arguments
 * @av: Array of arguments
 *
 * Return: 0 on success
*/
int main(int ac, char **av)
{
	int read, exec_file = 0;
	char *buff = NULL;
	int fd;

	signal(SIGINT, handle_signal);
	fd = handle_arguments(ac, av, &exec_file);
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

/**
 * handle_arguments - Check the number of arguments passed to main
 * @ac: Number of arguments
 * @av: Array of arguments as strings
 * @exec_file: Integer used to check if user wants to exec commands from file
 *
 * Return: File descriptor to file
*/
int handle_arguments(int ac, char **av, int *exec_file)
{
	int fd = STDIN_FILENO;
	char *err_msg = "Error: more than one argument\n";

	if (ac > 2)
	{
		write(STDERR_FILENO, err_msg, strlen(err_msg));
		exit(1);
	}
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		*exec_file = 1;
	}
	if (fd == -1)
	{
		perror(av[0]);
		exit(1);
	}

	return (fd);
}

/**
 * handle_signal - Avoids current process to finish
*/
void handle_signal(void)
{
}
