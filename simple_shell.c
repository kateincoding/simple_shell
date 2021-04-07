#include "shell.h"

/* Command handlers */
char **parse_user_input(char *str_input);
int count_args(char *str_input, char *delimiter);


/* Error handlers */
void dispatch_error(char *msg, int status);

void handle_PATH(char **commands);
char *getpath(char *dir, char *filename);

int handle_builtins(char *command);
int handle_enter(char **commands);

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
		/* Print console symbol */
		printf("#cisfun$ ");
		fflush(stdout);
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

/**
 * parse_user_input - Buidls an array of strings as arguments
 * @str_input: Command input given by the user
 *
 * Return: Array of strings
*/
char **parse_user_input(char *str_input)
{
	int i, args_count = 0;
	char **args;
	char *token, *tkn_ptr, *delimiter = " ";
	char *str_copy;

	if (str_input == NULL)
		dispatch_error("Error while parsing the command\n", 100);

	/* Count the number of arguments present in the input */
	args_count = count_args(str_input, delimiter);
	/* Allocate memory to hold eaach argument as a string */
	args = allocate_memory(sizeof(char *) * (args_count + 1));
	/* Store each argument as a string */
	str_copy = duplicate_string(str_input);
	tkn_ptr = str_copy;
	for (i = 0; i < args_count; i++)
	{
		token = _strtok(tkn_ptr, delimiter);
		if (token == NULL)
			break;
		tkn_ptr = NULL;
		/* store command as single string */
		args[i] = duplicate_string(token);
	}
	/* set the last element of array of arguments to NULL */
	args[i] = NULL;

	free(str_copy);

	return (args);
}

/**
 * count_args - Counts the number of arguments in a command string
 * @str_input: Command as a string
 * @delimiter: Delimiter by wich to separate the args
 *
 * Return: Number of arguments present in str_input
*/
int count_args(char *str_input, char *delimiter)
{
	char *tkn, *tkn_ptr;
	int count = 0;
	char *str_copy = duplicate_string(str_input);

	tkn_ptr = str_copy;
	while ((tkn = _strtok(tkn_ptr, delimiter)) != NULL)
	{
		count++;
		tkn_ptr = NULL;
	}

	free(str_copy);

	return (count);
}

/**
 * dispatch_error - Dispatches an error
 * @msg: Message to print as error
 * @status: Integer representing the error code
*/
void dispatch_error(char *msg, int status)
{
	perror(msg);
	exit(status);
}

/**
 * handle_PATH - Checks if the command to execute could be found in PATH's dirs
 * @commands: Array of strings containing the command and args
*/
void handle_PATH(char **commands)
{
	char *path_dirs, *path;
	char *tkn, *tkn_ptr;
	char *str_copy;

	if (
		commands == NULL || commands[0] == NULL ||
		commands[0][0] == '\0' || commands[0][0] == '/'
	)
		return;

	path_dirs = getenv("PATH");
	if (path_dirs == NULL)
		dispatch_error("Error", 100);

	str_copy = duplicate_string(path_dirs);
	tkn_ptr = str_copy;
	while (1)
	{
		tkn = _strtok(tkn_ptr, ":");
		if (tkn == NULL)
			break;
		tkn_ptr = NULL;

		path = getpath(tkn, commands[0]);
		if (access(path, F_OK) != -1)
		{
			free(commands[0]);
			commands[0] = path;
			break;
		}
		free(path);
	}

	free(str_copy);
}

/**
 * getpath - Creates a string representing a full path to file
 * @dir: String representing a directory path
 * @filename: Name of the file we are looking for
 *
 * Return: String as a full path to "filename"
*/
char *getpath(char *dir, char *filename)
{
	int dir_len = strlen(dir);
	int filename_len = strlen(filename);
	char *path;

	path = allocate_memory(sizeof(char *) * (dir_len + filename_len + 2));

	strcpy(path, dir);
	strcat(path, "/");
	strncat(path, filename, filename_len + 1);

	return (path);
}

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



/**
 * handle_enter - Check if no command was entered
 * @buff: User's input
 *
 * Return: 1 if no command was entered(just spaces and ENTER), 0 otherwise
*/
int handle_enter(char **commands)
{
	if (commands[0] == NULL || strcmp(commands[0], "\n") == 0)
		return (1);

	return (0);
}
