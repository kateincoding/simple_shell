#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Command handlers */
char **parse_user_input_1(char *str_input);
int count_args_1(char *str_input, char *delimiter);
void execute_command_1(char **commands);
/* Utils */
void remove_new_line_char_1(char **args, int index);
/* Memory management */
void *allocate_memory_1(unsigned int bytes);
char *duplicate_string_1(char *str);
/* Error handlers */
void dispatch_error_1(char *msg, int status);

int main(int ac, char **av, char **env)
{
	int read;
	char *buff = NULL;
	size_t buff_len = 0;

	int child_pid;
	char **commands;

	while(1)
	{
		/* Print console symbol */
		printf("#cisfun$ ");
		/* Read commands from console */
		read = getline(&buff, &buff_len, stdin);
		if (read == EOF || strcmp(buff,"exit\n") == 0)
		{
			free(buff);
			exit(0);
		}

		/* Fork parent process to execute the command */
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error");
			exit(1);
		}
		/* Fork parent process to execute the command */
		else if (child_pid == 0)
		{
			/* execute command */
			commands = parse_user_input_1(buff);
			execve(commands[0], commands, env);
			/* handle errors */
			perror("Error");
			exit(1);
		}
		else
			wait (NULL);
	}

	/* Cleanup buffer memory */
	free(buff);

	return (0);
}

char **parse_user_input_1(char *str_input)
{
	int i, args_count = 0;
	char **args;
	char *token, *delimiter = " ";
	char *str_copy;

	if (str_input == NULL)
		dispatch_error_1("Error while parsing the command\n", 100);

	/* Count the number of arguments present in the input */
	args_count = count_args_1(str_input, delimiter);
	args_count = 1;
	/* Allocate memory to hold eaach argument as a string */
	args = allocate_memory_1((sizeof(char *) * (args_count + 1)));
	args[0] = str_input;
	remove_new_line_char_1(args, 0);
	args[1] = NULL;
	return (args);
	/* Store each argument as a string */
	str_copy = duplicate_string_1(str_input);
	for (i = 0; i < args_count; i++)
	{
		token = strtok(str_copy, delimiter);
		if (token == NULL)
			break;
		str_copy = NULL;
		/* store command as single string */
		args[i] = duplicate_string_1(token);
		/* Remove '\n' char from command */
		remove_new_line_char_1(args, i);
	}
	/* set the last element of array of arguments to NULL */
	args[i] = NULL;

	free(str_copy);

	return (args);
}

int count_args_1(char *str_input, char *delimiter)
{
	char *tkn;
	int count = 0;
	char *str_copy = duplicate_string_1(str_input);

	while((tkn = strtok(str_copy, delimiter)) != NULL)
	{
		count++;
		str_copy = NULL;
	}

	free(str_copy);

	return (count);
}

void *allocate_memory_1(unsigned int bytes)
{
	char *new_mem = malloc(bytes);

	if (new_mem == NULL)
		dispatch_error_1("Error while allocating memory\n", 100);

	return (new_mem);
}

/*
void execute_command_1(char **commands)
{
	logica de pipes y redirection
}
*/

void dispatch_error_1(char *msg, int status)
{
	perror(msg);
	exit(status);
}

char *duplicate_string_1(char *str)
{
	char *str_copy = strdup(str);

	if (str_copy == NULL)
		dispatch_error_1("Error while making copy of string", 100);

	return (str_copy);
}

/**
 * remove_new_line_char_1 - Replaces '\n' char with '\0'
 * @args: Array of commands
 * @index: Command index to be evaluated
 */
void remove_new_line_char_1(char **args, int index)
{
	int len = strlen(args[index]);

	if (len == 0)
		return;

	if (len == 1 && args[index][0] == '\n')
		args[index] = NULL;
	else if (args[index][len - 1] == '\n')
		args[index][len - 1] = '\0';
}