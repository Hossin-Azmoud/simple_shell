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
	in->ctx          = NONE;
	in->input_size   = 0;
	in->commands_sz  = 0;
	in->command_idx  = 0;

	return (in);
}
/**
 * read_command - function to read and prepare a command/set of commands.
 * Return: pointer to input_buffer_t struct.
 */
static input_buffer_t *read_command()
{
	size_t cap;
	input_buffer_t *uinput = NULL;

	if (isatty(STDIN_FILENO) == 1)
		prompt_user();

	uinput = alloc_input_t();
	uinput->input_size = _getline(&(uinput->buff), &cap, STDIN_FILENO);

	if (uinput->input_size >= 1)
	{
		uinput->input_size = trim(&(uinput->buff));
		uinput->buff       = exclude_comments(uinput->buff);
		uinput->input_size = _strlen(uinput->buff);
		uinput->ctx        = check_context(uinput->buff);
		uinput->commands   = context_based_split(uinput->ctx, uinput->buff);
		uinput->commands_sz  = _strlen2d(uinput->commands);
		uinput->command_idx  = 0;
	}

	return (uinput);
}

static void free_input_t(input_buffer_t *uinput)
{
	free(uinput->buff);
	free_2d(uinput->tokens);

	if (uinput->commands != NULL)
		free_2d(uinput->commands);

	free(uinput);
}

/**
 * reader - function that read the input
 * @action: check the argument
 * Return: to the condition
 */
void *reader(reader_action_t action)
{
	static input_buffer_t *in = { 0 };

	switch (action)
	{
		case GET_TOKENS: {
			return (in->tokens);
		} break;
		case READ: {
			in = read_command();
			return (&(in->input_size));
		} break;
		case TOKENIZE: {

			if (in->tokens != NULL)
			{
				free_2d(in->tokens);
				in->tokens = NULL;
			}

			if (in->buff != NULL && (in->input_size) >= 1)
			{
				if (in->ctx == NONE)
				{
					in->tokens = split_by_delim((in->buff), DELIM);
				} else
				{
					if (*(in->commands + in->command_idx) != NULL)
					{
						in->tokens = split_by_delim(*(in->commands + in->command_idx), DELIM);
						in->command_idx++;
					}
				}
			}
		} break;
		case GET_ALL: {
			return (in);
		} break;
		case FREE: {
			if (in != NULL)
			{
				free_input_t(in);
			}
			in = NULL;
		} break;
		default: {
		} break;
	}
	return (NULL);
}
