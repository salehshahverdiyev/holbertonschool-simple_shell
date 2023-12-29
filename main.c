#include "main.h"
#include <unistd.h>

/**
 * main - entry
 * Return: IDK
 */
int main(void)
{
	char *buffer;
	size_t bufsize = BUFFER_SIZE;

	pid_t child_pid;
	int status;
	int use_absolute_path = 0;

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

		if (strcmp(buffer, "exit") == 0)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}

		if (buffer[0] == '/')
		{
			use_absolute_path = 1;
		}

		child_pid = fork();

		if (child_pid == -1)
		{
			perror("Error forking");
			exit(EXIT_FAILURE);
		}

		if (child_pid == 0)
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

			if (!use_absolute_path)
			{
				char full_path[BUFFER_SIZE];

				char *path = getenv("PATH");
				if (path == NULL)
				{
					perror("Error getting PATH");
					exit(EXIT_FAILURE);
				}

				token = strtok(path, ":");
				while (token != NULL)
				{
					snprintf(full_path, sizeof(full_path), "%s/%s", token, args[0]);
					if (execvp(full_path, args) != -1)
					{
						exit(EXIT_SUCCESS);
					}

					token = strtok(NULL, ":");
				}

				perror(args[0]);
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
			waitpid(child_pid, &status, 0);
		}
	}

	free(buffer);
	return 0;
}
