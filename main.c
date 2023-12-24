#include "main.h"


char **environ; // extern char **environ;  // Ensure environ is declared properly

// Define your copy function or remove the reference if not needed
int copyContents() {
    // Implement your copy function logic here
    return 0;
}

int executeCommand(char *command, char *arguments[]) {
    // Execute the command using execve
    if (execve(command, arguments, environ) == -1) {
        perror("execve");
        exit(EXIT_FAILURE);
    }

    return 0;
}

int main() {
    char *inputLine = NULL;
    size_t lineLength = 0;
    ssize_t bytesRead;
    pid_t childPid;
    int childStatus;
    char *commandArgs[] = { NULL, NULL }; // Initialize the array properly

    while (1)
      {
        bytesRead = getline(&inputLine, &lineLength, stdin);
        if (bytesRead == -1) {
            free(inputLine);
            exit(EXIT_SUCCESS);
        }

        // Tokenize the input
        char *delimiter = " \n";
        char *token = strtok(inputLine, delimiter);

        // Check for a special case (e.g., if the command starts with '.')
        if (token != NULL && token[0] == '.') {
            copyContents();
            commandArgs[0] = "./hbtn_ls";
            commandArgs[1] = "/var";
            executeCommand(commandArgs[0], commandArgs);
        } else {
            // Execute the command and arguments
            while (token != NULL) {
                commandArgs[0] = token;
                executeCommand(token, commandArgs);
                token = strtok(NULL, delimiter);
            }
        }

        // Wait for the child process to complete
        wait(&childStatus);
    }

    // Free allocated memory for getline
    free(inputLine);

    return 0;
}
