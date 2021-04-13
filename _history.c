#include "shell.h"

/* Global variables */
static int no_init_history;
static list_t *history_head;
static list_t *last_cmd;

/**
 * get_history_addrss - Return the address oof history head
 *
 * Return: Address of history head
*/
list_t **get_history_addrss()
{
	if (no_init_history == 1)
	{
		history_head = NULL;
		last_cmd = NULL;
		no_init_history = 0;
	}

	return (&history_head);
}

/**
 * get_last_cmd_addrss - Return the address oof history head
 *
 * Return: Address of last entered command
*/
list_t **get_last_cmd_addrss()
{
	if (no_init_history == 1)
	{
		history_head = NULL;
		last_cmd = NULL;
		no_init_history = 0;
	}

	return (&last_cmd);
}

/**
 * _history - Prints the all the commands entered by the user
 *
 * Return: 1 on success
*/
int _history(void)
{
	list_t *curr;
	char *str_num;
	int count = 0, len;

	for (curr = *get_history_addrss(); curr != NULL; curr = curr->next)
	{
		str_num = num_to_str(count++);
		len = strlen(str_num);
		write(STDOUT_FILENO, str_num, len);
		write(STDOUT_FILENO, "  ", 2);
		write(STDOUT_FILENO, curr->str, curr->len);
	}

	return (1);
}

/**
 * handle_history - Adds a command to the history
 * @buff: User's input
*/
void handle_history(char *buff)
{
	/* Only adds a command if is different from the previous one */
	if (last_cmd == NULL || strcmp(last_cmd->str, buff) != 0)
		last_cmd = add_node_end(&history_head, buff);
}

void free_history(void)
{
	printf("freeing history\n");
	free_list(history_head);
}
