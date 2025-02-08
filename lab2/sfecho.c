#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int rotate(int *ch, unsigned int places) {
  int rawChange = *ch + places;
  if (*ch > 126 || *ch < 33) {
    return -1;
  }

  if (rawChange > 126 && *ch <= 126 && *ch > 32) {
    *ch = rawChange - 126 - 126*(places / 126) + 32;
  } else {
    *ch = rawChange;
  }

  printf("%c", (char)*ch);
  return 0;
} 

int main(int argc, char *argv[]) {
  bool newline = true;
  bool cypher = false;
  int places;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == 'n') {
        newline = false;
      } else if (argv[i][1] == 'r') {
        cypher = true;
        places = atoi(argv[i + 1]);
        i++;
      } 
    } else {
      if (cypher) {
        size_t size = strlen(argv[i]);
  
        for (int j = 0; j < size; j++) {
          int c = *(argv[i] + j);
          int* ptr = &c;
          rotate(ptr, places);
        }
        printf(" ");
      } else {
        printf("%s ", argv[i]);
      }
    }
  }

  if (newline) {
    printf("\n");
  }

  return 0;
}