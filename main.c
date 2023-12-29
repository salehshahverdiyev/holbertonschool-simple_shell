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
			if (access(args[0], X_OK) == -1)
			{
				char *path = getenv("PATH");
				char *path_token = strtok(path, ":");

				while (path_token != NULL)
				{
					char path_command[BUFFER_SIZE];

					snprintf(path_command, sizeof(path_command), "%s/%s", path_token, args[0]);
					if (access(path_command, X_OK) == 0)
					{
						if (execv(path_command, args) == -1)
						{
							perror(path_command);
							exit(EXIT_FAILURE);
						}
					}
					path_token = strtok(NULL, ":");
				}
				fprintf(stderr, "%s: command not found\n", args[0]);
				exit(EXIT_FAILURE);
			}
			else
			{
				if (execvp(args[0], args) == -1)
				{
					perror(args[0]);
					exit(EXIT_FAILURE);
				}
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
