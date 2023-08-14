#include "_simple_shell.h"

input_buffer_t *alloc_input_t()
{

	input_buffer_t *in = malloc(sizeof(input_buffer_t));

	if (in == NULL)
	{
		fprintf(stderr, "Failed to allocate mem. user input will be ignored for now until memory is ready.\n");
		return (NULL);
	}

	in->buff   = NULL;
	in->tokens = NULL;
	in->size   = 0;
	return (in);
}

void *reader(reader_action_t action)
{
	static input_buffer_t *in = { 0 };
	static size_t cap;
	
	switch(action)
	{
		case GET_TOKENS: {
			return (in->tokens);
		} break;
		case READ: {
			if (isatty(STDIN_FILENO) == 1)
				prompt_user();

			in = alloc_input_t();
			in->size = _getline(&(in->buff), &cap, STDIN_FILENO);
				
			if (in->size >= 1)
				in->size = trim(&(in->buff));

			return &(in->size);
		} break;
		case TOKENIZE: {
			if (in->buff != NULL && (in->size) >= 1)
				in->tokens = split_by_delim((in->buff), DELIM);
		} break;
		case FREE: {
			if (in != NULL)
			{
				free(in->buff);
				free_2d(in->tokens);
				free(in);
				in = NULL;
			}
		} break;
		default: {
			return (NULL);
		} break;
	}

	return (NULL);
}
