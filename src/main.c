#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  // TODO: Uncomment the code below to pass the first stage
  printf("$ ");

  // Initialize a char type variable named 'str' with the size 100 to as as a string
  char input* = malloc(100);
  fgets(input, sizeof(input), stdin);

  if (input == input) {
    printf("{command}: command not found")
  }
  


  return 0;
}
