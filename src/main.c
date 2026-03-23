#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  if (!background) {}
    int ret = fork();
    printf("$ ");

    // Initialize input variable and take user input
    char command[100];
    fgets(command, sizeof(command), stdin);
    //remove trailing newline
    command[strcspn(command, "\n")] = '\0';

    printf("%s: command not found", command);
    waitpid(ret, NULL);
  }

  return 0;
}
