#include <ftw.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>


static int num_dirs, num_regular;

static int callback(const char *fpath, const struct stat *sb, int typeflag) {
  if(typeflag!=FTW_NS){ //check if path is a symbolic link
    if (typeflag==FTW_F) { //check if it's a regular file
      num_regular++;  //update the number of regular file
    }else if(typeflag==FTW_D){//check if it's a directory
      if((strcmp(fpath, "..")!=0)&&((strcmp(fpath, "."))!=0)){ //skip the "." and ".."
        num_dirs++;//update the number of directories
      }
    }
  }else{
    printf("This path is something other than a symbolic link on which stat() could not successfully be executed");
  }

  return 0;
}

#define MAX_FTW_DEPTH 16

int main(int argc, char* argv[]) {
  // Check arguments and set things up

  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  ftw(argv[1], callback, MAX_FTW_DEPTH);

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);
  return 0;
}
