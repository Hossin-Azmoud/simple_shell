#include "_simple_shell.h"

void err_report(const char *err, int line)
{
	fprintf(stderr, "[ERROR] %s:%d %s", __FILE__, line, err);
	exit(1);
}

int match(const char *pattern, const char *text)
{
	int matched = 0;
	char prev;

	if (pattern == NULL && text == NULL)
		return (-1);
	
	if (pattern == NULL || text == NULL)
		return (0);
	
	while (*pattern && *text) {
		switch(*pattern) {
			case '?': {
				pattern++;
				text++;
			} break;
			case '*': {
				if (match(pattern + 1, text)) return (1);
				text++;
			} break;
			case '[': {
				prev = *pattern;
				matched |=	prev == *text;
				pattern++;

				
				while (*pattern != ']' && *pattern) {
					if (*pattern == '-') {
						/* range was found! */
						pattern++;
						if (*pattern && *pattern != ']') {
							matched |= prev <= *text && *text <= *pattern;
							prev = *pattern;
							pattern++;
							continue;	
						}
						if (*pattern == ']')
							err_report("range pattern ended with 0 or ]", __LINE__);
					}

					matched |= *pattern == *text;
					pattern++;
				}

				if (*pattern != ']') {
					err_report("unclosed bracket inside pattern.", __LINE__);
				}

				if (!matched) return (0);
				pattern++;
				text++;
			} break;
			default: {
				if (*pattern == *text) {
					pattern++;
					text++;
				} else {
					return false;
				}
			};
		}
	}

	if (*text == 0) {
		while (*pattern == '*') pattern++;
		return (*pattern == 0);
	}
	
	return (1);
}

void check(const char *p, const char *t)
{
	printf("%5s <==> %5s => %s\n", p, t, match(p, t) ? "true" : "false");
}

int main2()
{
	check("La?", "Lax");
	check("La*", "Laxxxxxxxxxxxxa");
	check("La*a", "Laxxxxxxxxxxxxb");
	check("[a-c]", "d");

	return (0);
}

/**
* main - entry point.
* Return: always 0.
*/
int main(void)
{
	init_environment();
	start_shell();
	uinit_environment();
	return (get_status());
}
