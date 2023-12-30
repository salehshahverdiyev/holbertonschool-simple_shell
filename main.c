#include "main.h"
/**
 * print_environment - prints the current environment
*/
void print_environment(void)
{
	extern char **environ;
	char *prev_var = NULL;

	for (int i = 0; environ[i] != NULL; i++)
	{
		if (prev_var == NULL || strcmp(environ[i], prev_var) != 0)
		{
		printf("%s\n", environ[i]);
		prev_var = environ[i];
		}
	}
}

/**
 * execute_command - execute the given command
 * @buffer: command to be executed
 * @status: exit status
*/
void execute_command(char *buffer, int *status)
{
	if (strcmp(buffer, "exit") == 0)
	{
		free(buffer);
		exit(*status);
	}
	else if (strcmp(buffer, "env") == 0)
	{
		print_environment();
	}
	else
	{
		if (fork() == 0)
		{
			char *token;
			char *args[BUFFER_SIZE];
			int i = 0;
			
			token = strtok(buffer, " ");
			while (token != NULL)
			{
				args[i++] = token;
				token = strtok(NULL, " ");
			}
			args[i] = NULL;
			execvp(args[0], args);
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(status);
			if (WIFEXITED(*status))
			{
				*status = WEXITSTATUS(*status);
			}
		}
	}
}

/**
 * main - entry point
 * Return: 0
 */
int main(void)
{
	char *buffer;
	size_t bufsize = BUFFER_SIZE;
	int status = 0;
	
	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		printf("($) ");
		getline(&buffer, &bufsize, stdin);
		buffer[strlen(buffer) - 1] = '\0';
		execute_command(buffer, &status);
	}
	free(buffer);
	return (0);
}
