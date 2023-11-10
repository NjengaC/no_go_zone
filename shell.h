#ifndef MAIN_H
#define MAIN_H

extern char **environ;


#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>



/**
 * struct SHELL - This struct represents the shell environment and stores info
 * on the shell's state.
 * @av: An array of strings representing the command-line arguments passed
 * to the shell.
 * @toks: An array of strings representing the tokens of the current command
 * input.
 * @pid: An integer representing the process ID of the current process.
 * @status: An integer representing the exit status of the last executed
 * command.
 * @_environ: An array of strings.
 * @loop_count: An integer representing the number of times the shell has
 * executed its main loop.
 */

typedef struct SHELL
{
	char **av;
	char **toks;
	int pid;
	int status;
	char **_environ;
	int loop_count;
} SHELL;


/**
 * struct builtincommands - This struct stores built-in commands in the shell.
 * @command: A string representing the name of the built-in command.
 * @function: A function pointer to the function that executes
 * the built-in command.
 */

typedef struct builtincommands
{
	char *command;
	void (*function)(SHELL *);
} builtin;



/**
 * struct log - This struct represents a node in a linked list used to store
 * logical operators in a command line.
 * @com: A string representing the command associated with the node.
 * @sep: A character representing the logical operator separator.
 * @next: A pointer to the next node in the linked list.
 */

typedef struct log
{
	char *com;
	char sep;
	struct log *next;
} log;

			/* PROCESS FUNCTIONS */
void _sigint(int signum __attribute__((unused)));
void get_env(SHELL *shell);
void fill_shell(SHELL *eshell);
void frees(SHELL *eshell);
void write_i(char *input);
void fork_(char *input, SHELL *shell);
void command_unfound(SHELL *shell);
void path_errors(SHELL *shell);
void log(log **head, char *command);
void log_current(SHELL *shell, log **current);
void line_shuffler(char *line, int mode);
void free_log(log *head);
void sep(log **head, char *line);
void file_as_arg(SHELL *shell);
void flush_error(char *error, SHELL *shell);
void ext(char *nextToken, const char *delim, int *isDelimiter);

char *Replace(char *input, char *new, char *copy, char *ename);
char **tokenize(char *line, int mode);
char *handle_hash(char *buffer);
char *which(char *input);
char *_strtok(char *str, const char *delim);
char *_itoa(int n);
char *global_variable(char *input __attribute__ ((unused)), SHELL *shell);
char *exit_status(char *input, char *status);
char *identity(char *input, char *id);
char *en_var(char *input, SHELL *shell);

int _source(SHELL *shell, char *line);
int _executables(char *input);
int _process(SHELL *shell __attribute__ ((unused)));
int _access(char *input, SHELL *shell);
int _first(char *input, SHELL *shell);
int syntax(char *input, SHELL *shell);
int syntax_error(char *input, SHELL *shell);
int pipe(char *input, SHELL *shell);
int handle_amp(char *input, SHELL *shell);

/* Handles builtin commands */

void _chdir(SHELL *shell);
void exit_(SHELL *shell);
void env_(SHELL *shell);
int handle_builtins(SHELL *shell);


char *_getenv(const char *name);
int _atoi(const char *nptr);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);
char *_strdup(const char *s);
void *_realloc(void *ptr, size_t old_size, size_t size);
char *_getline();
int _strlen(char *input);
size_t _strlen0(const char *s);

#endif
