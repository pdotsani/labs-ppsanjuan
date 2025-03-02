#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>

struct globals {
    bool help;
    bool numbering;
    bool meowed;
    char str[1024];
    int opt;
};

void readFromStdin(struct globals *g, int *lineNo) {
  while(fgets(g->str, sizeof(g->str), stdin) != NULL) {
    if (g->numbering == true) {
      printf("%5d\t%s", *lineNo, g->str);
      *lineNo = *lineNo + 1;
    } else {
      printf("%s", g->str);
    }
  }
}
 
int main(int argc, char *argv[]) {
  struct globals g;
  g.help = false;
  g.numbering = false;
  g.meowed = false;
  
  int *lineNo;
  lineNo = malloc(100);
  *lineNo = 1;

  while((g.opt = getopt(argc, argv, "mnh")) != -1) {
    switch (g.opt)
    {
      case 'n':
      g.numbering = true;
      break;
      case 'm':
      g.meowed = true;
      break;
      case 'h':
      g.help = true;
      printf("sfcat\n\nprints the output of the file(s) or stdin.\n\n-n line numbering\n-m add a meow to every line!\n-h help\n");
      break;
      
      default:
      break;
    }
  }

  if(g.help) {
    return 0;
  }

  if (optind == argc) {
    readFromStdin(&g, lineNo);
  }
  
  for (int i = optind; i < argc; i++) {
    if (strcmp(argv[i], "-") == 0) {
      readFromStdin(&g, lineNo);
    } else {
      FILE* file = fopen(argv[i], "r");
    
      if (file == NULL) {
        perror("fopen");
        return 1;
      }

      char buf[1024];
      char line[1024];
      char meow[] = " meow!";

      while (fgets(buf, sizeof(buf), file) != NULL) {      
        strcpy(line, buf);
        
        if (g.meowed) {
          // remove newline from buffered string
          line[strlen(line)-1] = '\0';
          strcat(line, meow);
          strcat(line, "\n");
        }

        if (g.numbering) {
          printf("%5d\t%s", *lineNo, line);
          *lineNo = *lineNo + 1;
        } else {
          printf("%s", line);
        }
      }
      fclose(file);
      printf("\n");
    }
  }
  free(lineNo);
  return 0;
}