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

    if (strcmp(command, "exit") == 0) {
      exit(0);
    } else {
      printf("%s: command not found", command);
      printf("\n");
    }
  }

  return 0;
}
