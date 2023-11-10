#include "shell.h"

#define buffsize 1024

/**
 * Realloc - the function that reallocates memory using malloc.
 * @ptr: Pointer of the memory to be reduced.
 * @old_size: old size of the memory to be changed.
 * @size: new size to change to.
 * Return: nothing.
 */

void *Realloc(void *ptr, size_t old_size, size_t size)
{
	void *new_ptr;
	char *old_ptr = (char *)ptr;
	char *new_char_ptr;
	size_t i;

	if (!ptr)
	{
		return (malloc(size));
	}
	else if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		new_ptr = malloc(size);
		if (!new_ptr)
		{
			return (NULL);
		}
		if (size < old_size)
		{
			old_size = size;
		}
		new_char_ptr = (char *)new_ptr;
		for (i = 0; i < old_size; i++)
		{
			new_char_ptr[i] = old_ptr[i];
		}
		free(ptr);
		return (new_ptr);
	}
}


/**
 * Getline - the Function that fetches the entire input from the output
 * stream.
 * Return: input fetched from the stream.
 */


char *Getline()
{
	char *buffer, r = 0;
	int i = 0, charsRead, buffer_size;

	buffer_size = buffsize,	buffer = malloc(buffer_size * sizeof(char));

	if (buffer == NULL)
	{
		free(buffer);
		return (NULL);
	}

	while (r != EOF && r != '\n')
	{
		fflush(stdin);
		charsRead = read(STDIN_FILENO, &r, 1);
		if (charsRead == 0)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		buffer[i] = r;
		if (buffer[0] == '\n')
		{
			free(buffer);
			return ("\0");
		}

		i++;
	}
	buffer[i] = '\0', buffer = hash(buffer);
	if (buffer == NULL)
	{
		return ("\0");
	}
	return (buffer);
}

/**
 * hash - a Function that handles the case where # has been used in a command.
 * @buffer: pointer to where the user input is stored.
 * Return: the buffer after the #has been ignored hence a comment.
 */

char *hash(char *buffer)
{
	int i;
	bool quotes = false;

	if (buffer[0] == '#')
	{
		free(buffer);
		return (NULL);
	}

	else
	{
		for (i = 0; buffer[i]; i++)
		{
			if (buffer[i] == 34)
			{
				quotes = !quotes;
			}

			if (!quotes && buffer[i] == '#' && buffer[i - 1] == ' ')
			{
				buffer[i] = '\0';
				break;
			}
		}
	}

	return (buffer);
}

/**
 * _strtok - a function that tokenizes a string based on whatever it is given.
 * @str: Pointer to the string to be tokenized.
 * @delim: delimiter which strtok function use to tokenize the string.
 * Return: The tokenized words, else return NULL on failure.
 */

char *_strtok(char *str, const char *delim)
{
	static char *nextToken;
	char *token = NULL;
	int isDelimiter;

	if (str != NULL)
		nextToken = str;
	if (nextToken == NULL || *nextToken == '\0')
		return (NULL);
	while (*nextToken != '\0')
	{
		isDelimiter = 0;
		extension(nextToken, delim, &isDelimiter);
		if (!isDelimiter)
			break;
		nextToken++;
	}
	if (*nextToken == '\0')
		return (NULL);
	token = nextToken;
	while (*nextToken != '\0')
	{
		isDelimiter = 0;
		extension(nextToken, delim, &isDelimiter);
		if (isDelimiter)
		{
			*nextToken = '\0', nextToken++;
			break;
		}
		nextToken++;
	}
	return (token);
}


/**
 * getenv_custom - this gets environment variables
 * @name: a name of the variable
 *
 * Return: NULL on failure, else pointer to the value of the
 * environment variable.
 **/

char *getenv_custom(const char *name)
{
	size_t name_length = 0;
	int match;
	char **env;
	size_t i;

	if (name == NULL || *name == '\0')
	{
		return (NULL);
	}
	while (name[name_length] != '\0')
		name_length++;
	for (env = environ; *env != NULL; env++)
	{
		match = 1;
		for (i = 0; i < name_length; i++)
		{
			if ((*env)[i] != name[i])
			{
				match = 0;
				break;
			}
		}
		if (match && (*env)[name_length] == '=')
		{
			return (&(*env)[name_length + 1]);
		}
	}
	return (NULL);
}
