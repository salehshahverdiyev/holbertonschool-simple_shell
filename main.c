#include "main.h"
/**
 * file_exists - checks if a file exists and is executable
 * @filename: name of the file to check
 * Return: 1 if the file exists and is executable, 0 otherwise
*/
int file_exists(const char *filename)
{
	return (access(filename, X_OK) == 0);
}

/**
 * concat_path - concatenates two strings with a '/' in between
 * @path: first part of the path
 * @command: second part of the path
 * Return: pointer to the concatenated path
 */
char *concat_path(const char *path, const char *command)
{
	size_t len_path = strlen(path);
	size_t len_command = strlen(command);
	char *result = malloc(len_path + 1 + len_command + 1);
	
	if (result == NULL)
	{
		perror("Unable to allocate memory");
		exit(EXIT_FAILURE);
	}
	strcpy(result, path);
	if (result[len_path - 1] != '/')
	{
		strcat(result, "/");
	}
	strcat(result, command);
	return (result);
}

/**
 * main - entry
 * Return: 0
*/
int main(void)
{
	char *buffer;
	size_t bufsize = BUFFER_SIZE;
	int status;

	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		char *path_copy = NULL;
		getline(&buffer, &bufsize, stdin);
		buffer[strlen(buffer) - 1] = '\0';
		if (strcmp(buffer, "exit") == 0)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		printf("($) ");
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
			if (strchr(args[0], '/') != NULL)
			{
				if (execv(args[0], args) == -1)
				{
					perror(args[0]);
					exit(EXIT_FAILURE);
				}
				else
				{
					char *path = getenv("PATH");
					char *path_copy = strdup(path);
					char *path_token = strtok(path_copy, ":");
					while (path_token != NULL)
					{
						char *full_path = concat_path(path_token, args[0]);
						
						if (file_exists(full_path))
						{
							if (execv(full_path, args) == -1)
							{
								perror(full_path);
								exit(EXIT_FAILURE);
							}
						}
						free(full_path);
						path_token = strtok(NULL, ":");
					}
				}
				fprintf(stderr, "%s: command not found\n", args[0]);
				free(path_copy);
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
			wait(&status);
			if (WIFEXITED(status))
			{
			return WEXITSTATUS(status);
			}
		}
	}
	free(buffer);
	return (0);
}
