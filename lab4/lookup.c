#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {

  char *keyword = argv[1];
  int keywordIdx = 0;
  int keywordLength = strlen(keyword);
  
  int fd = open(argv[2], O_RDONLY);
  if (fd == -1) {
    perror("open");
    return 1;
  }

  char c;
  ssize_t read_sz;
  while((read_sz = read(fd, &c, 1)) > 0) {
    if (*(keyword + keywordIdx) == c) {
      keywordIdx++;
      if (keywordIdx == keywordLength - 1) {
        keywordIdx = 0;
        printf("keyword");
      }
    }

    // printf("%c", c);
  }
  if (read_sz == -1) {
    perror("read");
    return 1;
  }


  return 0;
}