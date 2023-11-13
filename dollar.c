#include "shell.h"
/**
 *source - controls or parses the input
 *@shell: the main structure
 *@line: the input
 *Return: 0 incase of commad exit else 1
 */

int _source(SHELL *shell, char *line)
{
	log *head, *current;
	char *word, *copy;
	int result;

	head = NULL, copy = Strdup(line), word = strtok(copy, "|&;\n");

	while (word)
	{
		Log(&head, word), word = strtok(NULL, "|&;\n");
	}
	seperator(&head, line),	current = head;
	while (current)
	{
		shell->toks = tokenize(current->com, 1), env_extract(shell);
		if (!shell->toks)
		{
			continue;
		}
		result = handle_builtin_commands(shell);
		if (result == 1)
		{
			free(copy), Free_log(head), Frees(shell);
			return (0);
		}
		process(shell),	En_passant(shell, &current);
		if (current)
		{
			current = current->next;
		}
		Frees(shell);
	}
	free(copy), Free_log(head);
	return (1);
}

/**
 *shuffle - swap one of logcal operators for non printables and back
 *@line: input
 *@mode: 1 for swaping to non printable and 2 for the undo
 *Return: nothing
 */

void line_shuffler(char *line, int mode)
{
	int i;
	char a;

	if (mode == 1)
	{
		for (i = 0; line[i]; i++)
		{
			a = line[i];
			if (a == '|')
			{
				line[i] = 1, i++;
			}
			else if (a == '&')
			{
				line[i] = 2, i++;
			}
		}
	}

	else if (mode == 2)
	{
		for (i = 0; line[i]; i++)
		{
			a = line[i];
			if (a == 1)
			{
				line[i] = '|';
			}
			else if (a == 2)
			{
				line[i] = '&';
			}
		}
	}
}
/**
 *En_passant - control logical operator according to exit status
 *@shell: main structure
 *@current: logical operators linked list
 *Return: void
 */

void log_current(SHELL *shell, log **current)
{
	char sp;
	int stat;

	stat = shell->status;
	sp = (*current)->sep;

	if (stat == 0)
	{
		if (sp == '&' || sp == ';')
		{
			return;
		}
		else if (sp == '|')
		{
			*current = (*current)->next;
		}
	}

	else if (stat != 0)
	{
		if (sp == '|' || sp == ';')
		{
			return;
		}
		else if (sp == '&')
		{
			*current = (*current)->next;
		}
	}
}
/**
 *handle_builtin_commands - this handles builtins
 *@shell: main structure
 *Return: 1 case of exit, 0 upon success and -1 for fail
 */
int handle_builtins(SHELL *shell)
{
	unsigned long int i;
	int exit_status;

	builtin builtin_commands[] = {
		/*{"env", env_command},*/
		{"exit", exit_command},
		{"cd", change_dir_command}
	};

	for (i = 0; i < sizeof(builtin_commands) / sizeof(builtin); i++)
	{
		if (Strcmp(shell->toks[0], builtin_commands[i].command) == 0)
		{
			if (Strcmp(builtin_commands[i].command, "exit") == 0)
			{
				if (shell->toks[1])
				{
					exit_status = Atoi(shell->toks[1]);
					shell->status = exit_status;
				}
				else
					shell->status = 0;
				return (1);
			}
			builtin_commands[i].function(shell);
			return (0);
		}
	}
	return (-1);
}


/**
 *env_command - this prints the enviroment variables.
 *@shell: mian structure.
 *Return: nothing.
 */
void env_(SHELL *shell)
{
	char **_env = shell->_environ;

	while (*_env)
	{
		Write(*_env);
		Write("\n");
		_env++;
	}
}
