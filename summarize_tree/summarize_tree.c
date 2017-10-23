#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


static int num_dirs, num_regular;

bool is_dir(const char* path) {
  struct stat buf; //declare the stat struct to check if path is a directory
  int errnum; //this int will be used to store the errno value for error messages
  if((stat(path, &buf))==-1){ // Cheks if path is the directory and checks for errors
    errnum = errno;
    printf("Error checking the path: %s, the path name: %s\n", strerror(errnum), path);
    exit(1);
  }
  if(S_ISDIR(buf.st_mode) != 0){ //S_ISDIR returns nonzero value if path is the directory
    return true;
  }else{
    return false;
  }
}

/*
* I needed this because the multiple recursion means there's no way to
* order them so that the definitions all precede the cause.
*/
void process_path(const char*);

void process_directory(const char* path) {
  num_dirs++; //increment the number of directories
  struct dirent *cur_dir;
  DIR *dir;
  int errnum; //this int will be used to store the errno value for error messages
  if((dir = opendir(path))==NULL){  //open the directory and checks for error
    errnum = errno;
    printf("Error opening directory: %s, the directory name: %s\n", strerror(errnum), path);
    exit(1);
  }
  if(chdir(path)==-1){ //go to this directory and checks for error
    errnum = errno;
    printf("Error changing directory: %s, the directory name: %s\n", strerror(errnum), path);
    exit(1);
  }
  while((cur_dir = readdir(dir))!=NULL){ //loop through the entries in the directory

    // skip if the entries are ".." or "."
    if((strcmp((cur_dir->d_name),"..")==0)||(strcmp((cur_dir->d_name),".")==0)){
      continue;
    }

    //recursive call to check the entry
    process_path(cur_dir->d_name);

  }

  if(chdir("..")==-1){ //go to the parent directory and checks for error
    errnum = errno;
    printf("Error changing directory: %s, the directory name: %s\n", strerror(errnum), "..");
    exit(1);
  }

  if(closedir(dir)==-1){ //closes directory and checks for error
    errnum = errno;
    printf("Error closing directory: %s, the directory name: %s\n", strerror(errnum), path);
    exit(1);
  }
}

void process_file(const char* path) {
  num_regular++; //update the number of regular files
}

void process_path(const char* path) {
  if (is_dir(path)) {
    if(path!="."&&path!="..")process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  process_path(argv[1]);

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
