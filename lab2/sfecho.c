#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[]) {
  bool newline = true;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] == 'n') {
      newline = false;
    } else {
      printf("%s ", argv[i]);
    }
  }

  if (newline) {
    printf("\n");
  }

  return 0;
}