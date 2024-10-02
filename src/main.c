#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/terminal.h"

#define MAX_INPUT 1024

/**
 * @brief Changes to the specified directory.
 * @param dir The directory path to change to.
 */
void change_to_directory(const char *dir) {
  if (chdir(dir) != 0) {
    perror("chdir() to directory failed");
    exit(EXIT_FAILURE);
  }
}

/**
 * @brief Prints the current working directory.
 */
void print_current_directory() {
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("Current working directory: %s\n", cwd);
  } else {
    perror("getcwd() error");
  }
}

int main(int argc, char *argv[]) {
  char input[MAX_INPUT];

  // Check if a directory path is provided as an argument
  if (argc > 1) {
    change_to_directory(argv[1]);  // Use the directory passed as an argument
  } else {
    printf("Usage: %s <directory_path>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  while (1) {  // Infinite loop to continuously take input
    // Print the current directory
    print_current_directory();

    // Prompt for user input
    printf("custom-shell> ");
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
      printf("Error reading input. Please try again.\n");
      continue;  // Continue loop to ask for input again
    }

    // Remove trailing newline character
    input[strcspn(input, "\n")] = 0;

    // Split input by ';' to handle multiple commands
    char *command = strtok(input, ";");
    while (command != NULL) {
      // Execute each command
      if (strlen(command) > 0) {
        execute_command(command);
      }
      command = strtok(NULL, ";");
    }
  }

  return 0;
}
