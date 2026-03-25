#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>


// THIS PROGRAM DOES NOT RUN ON WINDOWS OS
/* TODO: 
    -refactor for cleaner and more efficient code later
    -reconsider using snprint() to manage buffer when printing
    -double check memory management
    -implement graceful error handling
*/

// Extract a substring from the input
char* extractArg(const char *input) {
  //skip leading space
  while (*input == ' ') {
    input++;
  }

  // Initialize a dynamic char array to hold our string; Return NULL if NULL
  int length = strcspn(input, " ");
  char *com_arg = malloc(length + 1);
  if (!com_arg) {
    return NULL;
  }

  // Copy the desired substring of the input
  strncpy(com_arg, input, length);
  
  // End string with null terminator
  com_arg[length] = '\0';

  return com_arg;
}

// returns the rest of the arguments minus a substring
char* extractArgList(const char *command) {  
  // Skip leading spaces
  while (*command == ' ') {
    command++;
  }

  // Skip first word
  int first_arg = strcspn(command, " ");
  command += first_arg;

  // Skip spaces after first word
  while (*command == ' ') command++;

  // Length of remaining string
  int length = strlen(command);

  // Allocate memory
  char *arg_list = malloc(length + 1);
  if (!arg_list) {
    return NULL;
  }

  // Copy remaining string
  strncpy(arg_list, command, length);
  arg_list[length] = '\0';

  return arg_list;
}

// Checks if exe file exists and if it has executable permisison
int printExePath(char **token_path, char *command) {
  for (int i = 0; token_path[i] != NULL; i++) {
    char *full_path = malloc(strlen(token_path[i]) + strlen(command) + 2);

    if (!full_path) {
      fprintf(stderr, "malloc failed\n");
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
    
    //finds the first argument(command)
    char *command = extractArg(input);

    // Command conditionals
    if (strcmp(command, "type") == 0) {
      char *argument_list = extractArgList(input); 
      char *path = getenv("PATH");

      if (strcmp(argument_list, "echo") == 0 || strcmp(argument_list, "exit") == 0 || strcmp(argument_list, "type") == 0) {
        printf("%s is a shell builtin\n", argument_list);
      } else {
        if (path != NULL) {
          char **token_path = (tokenize(path, ":"));
          printExePath(token_path, extractArg(argument_list));
        }
      }
      free(argument_list);
      
    } else if (strcmp(input, "exit") == 0) {
        exit(0);
    } else if (strcmp(command, "echo") == 0) {
        char *args = extractArgList(input);
        printf("%s\n", args);
        free(args);
    } else {
        printf("%s: command not found\n", input);
    }

    free(command);
  }
  return 0;
}
