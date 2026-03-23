#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findDelimIndex (const char *input) {
  return strcspn(input, " ");
}

// Extract the a substring from the input
char* extractArg(const char *input) {
  //skip leading space
  while (*input == ' ') input++;

  // Initialize a dynamic char array to hold our string; Return NULL if NULL
  int length = strcspn(input, " ");
  char *com_arg = malloc(length + 1);
  if (!com_arg) return NULL;


  // Copy the desired substring of the input
  strncpy(com_arg, input, length);
  
  // End string with null terminator
  com_arg[length] = '\0';

  return com_arg;
}

// returns the rest of the arguments minus a substring
char* extractArgList(const char *command) {  
  //skip leading space
  while (*command == ' ') command++;

  //skips to start of second argument
  int first_arg = strcspn(command, " ");
  command += first_arg;
  while (*command == ' ') command++;

  // Initialize a dynamic char array to hold our string; Return NULL if NULL
  int length = strlen(command);
  char *arg_list = malloc(length + 1);
  if (!arg_list) return NULL;

  // Extracts the arguments after a substring
  strncpy(arg_list, command + first_arg, length);

  // End string with null terminator
  arg_list[length] = '\0';

  return arg_list;
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

    // IF tree
    if (strcmp(command, "type") == 0) {
      char *argument_list = extractArgList(command); 
      if (strcmp(argument_list, "echo") == 0) {
        printf("%s is a shell builtin\n", argument_list);
      } else if (strcmp(argument_list, "exit") == 0) {
          printf("%s is a shell builtin\n", argument_list);
      } else {
          printf("%s: input not found\n", argument_list);
      }
      free(argument_list);
    } else if (strcmp(input, "exit") == 0) {
        exit(0);
    } else if (strcmp(command, "echo") == 0) {
        extractArgList(input);
    } else {
        printf("%s: input not found\n", input);
    }

    free(command);
  }
  return 0;
}
