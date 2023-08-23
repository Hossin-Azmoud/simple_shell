#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H
#define COMMAND_NOT_FOUND_STATUS 127
#define EXIT_SUCCESS 0
#define SHELL_HEADER "SHELL -> "
#define INTRPT_CODE  -20
#define SEQ_START_BYTE ('\x1b')
#define BUILTINS_MAX_SIZE 32
#define ENV_MAX 255
#define CTX_MAX 200
#define DELIM " \t\n\r"
#define CLEAR_BYTES ("\033[2J")
#define ROOT "/"
#define PATH_MAX 4096
/* #define SEQ_START_BYTE '\x1b' for handling keys.. */


#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
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
 * @SET_SHELL_NAME: set the shell-s name
 * @GET_SHELL_NAME: get the shell-s name
 */
typedef enum shell_state_action_e
{
	INIT_STATE,
	INCR_INDEX,
	GET_INDEX,
	SET_STATUS,
	GET_STATUS,
	SET_SHELL_NAME,
	GET_SHELL_NAME
} shell_state_action_t;

/**
 * enum ctx_e - shell commmand context.
 * @AND: and which refers to '&&'
 * @OR:  or that refers to '||'
 * @JOIN: join that refers to ';'
 * @END: refers to the ending context.
 */
typedef enum ctx_e
{
	AND,
	JOIN,
	OR,
	END
} ctx_t;

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
 * @READ:        Read user input.
 * @TOKENIZE:    organize and parse user input.
 * @FREE:        free user input and tokenization buffer.
 * @GET_TOKENS:  get tokenized input.
 * @GET_ALL: gets the input struct.
 * @NEXT_CMD: goto the next command.
 */
typedef enum reader_action_e
{
	READ,
	TOKENIZE,
	FREE,
	GET_TOKENS,
	GET_ALL,
	NEXT_CMD
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
 * @input_size:   size of the raw buffer.
 * @commands: commands that will be toked based on context.
 * @ctx: command context.
 * @command_idx: current command index
 * @commands_sz: amount of current passed commands.
 */
typedef struct input_buffer_s
{
	char   *buff;
	char   **tokens;
	char   **commands;
	int    input_size;
	size_t commands_sz;
	size_t command_idx;
	ctx_t  *ctx;
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
 * @shell_name:    current shell name.
 */
typedef struct shell_state_s
{
	int latest_status;
	int line_idx;
	char *c_line;
	char **c_line_toks;
	char shell_name[PATH_MAX];
} shell_state_t;

/**
 * struct meta_data_s - shell meta information.
 * @uname:  user name.
 * @pwd:    current working directory.
 * @prompt: shell pro max.
 */
typedef struct meta_data_s
{
	char *uname;
	char *pwd;
	char *prompt;
} meta_data_t;
/* string */
char *_strdup(char *s);
char *_strcpy(char *dest, char *src);
int   _strcmp(char *s1, char *s2);
int   _strlen(char *s);
int   _strlen2d(char **array);
char *_strcat(char *dst, char *src);
char  *_join_with_path(char *path, char *file_name);
void  terminate_incoming_str(char *s, int *size);
int   trim(char **s);

/* stdio */
int   _fputs(char *s, int fd);
int   _putchar(char c);
int   _puts(char *s);
int   _getline(char **buff, size_t *size, int fd);

/* my standard. */
char *__itoa(int n);
char  *get_shell_header(void);
void  prompt_user(void);
void  free_2d(char **Array);
void  free_n2d(char **Array, int n);
void  print_2d(char **Array);
char  **split_by_delim(char *buffer, char *delim);
char  **parse_command(char *buff);
char  *_getpath(void);
char  **get_tokenized_path(void);
void  _exec(void);
void  *shell_atoi(char *ascii);
void  handle_signal(int signal);
int   _sig_int(int sig);
char *exclude_comments(char *buff);
char **check_variables(char **tokens);

/* Map */
map_t *create_map(size_t size);
void  distroy_map(map_t *m);
void  append_entry(map_t *m, char *entry, char *key, char *value);
void  map_cpy(map_t *m, char **src);
char  *get_value(const map_t *m, char *key);
void  set_value(map_t *m, char *key, char *value);
int   find_entry_index(map_t *m, char *k);
map_t *delete_entry(map_t *m, char *k);

/* PATH MANAGER */
void path_manager(path_action_t action, char **cmd_loc, int *res);
void find_cmd(char **cmd_loc, char **paths, int *result_);
void init_path_manager(void);
void print_path(void);
void distroy_path(void);

/* ENV MANAGER */
void  *env_manager(env_action_t action, char *key, char *value);
void  init_env_manager(void);
void  print_env(void);
map_t *get_envp_map(void);
char  *_get_env(char *key);
void  _set_env(char *key, char *value);
void  distroy_env_(void);

/* SHELL_STATE_MANAGER */
void *
shell_state_manager(shell_state_action_t action, int payload, char **name);
int  get_line_index(void);
void inc_line_index(void);
int  get_status(void);
void set_status(int payload);
void init_state_manager(void);
char *get_shell_name(void);
void set_shell_name(char **name);

builtin_func_t *
builtins_manager(builtins_action_t action, char *name, void (*f)(void));
void init_builtins(void);
void set_builtin(char *name, void (*f)(void));
builtin_func_t *get_builtin(char *name);

/* input managing. */
void *reader(reader_action_t action);

/* init and deinit. */
void init_environment(char *shell_);
void uinit_environment(void);
/* context */
ctx_t *check_context(char *buff);
char **context_based_split(ctx_t context, char *buff);
char *ctx_str(ctx_t context);
/* main */
void start_shell(void);

/* builtins */
void __exit_shell(void);
void change_dir(void);
void clear(void);
void unset__env(void);
void set__env(void);

#endif /* SIMPLE_SHELL_H */
