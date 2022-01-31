#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main() 
{
  char buf[1];
  int parent[2];
  int child[2];
  int parent_pipe = pipe(parent);
  int child_pipe = pipe(child);

  if (parent_pipe == -1) {
    fprintf(1, "Usage: Failed to create parent pipe");
    exit(1);
  }

  if (child_pipe == -1) {
    fprintf(1, "Usage: Failed to create child pipe");
    exit(1);
  }

  if (fork() == 0) {
    close(parent[1]);
    close(child[0]);
    read(parent[0], buf, 1);
    printf("%d: received p%sng\n", getpid(), buf);
    write(child[1], "o", 1);
    close(child[1]);
  } else if (fork() > 0) {
    close(parent[0]);
    close(child[1]);
    write(parent[1], "i", 1);
    close(parent[1]);
    read(child[0], buf, 1);
    printf("%d: received p%sng\n", getpid(), buf);
  }
  exit(0);
}
