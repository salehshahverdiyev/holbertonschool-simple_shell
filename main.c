#include "main.h"
/**
 * main - entry
 * Return: IDK
*/
int main(void)
{
	char *buffer;
	size_t bufsize = BUFFER_SIZE;

	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}
	while (1)
	{
		printf("($) ");
		getline(&buffer, &bufsize, stdin);
		buffer[strlen(buffer) - 1] = '\0';
		if (strcmp(buffer, "exit") == 0)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
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
			if (execvp(args[0], args) == -1)
			{
				perror(args[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}
	}
	free(buffer);
	return (0);
}
