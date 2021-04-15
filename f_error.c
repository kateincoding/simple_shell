#include "shell.h"

/**
 * dispatch_error - Dispatches an error
 * @msg: Message to print as error
*/
void dispatch_error(char *msg)
{
	int len = _strlen(msg);

	/* perror(msg); */
	write(STDERR_FILENO, msg, len);
	write(STDERR_FILENO,": not found\n", 12);
	/*exit(errno);*/
	exit(127);
}

/**
 * print_builtin_error - Prints error for buitin function
 * @msg: Error message
*/
void print_builtin_error(char *msg)
{
	int len = _strlen(msg);

	write(STDERR_FILENO, msg, len);
	set_process_exit_code(1);
}
