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
		if (fork() == 0)
		{
			char *args[2];

			args[0] = buffer;
			args[1] = NULL;

			if (execve(buffer, args, NULL) == -1)
			{
				perror(buffer);
			}
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
		}
	}
	free(buffer);
	return (0);
}
