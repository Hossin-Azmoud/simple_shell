#include "_simple_shell.h"
/**
 * alloc_input_t - function allocate the memory to the inputs
 * Return: the inputs with the allocated memory
 */
static input_buffer_t *alloc_input_t(void)
{
	input_buffer_t *in = malloc(sizeof(input_buffer_t));

	if (in == NULL)
	{
		fprintf(stderr, "Failed to allocate memory.\n");
		return (NULL);
	}

	in->buff         = NULL;
	in->tokens       = NULL;
	in->commands     = NULL;
	in->ctx          = NULL;
	in->input_size   = 0;
	in->commands_sz  = 0;
	in->command_idx  = 0;

	return (in);
}
/**
 * read_command - function to read and prepare a command/set of commands.
 * @fd: file to read from.
 * Return: pointer to input_buffer_t struct.
 */
static input_buffer_t *read_command(int fd)
{
	size_t cap;
	input_buffer_t *uinput = NULL;

	if (isatty(fd) == 1)
		prompt_user();

	uinput = alloc_input_t();
	uinput->input_size = _getline(&(uinput->buff), &cap, fd);
	if (uinput->input_size >= 1)
	{
		uinput->input_size   = trim(&(uinput->buff));
		uinput->buff         = exclude_comments(uinput->buff);
		uinput->input_size   = _strlen(uinput->buff);
		uinput->ctx          = check_context(uinput->buff);
		uinput->commands     = split_by_delim(uinput->buff,  ";&&||");
		uinput->commands_sz  = _strlen2d(uinput->commands);
		uinput->command_idx  = 0;
	}

	return (uinput);
}

/**
 * free_input_t - a function to free an input_buffer_t allocated space.
 * @uinput: structure to free.
 * Return: void
 */
static void free_input_t(input_buffer_t *uinput)
{
	free(uinput->buff);
	free_2d(uinput->tokens);

	if (uinput->commands != NULL)
		free_2d(uinput->commands);
	if (uinput->ctx != NULL)
		free(uinput->ctx);

	free(uinput);
}
/**
 * tokenize - function that tokenizes the input of the function.
 * @uinput: user input buffer.
 * Return: tokens of the current command
 */
static char **tokenize(input_buffer_t *uinput)
{
	if (uinput->tokens != NULL)
	{
		free_2d(uinput->tokens);
		uinput->tokens = NULL;
	}

	if (uinput->buff != NULL && (uinput->input_size) >= 1)
	{
		if (uinput->ctx == NULL)
		{
			uinput->tokens = split_by_delim((uinput->buff), DELIM);
		}
		else if (*(uinput->commands + uinput->command_idx) != NULL)
		{
			uinput->tokens = split_by_delim(
				*(uinput->commands + uinput->command_idx),
				DELIM
			);
			uinput->command_idx++;
		}
	}

	uinput->tokens = check_variables(uinput->tokens);
	return (uinput->tokens);
}

/**
 * reader - function that read the input
 * @action: the action that the reader will do.
 * @fd_:    the fd to the file that will be consumed.
 * Return: to the condition
 */
void *reader(reader_action_t action, int fd_)
{
	static input_buffer_t *in = { 0 };
	static int fd = STDIN_FILENO;

	switch (action)
	{
		case SET_FD: {
			fd = fd_;
		} break;

		case NEXT_CMD: {
			in->command_idx++;
		} break;
		case GET_TOKENS: {
			return (in->tokens);
		} break;
		case READ: {
			in = read_command(fd);
			return (&(in->input_size));
		} break;
		case TOKENIZE: {
			return (tokenize(in));
		} break;
		case GET_ALL: {
			return (in);
		} break;
		case FREE: {
			if (in != NULL)
				free_input_t(in);
			in = NULL;
		} break;
		default: {
		} break;
	}
	return (NULL);
}
