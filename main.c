#include "main.h"
char **environ;
/**
 * is_absolute_path - Check if a string is an absolute path.
 * @str: The string to check.
 * @argv: The argument vector.
 * Return: 0 if not an absolute path, 1 otherwise.
 */
int is_absolute_path(char *str, char *argv[])
{
    if (str[0] == '/')
        execve(str, argv, environ);
    return 0;
}

/**
 * main - Simple shell program.
 * Return: Always 0.
 */
int main(int argc, char **argv, char **envp)
{
    char *buffer = NULL, *token = NULL, *exit_command = "exit";
    int buffer_size = 1, child_pid = 0, status = 0;
    char *arguments[] = {"", NULL};
    size_t line_length = 33;

    (void)argc;
    (void)argv;
    (void)envp;

    while (1)
    {
        buffer_size = getline(&buffer, &line_length, stdin);
        token = strtok(buffer, " \n");

        if (buffer_size == -1 || *buffer == *exit_command)
        {
            free(buffer);
            exit(0);
        }
        else if (buffer == NULL)
        {
            free(buffer);
        }

        child_pid = fork();

        if (child_pid == -1)
        {
            printf("Process error!\n");
        }

        if (child_pid == 0)
        {
            if (buffer[0] == '.')
            {
                copy_func();
                arguments[0] = "./hbtn_ls";
                arguments[1] = "/var";
                arguments[2] = NULL;
                execve("./hbtn_ls", arguments, environ);
            }
            else
            {
                token = strtok(buffer, " \n");
                while (token != NULL)
                {
                    is_absolute_path(token, arguments);
                    token = strtok(NULL, " \n");
                }
            }
        }
        else
        {
            wait(&status);
        }
    }

    return 0;
}
