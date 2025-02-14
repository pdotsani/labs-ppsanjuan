#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int opt;
  bool help = false;
  bool numbering = false;
  bool meowed = false;

  while((opt = getopt(argc, argv, "mnh")) != -1) {
    switch (opt)
    {
      case 'n':
      numbering = true;
      break;
      case 'm':
      meowed = true;
      break;
      case 'h':
      help = true;
      printf("sfcat\n\nprints the output of the file(s) or stdin.\n\n-n line numbering\n-m add a meow to every line!\n-h help\n");
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
    char line[1024];
    char meow[] = " meow!";
    int lineNo = 1;

    while (fgets(buf, sizeof(buf), file) != NULL) {      
      strcpy(line, buf);
      
      if (meowed) {
        // remove newline from buffered string
        line[strlen(line)-1] = '\0';
        strcat(line, meow);
        strcat(line, "\n");
      }

      if (numbering) {
        printf("%5d\t%s", lineNo, line);
        lineNo++;
      } else {
        printf("%s", line);
      }
    }
    fclose(file);
  }

  return 0;
}