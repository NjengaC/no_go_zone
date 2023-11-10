#include "shell.h"


/**
 * handle_sigint - Functions that handles CTRL C.
 * @signum: represent the single number that triggers the signal.
 * Return: void.
 */

void handle_sigint(int signum __attribute__((unused)))
{
	write(STDOUT_FILENO, "\n", 1);
	if (isatty(STDIN_FILENO))
	{
		Write("$");
		fflush(stdout);
	}
}

/**
 *main - the entry point
 *@ac: arguement count
 *@argv: argurment vector
 *Return: the status of the exectutions
 */

int main(int ac __attribute__ ((unused)), char **argv)
{
	char *line;
	int mode = 1;
	SHELL eshell;

	eshell.av = argv;
	fill_eshell(&eshell);

	if (argv[1])
	{
		handle_file(&eshell);
	}
	signal(SIGINT, handle_sigint);

	while (mode)
	{
		line = NULL;
		eshell.loop_count++;

		if (isatty(STDIN_FILENO))
			Write("$> ");

		line = Getline();
		line = global_var(line, &eshell);

		if (line[0] == '\0' || !line)
		{
			continue;
		}

		if (Syntax(line, &eshell) == -1)
		{
			free(line);
			continue;
		}

		mode = source(&eshell, line);
		free(line);
		line = NULL;
	}
	return (eshell.status);
}


/**
 * fill_eshell - Functions that fill the structure members with respective
 * content.
 * @eshell: structure to be filled.
 * Return: Void.
 */

void fill_eshell(SHELL *eshell)
{
	eshell->pid = getpid();
	eshell->status = 0;
	eshell->_environ = NULL;
	eshell->loop_count = 0;
}


/**
 * Write - Function that writes content given to the POSIX.
 * @input: Pointer to content to be written out.
 * Return: Void.
 */

void Write(char *input)
{
	int i;

	for (i = 0; input[i]; i++)
		;

	write(STDOUT_FILENO, input, i);
}
/**
 *seperator - determine which command should be executed next
 *@head: head of linked list
 *@line: tokenized command
 *Return: nothing
 */

void seperator(log **head, char *line)
{
	int i;
	log *current;
	char a;


	shuffle(line, 1);
	current = *head;

	for (i = 0; line[i]; i++)
	{
		a = line[i];

		if (a == '|')
		{
			current->sep = '|';
			current = current->next;
		}

		else if (a == '&')
		{
			current->sep = '&';
			current = current->next;
		}

		else if (a == ';')
		{
			current->sep = ';';
			current = current->next;
		}

	}

	shuffle(line, 2);
}
