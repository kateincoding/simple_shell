#include "shell.h"

/**
 * dispatch_error - Dispatches an error
 * @msg: Message to print as error
*/
void dispatch_error(char *msg)
{
	perror(msg);
	exit(*process_exit_code());
}
