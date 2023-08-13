#include "_simple_shell.h"

void prompt_user()
{
	_puts(SHELL_HEADER);
}

int _getline(char **buff, size_t *size, int fd)
{
	int    consume  = 1;
	size_t it       = 0;
	int    nread    = 0;
	char c;
	struct sigaction sa;
	
	*size = 16;
	*buff = malloc(*size);
	/* Interruption logic.. */
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

	while(consume)
	{
		if (it == *size - 2)
		{
			*size *= 2;
			*buff = realloc(*buff, *size);
			if (buff == NULL)
			{
				fprintf(stderr, "realloc failed to reallocate new buffer\n");
				return -1;
			}
		}

		if ((nread = read(fd, &c, 1)) <= 0) break;
		/* reallocate memory.*/	
		switch(c)
		{
			case '\n': {
				(*buff)[it] = 0;
				consume = 0;
				it++;
			} break;
			case '\r': {
			} break;
			case EOF: {
				return -1;
			} break;
			case SEQ_START_BYTE: {
				printf("started sequence..\n");
			} break;
			default: {
				(*buff)[it] = c;
				it++;
			} break;
		}
	}
	
	if (it == 0 && nread == 0)
		return -1;

	if (got_interrupted)
		return INTRPT;

	return it;
}
