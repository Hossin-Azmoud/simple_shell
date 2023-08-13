#include "_simple_shell.h"

char **parse_command(char *buff)
{		
	return split_by_delim(buff, " \t\n");
}
