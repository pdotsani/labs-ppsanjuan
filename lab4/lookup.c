#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

struct keyword {
  char *keyword;
  char *dlim;
  int keywordIdx;
  int dlimIdx;
  int keywordLength;
  int dlimLength;
  bool foundKeyword;
  bool foundDlim;
  char *captured;
  bool startCapture;
  int idx;
};

int main(int argc, char *argv[]) {
  struct keyword key;
  key.keyword = argv[1];
  key.dlim = argv[2];
  key.keywordIdx = 0; 
  key.dlimIdx = 0; 
  key.keywordLength = strlen(argv[1]);
  key.dlimLength = strlen(argv[2]);
  key.foundKeyword = false;
  key.foundDlim = false;
  key.idx = 0;
  key.captured = (char *)malloc(1025);
  key.startCapture = false;
  
  int fd = open(argv[3], O_RDONLY);
  if (fd == -1) {
    perror("open");
    return 1;
  }

  char c;
  ssize_t read_sz;
  while((read_sz = read(fd, &c, 1)) > 0) {
    if (*(key.keyword + key.keywordIdx) == c && key.foundKeyword == false) {
      key.keywordIdx++;
      if (key.keywordIdx == key.keywordLength) {
        key.keywordIdx = 0;
        key.foundKeyword = true;
      }
    } else {
      key.keywordIdx = 0;
    }

    if (key.foundKeyword == true && key.foundDlim == false) {
      if(*(key.dlim + key.dlimIdx) == c) {
        key.dlimIdx++;
        if(key.dlimIdx == key.dlimLength) {
          key.dlimIdx = 0;
          key.foundDlim = true;
        }
      }
    }

    if (key.foundDlim == true && key.foundKeyword == true && key.startCapture == false) {
      if (c != ' ' && *(key.dlim + key.dlimLength - 1) != c) {
        key.startCapture = true;
      }
    }

    if (key.foundDlim == true && key.foundKeyword == true && key.startCapture == true) {
      if (c != ' ') {
        *(key.captured + key.idx) = c;
        key.idx++;
      } else {
        key.startCapture = false;
        printf("%s\n", key.captured);
        return 0;
      }
    }
  }

  if (read_sz == -1) {
    perror("read");
    return 1;
  }

  return 0;
}