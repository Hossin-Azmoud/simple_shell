#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H
#define EXIT_SUCCESS 0
#define SHELL_HEADER "SHELL -> "
#define INTRPT_CODE  -20
#define SEQ_START_BYTE ('\x1b')
#define BUILTINS_MAX_SIZE 32
#define ENV_MAX 255
#define DELIM " \t\n\r"
#define CLEAR_BYTES ("\033[2J")
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

/**
 * enum shell_state_action_e - possible shell state actions.
 * @INIT_STATE: initialise the status.
 * @INCR_INDEX: increment line index.
 * @GET_INDEX:  get line index.
 * @SET_STATUS: set status.
 * @GET_STATUS: get status.
 */
typedef enum shell_state_action_e
{
	INIT_STATE,
	INCR_INDEX,
	GET_INDEX,
	SET_STATUS,
	GET_STATUS
} shell_state_action_t;

/**
 * enum builtins_action_e - builtin manager actions.
 * @GET_BUILTN:  get a builtin function by name.
 * @INIT_BUILTN: initialise builtin functions buffer.
 * @SET_BUILTN:  set a builtin.
 */
typedef enum builtins_action_e
{
	GET_BUILTN,
	INIT_BUILTN,
	SET_BUILTN
} builtins_action_t;

/**
 * enum reader_action_e - possible reader actions (for user input.)
 * @READ:      Read user input.
 * @TOKENIZE:  organize and parse user input.
 * @FREE:      free user input and tokenization buffer.
 * @GET_TOKENS: get tokenized input.
 */
typedef enum reader_action_e
{
	READ,
	TOKENIZE,
	FREE,
	GET_TOKENS
} reader_action_t;

/**
 * enum env_action_e - possible environment actions
 * @PRINT_ENV:     print the environment.
 * @INIT_ENV:      initialise the environment.
 * @SET_ENTRY:     set an entry in the env storage.
 * @GET_VALUE:     get a value from the env storage.
 * @GET_KEYS:      get keys from the env storage.
 * @GET_MAP:       get the map that stores (key, value) pairs.
 * @DELETE_ENTRY:  delete and entry from the storage.
 * @CLEAR_ENV:     clear/free the storage.
 */
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

/**
 * enum path_action_e - possible path actions.
 * @PRINT_PATH:  print the path.
 * @INIT_PATH:   initialise the path.
 * @FIND_CMD:    find a command in the path (which is not a suitable name).
 * @CLEAR_PATH : clear/free path.
*/
typedef enum path_action_e
{
	PRINT_PATH,
	INIT_PATH,
	FIND_CMD,
	CLEAR_PATH
} path_action_t;

/**
 * struct map_s - map that hold key, value pairs and an environment eq (all)
 * @keys:    an array of keys
 * @values:  an array of values
 * @all:     an array of entries
 * @size:    the size of the map
 * @cap:     the capacity of the map
 */
typedef struct map_s
{
	char **keys;
	char **values;
	char **all;
	int size;
	int cap;
} map_t;

/**
 * struct input_buffer_s - user input storage entity
 * @buff:   buffer to store raw input from user.
 * @tokens: 2d string array to store parsed/tokenized user input.
 * @size:   size of the raw buffer.
 */
typedef struct input_buffer_s
{
	char *buff;
	char **tokens;
	int size;
} input_buffer_t;

/**
 * struct builtin_func_s - shell builtin function type.
 * @name: function name to be used as a command.
 * @f:    the actual function
 */
typedef struct builtin_func_s
{
	char name[32];
	void (*f)();
} builtin_func_t;

/**
 * struct shell_state_s - shell state structure.
 * @latest_status: latest command status code.
 * @line_idx:      current line index.
 * @c_line:        current line input.
 * @c_line_toks:   current tokens
 */

typedef struct shell_state_s
{
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
void  prompt_user(void);
void  free_2d(char **Array);
void  free_n2d(char **Array, int n);
void  print_2d(char **Array);
void  terminate_incoming_str(char *s, int *size);
int   trim(char **s);
char  **split_by_delim(char *buffer, char *delim);
char  **parse_command(char *buff);
char  *_getpath(void);
char  **get_tokenized_path(void);
void  _exec(void);
char  *get_value(const map_t *m, char *key);
void  set_value(map_t *m, char *key, char *value);
map_t *create_map(size_t size);
void  distroy_map(map_t *m);
void  append_entry(map_t *m, char *entry, char *key, char *value);
void  map_cpy(map_t *m, char **src);

/* PATH MANAGER */

void path_manager(path_action_t action, char **cmd_loc, int *res);
void find_cmd(char **cmd_loc, char **paths, int *result_);
void init_path_manager(void);
void resolve_command_path(char **old_path, int *res);
void print_path(void);
void release_path(void);

/* ENV MANAGER */
void  *env_manager(env_action_t action, char *key, char *value);
void  init_env_manager(void);
void  print_env(void);
map_t *get_envp_map(void);
char  *_get_env(char *key);
void  _set_env(char *key, char *value);
void  release_env_(void);

/* SHELL_STATE_MANAGER */
int  shell_state_manager(shell_state_action_t action, int payload);
int  get_line_index(void);
void inc_line_index(void);
int  get_status(void);
void set_status(int payload);
void init_state_manager(void);

/* builtins funcs and builtins manager..*/
builtin_func_t *
builtins_manager(builtins_action_t action, char *name, void (*f)(void));
void init_builtins(void);
void set_builtin(char *name, void (*f)(void));
builtin_func_t *get_builtin(char *name);

/* input managing. */
input_buffer_t *alloc_input_t(void);
void *reader(reader_action_t action);

/* init and deinit. */
void init_environment(void);
void uinit_environment(void);

/* main */
void start_shell(void);

/* builtins */
void __exit_shell(void);
void change_dir(void);
void clear(void);

/* other */
void *shell_atoi(char *ascii);
void handle_signal(int signal);
int _sig_int(int sig);

#endif /* SIMPLE_SHELL_H */
