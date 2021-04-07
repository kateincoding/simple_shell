#ifndef __SHELL_H
#define __SHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* builtins */
void env(void);

/* own implementations */
char *_strtok(char *str, char *delimiter);
int _getline(char **buffer, size_t *buf_size, FILE *restrict stream);

/* Memory management */
void *allocate_memory(unsigned int bytes);
char *duplicate_string(char *str);
void free_dbl_ptr(char **dbl_ptr);


#endif /* __SHELL_H */