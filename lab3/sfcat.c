#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int opt;
  bool help = false;
  bool numbering = false;

  while((opt = getopt(argc, argv, "nh")) != -1) {
    switch (opt)
    {
      case 'n':
      numbering = true;
      break;
      case 'h':
      help = true;
      printf("sfcat\n\nprints the output of the file(s) or stdin.\n\n-n line numbering\n-h help\n");
      break;
      
      default:
      break;
    }
  }

  if(help) {
    return 0;
  }

  if (optind == argc) {
    char str[100];
    scanf("%s", str);
    printf("%s\n", str);
    return 0;
  }
  
  for (int i = optind; i < argc; i++) {
    FILE* file = fopen(argv[i], "r");
    
    if (file == NULL) {
      printf("Error opening file\n");
      return 1;
    }

    char buf[1024];
    int line = 1;

    while (fgets(buf, sizeof(buf), file) != NULL) {
      if (numbering) {
        printf("%5d\t%s", line, buf);
        line++;
      } else {
        printf("%s", buf);
      }
    }
    fclose(file);
  }

  return 0;
}