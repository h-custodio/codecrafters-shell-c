#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findDelimIndex (const char *input) {
  return strcspn(input, " ");
}

// Extract the first argument (input)
char* extractArg(const char *input, int delim_index) {
  // Initialize a dynamic char array to hold our string; Return NULL if NULL
  char *com_arg = malloc(delim_index  + 1);
  if (!com_arg) return NULL;

  // Extracts the first word from input
  strncpy(com_arg, input, delim_index);
  // End string with null terminator
  com_arg[delim_index] = '\0';

  return com_arg;
}

// Prints the arguments
void printArgList(const char *input, int delim_index) {  
  char arg_list[100] = "";
  strncat(arg_list, input + delim_index + 1, strlen(input));
  printf(arg_list);
  printf("\n");
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
    char *command = extractArg(input, findDelimIndex(input));

    // IF tree
    if (strcmp(command, "type") == 0) {
      char *argument = extractArg(command, findDelimIndex(command)); 
      printf(argument);
      if (strcmp(argument, "echo") == 0) {
        printf("%s is a shell builtin\n", argument);
      } else if (strcmp(argument, "exit") == 0) {
          printf("%s is a shell builtin\n", argument);
      } else {
          printf("%s: input not found\n", argument);
      }
      free(argument);
    } else if (strcmp(input, "exit") == 0) {
        exit(0);
    } else if (strcmp(command, "echo") == 0) {
        printArgList(input, findDelimIndex(input));
    } else {
        printf("%s: input not found\n", input);
    }

    free(command);
  }
  return 0;
}
