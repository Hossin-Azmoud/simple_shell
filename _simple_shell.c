#include "_simple_shell.h"
volatile sig_atomic_t got_interrupted = 0;
void handle_signal(int signal)
{
    if (signal == SIGINT)
	{
        got_interrupted = 1;
    }
}


void print_2d(char **Array)
{
	int it = 0;
	
	if (Array == NULL)
		return;
	
	while (Array[it])
	{
		puts(Array[it]);
		it++;
	}
}

void start_shell()
{
	int nread = 0;
	do {
		nread = *((int *)reader(READ));
		if (nread <= 1)
		{
			reader(FREE);
			if (nread == 1)
			{
				inc_line_index();
				continue;
			}

			if (nread == -1 || nread == INTRPT)
				break;
		}
		
		if (nread > 0)
		{
			reader(TOKENIZE);
			_exec();
		}
		
		reader(FREE);
		inc_line_index();
	} while (nread >= 0);
}

void *shell_atoi(char *ascii)
{
	int *r;
	int it;
	int unit;
	int tmp;

	if (ascii == NULL)
		return NULL;

	r = malloc(sizeof(int)); 
	tmp  = 0;
	unit = 1;
	it   = (strlen(ascii) - 1);

	while (it >= 0)
	{
		if (it == 0)
		{
			if (ascii[it] == '-')
			{
				tmp *= (-1);
				*r = tmp;
				return (r);
			}


			if (ascii[it] >= '0' && ascii[it] <= '9')
			{
				tmp += ((int)(ascii[it] - '0')) * unit;
				*r = tmp;
				return (r);
			}

			free(r);
			return (NULL);
		}

		if (ascii[it] >= '0' && ascii[it] <= '9')
		{
			tmp += ((int)(ascii[it] - '0')) * unit;
			unit *= 10;
			it--;
			continue;
		}

		free(r);
		return NULL;
	}

	*r = tmp;
	return (r);
}
/*
char *strtok(char *s, const char delim)
{
	static char **tok;
	static int internal_it;
	int i = 0, j = 0;

	if (s == NULL)
	{
		if (tok[internal_it] != NULL)
			return tok[internal_it++];

		return NULL;
	}

	internal_it = 0;
	while (*(s++) != 0)
	{
		for(;*(delim+j) != 0;)
		{
			if (*(s) != *())
		}
	}

	if ()
}
*/
