#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H
#define EXIT_SUCCESS 0
#define SHELL_HEADER "SHELL -> "
#define INTRPT_CODE  -20
#define SEQ_START_BYTE '\x1b'
#define BUILTINS_MAX_SIZE 32
#define ENV_MAX 255
#define DELIM " \t\n\r"
#define CLEAR_BYTES "\033[2J"
#define ROOT "/"

/* #define SEQ_START_BYTE '\x1b' for handling keys.. */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <fcntl.h>    /* Definition of AT_* constants */
#include <unistd.h>

/* enumerations */
typedef enum shell_state_action_e {
	INIT_STATE,
	INCR_INDEX,
	GET_INDEX,
	SET_STATUS,
	GET_STATUS
} shell_state_action_t;

typedef enum builtins_action_e {
	GET_BUILTN,
	INIT_BUILTN,
	SET_BUILTN
} builtins_action_t;

typedef enum reader_action_e
{
	READ,
	TOKENIZE,
	FREE,
	GET_TOKENS
} reader_action_t;

typedef enum env_action_e
{
	PRINT_ENV,
	INIT_ENV,
	SET_ENTRY,
	GET_VALUE,
	GET_KEYS,
	GET_MAP,
	DELETE_ENTRY,
	CLEAR_ENV
} env_action_t;


typedef enum path_action_e
{
	PRINT_PATH,
	INIT_PATH,
	FIND_CMD,
	CLEAR_PATH
} path_action_t;

/* STRUCTURES */
typedef struct map_s
{
	char **keys;
	char **values;
	char **all;
	int size;
	int cap;
} map_t;

typedef struct input_buffer_s
{
	char *buff;
	char **tokens;
	int size;
} input_buffer_t;

typedef struct builtin_func_s {
	char name[32];
	void (*f)();
} builtin_func_t;

typedef struct shell_state_s {
	int latest_status;
	int line_idx;
	char *c_line;
	char **c_line_toks;
} shell_state_t;

int   _strcmp(char *s1, char *s2);
int   _strlen(char *s);
int   _strlen2d(char **array);
int   _fputs(char *s, int fd);
int   _putchar(char c);
int   _puts(char *s);
int   _getline(char **buff, size_t *size, int fd);
void  prompt_user();
void  free_2d(char **Array);
void  free_n2d(char **Array, int n);
void  print_2d(char **Array);
void  terminate_incoming_str(char *s, int *size);
int   trim(char **s);
char  **split_by_delim(char *buffer, char *delim);
char  **parse_command(char *buff);
char  *_getpath();
char  **get_tokenized_path();
void  _exec();
char  *get_value(const map_t *m, char *key);
void  set_value(map_t *m, char *key, char *value);
map_t *create_map(size_t size);
void  distroy_map(map_t *m);
void  append_entry(map_t *m, char *entry, char *key, char *value);
void  map_cpy(map_t *m, char **src);

/* PATH MANAGER */

void path_manager(path_action_t action, char **cmd_loc, int *res);
void find_cmd(char **cmd_loc, char **paths, int *result_);
void init_path_manager();
void resolve_command_path(char **old_path, int *res);
void print_path();
void release_path();

/* ENV MANAGER */
void  *env_manager(env_action_t action, char *key, char *value);
void  init_env_manager();
void  print_env();
void  print_env_internal(map_t *m);
map_t *get_envp_map();
char  *_get_env(char *key);
void  _set_env(char *key, char *value);
void  release_env_();

/* SHELL_STATE_MANAGER */
int  shell_state_manager(shell_state_action_t action, int payload);
int  get_line_index();
void inc_line_index();
int  get_status();
void set_status(int payload);
void init_state_manager();

/* builtins funcs and builtins manager..*/
builtin_func_t *builtins_manager(builtins_action_t action, char *name, void (*f)());
void init_builtins();
void set_builtin(char *name, void (*f)());
builtin_func_t *get_builtin(char *name);

/* input managing. */
input_buffer_t *alloc_input_t();
void *reader(reader_action_t action);

/* init and deinit. */
void init_environment();
void uinit_environment();

/* main */
void start_shell();

/* builtins */
void __exit_shell();
void change_dir();
void clear();

/* other */
void *shell_atoi(char *ascii);
void handle_signal(int signal);
int _sig_int(int sig);

#endif /* SIMPLE_SHELL_H */
