#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

int rotate(int *ch, unsigned int places) {
  int rawChange = *ch + places;
  // If character not in range, return -1
  if (*ch > 126 || *ch < 33) {
    return -1;
  }

  // If character after + places goes over range, 
  // recycle back to beginning of range
  if (rawChange > 126 && *ch <= 126 && *ch > 32) {
    *ch = rawChange - 126 - 126*(places / 126) + 32;
  } else {
    *ch = rawChange;
  }
  return 0;
} 

int main(int argc, char *argv[]) {
  bool newline = true;
  bool cypher = false;
  bool help = false;
  int places;
  int opt;
  
  while((opt = getopt(argc, argv, "nr:h")) != -1) {
    switch (opt)
    {
      case 'n':
      newline = false;
      break;
      case 'r':
      places = atoi(optarg);
      cypher = true;
      break;
      case 'h':
      help = true;
      printf("sfecho\n\nechos a statement you make after the command.\n\n-n no newline\n-r cypher the message!\n-h help\n");
      break;
      
      default:
      break;
    }
  }

  if(help) {
    return 0;
  }
  
  for (int i = optind; i < argc; i++) {
    if (cypher) {
      size_t size = strlen(argv[i]);

      for (int j = 0; j < size; j++) {
        int c = *(argv[i] + j);
        int *ptr = &c;
        rotate(ptr, places);
        printf("%c", (char)c);
      }
      printf(" ");
    } else {
      printf("%s ", argv[i]);
    }
  }
    

  if (newline) {
    printf("\n");
  }

  return 0;
}