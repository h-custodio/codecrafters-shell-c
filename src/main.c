#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  //ongoing Read-Eval-Print Loop
  while (true) {
    printf("$ ");

    // Initialize input variable and take user input
    char command[100];
    fgets(command, sizeof(command), stdin);
    //remove trailing newline
    command[strcspn(command, "\n")] = '\0';
    
    int space_index = strcspn(command, "\0");
    char com_arg[16] = "";
    strncat(com_arg, command, space_index);

    if (strcmp(command, "exit") == 0) {
      exit(0);
    } else if (strcmp(com_arg, "echo") == 0) {
      printf(command);
    } else {
      printf(com_arg);
      //printf("%s: command not found", command);
      printf("\n");
    }
  }

  return 0;
}
