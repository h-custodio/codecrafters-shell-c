#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>


// THIS PROGRAM DOES NOT RUN ON WINDOWS OS (Because libraries used are for UNIX, since Codecrafter's remote servers are Linux based or something)
/* TODO: 
    -refactor for cleaner and more efficient code later
    -reconsider using snprint() to manage buffer when printing
    -double check memory management
    -implement graceful error handling
*/

// Prints the rest of the arguments excluding the first 
void printArgList(char **argument) {
  if (!argument || !argument[0]) {
     return;
  }
  
  for (int i = 1; argument[i]; i++) {
    printf("%s", argument[i]);
    if (argument[i + 1]) {
      printf(" ");
    }
  }
  printf("\n");
}

// Checks if exe file exists and if it has executable permisison
int printExePath(char **token_path, char *command) {
  for (int i = 0; token_path[i] != NULL; i++) {
    char *full_path = malloc(strlen(token_path[i]) + strlen(command) + 2);

    if (!full_path) {
      perror("malloc");
      return 1;
    }

    sprintf(full_path, "%s/%s", token_path[i], command);

    if (access(full_path, X_OK) == 0) {
      printf("%s is %s\n", command, full_path);
      free(full_path);
      return 0;
    }

    free(full_path);
  }

  printf("%s: not found\n", command);
  return 1;
}

int execute(char *command, char **argument) {
  if (!command || !argument) {
    printf("cannot execute NULL");
    return 1;
  }

  int ret;
  ret = fork();

  if (ret == 0) {
    // Child process
    execvp(command, argument);
    perror("execvp");
    exit(1);
  } else if (ret < 0) {
    perror("fork");
    return 1;
  }

  //compares console's pid to current process's pid to check if background
  if (tcgetpgrp(STDOUT_FILENO) == getpgrp()) {
    waitpid(ret, NULL, 0);
  }

  return 0;
}

// Parse through a string (command) to separate using a delimiter
char** tokenize(char *command, const char *delim) {
  char *token, *savedpos;
  int capacity = 50;
  char **args = malloc((capacity + 1) * sizeof(char *));
  int arg_count = 0;
  char *copy = strdup(command);

  // Finds the first instance of word separated by delimiter
  token = strtok_r(copy, delim, &savedpos);

  while (token != NULL) {
    if (arg_count == capacity) {
      capacity *= 2;
      char **temp = realloc(args, (capacity+1) * sizeof(char *)); 

      if (temp == NULL) {
        printf("cannot reallocate more memory for tokens\n");  

        for (int i = 0; i < arg_count; i++) {
          free(args[i]);
        }

        free(args);
        return NULL;  
      } else {
        args = temp;   
      }
    }

    args[arg_count++] = strdup(token);
    // Continue to parse from one token to next from saved position
    token = strtok_r(NULL, delim, &savedpos);
  }

  args[arg_count] = NULL;
  free(copy);
  return args;
}

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  //ongoing Read-Eval-Print Loop
  while (1) {
    printf("$ ");

    // Initialize input variable, then takes user input and removes trailing newline
    char input[100];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    

    char** argument = tokenize(input, " ");
    char *path = getenv("PATH");

    //  Conditionals
    if (strcmp(argument[0], "type") == 0) {
      if (argument[1] && (strcmp(argument[1], "echo") == 0 || strcmp(argument[1], "exit") == 0 ||strcmp(argument[1], "type") == 0)) {
        printf("%s is a shell builtin\n", argument[1]);

      } else {
        if (path != NULL) {
          char **token_path = (tokenize(path, ":"));
          if (printExePath(token_path, argument[1])) {
            execute(argument[0],argument);
          }
        }

      }
    } else if (strcmp(input, "exit") == 0) {
        exit(0);

    } else if (strcmp(argument[0], "echo") == 0) {
        printArgList(argument);

    } else {
        printf("%s: command not found\n", input);
    }

    for (int i = 0; argument[i] != NULL; i++) {
      free(argument[i]);
    }
    free(argument);
  }
  return 0;
}
