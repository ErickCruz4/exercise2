#include "../include/terminal.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_ARGS 64

/**
 * @brief Executes the given command.
 * @param input The command to execute.
 */
void execute_command(char *input) {
  char *args[MAX_ARGS];
  int i = 0;

  // Tokenize the input string into arguments
  args[i] = strtok(input, " \t\n");
  while (args[i] != NULL && i < MAX_ARGS - 1) {
    i++;
    args[i] = strtok(NULL, " \t\n");
  }

  if (i == 0) return;  // No command entered

  // Create a child process
  pid_t pid = fork();
  if (pid < 0) {
    perror("fork failed");
  } else if (pid == 0) {
    // Child process: execute the command

    // Ensure the PATH environment variable is available
    if (getenv("PATH") == NULL) {
      setenv("PATH", "/usr/bin:/bin:/usr/sbin:/sbin", 1);
    }

    execvp(args[0], args);
    perror("execvp failed");  // If execvp returns, it must have failed
    exit(EXIT_FAILURE);
  } else {
    // Parent process: wait for the child process to finish
    wait(NULL);
  }
}
