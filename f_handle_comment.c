#include "shell.h"

/**
 * handle_comment - deletes a comment from the buffer
 * @str_input: User's input
 *
 * Return: pointer to string
 */
char *handle_comment(char *str_input)
{
	char *without_comments = str_input;

	while(str_input && *str_input)
    {
		if (*str_input == '#' && *(str_input - 1) == ' ')
		{
			*(str_input - 1) = '\n';
			*str_input = '\0';
			break;
		}
        str_input++;
    }
	return (without_comments);
}
