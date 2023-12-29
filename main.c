#include "main.h"
/**
 * print_environment - prints the current environment
*/
void print_environment(void)
{
	extern char **environ;
	int i = 0;
	
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
/** main- entry point
 * Return: 0
*/
int main(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	int status = 0;
	
	while (1)
	{
		printf("($) ");
		getline(&buffer, &bufsize, stdin);
<<<<<<< HEAD
		buffer[strcspn(buffer, "\n")] = '\0';
		if (strcmp(buffer, "exit") == 0)
		{
			free(buffer);
			exit(status);
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
				wait(&status);
			}
		}
=======
		buffer[strlen(buffer) - 1] = '\0';
		execute_command(buffer, &status);
>>>>>>> parent of a1786c7... please pass :(
	}
	free(buffer);
	return (0);
}
