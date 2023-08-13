#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H
#define EXIT_SUCCESS 0
#define SHELL_HEADER "Shell@"
#define INTRPT  -20
#define ENV_MAX 255
/* #define SEQ_START_BYTE '\x1b' for handling keys.. */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <fcntl.h> /* Definition of AT_* constants */
#include <unistd.h>

typedef struct map_s
{
	char **keys;
	char **values;
	char **all;
	int size;
	int cap;
} map_t;

#endif /* SIMPLE_SHELL_H */
