#ifndef __SHELL_H
#define __SHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* Special functions */
void __attribute__((constructor)) build_dynamic_environ(void);
void __attribute__((destructor)) free_dynamic_environ(void);

/* builtins */
void env(void);
int _setenv(char *name, char *value);
int _unsetenv(char *name);

/* builtins utils */
int validate_env_name(char *name);
int is_valid_env_var_name(char *name);
int get_env_index(char *name);

/* own implementations */
char *_strtok(char *str, char *delimiter);
int _getline(char **buffer, size_t *buf_size, FILE *stream);

/* Command handlers */
void handle_PATH(char **commands);
char *getpath(char *dir, char *filename);
char **parse_user_input(char *str_input);
int count_args(char *str_input, char *delimiter);

/* Memory management */
void *allocate_memory(unsigned int bytes);
char *duplicate_string(char *str);
void free_dbl_ptr(char **dbl_ptr);

/* handle_builtins */
int handle_builtins(char **commands);

/* handle_enter */
int handle_enter(char **commands);
/* handle comments in input */
char *handle_comment(char *str_input);

/* Exit handlers */
int handle_exit(char *buff, char **commands);
int get_exit_status(char *buff);
void print_Illegal_exit_status(char *status_str);

/* Error handlers */
void dispatch_error(char *msg, int status);

#endif /* __SHELL_H */
