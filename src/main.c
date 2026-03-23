#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  // TODO: Uncomment the code below to pass the first stage
  printf("$ ");

  // Initialize input variable and take user input
  char command[1024];
  fgets(command, sizeof(command), stdin);

  //remove trailing newline
  command[strcspn(command, "\n")] = '\0';

  printf("{command}: command not found");
  
  


  return 0;
}
