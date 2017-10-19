#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define BUF_SIZE 1024

bool is_vowel(char c) {
//Checks if the character is vowel
  switch(c){
	    case 'a':
      case 'e':
      case 'u':
      case 'i':
      case 'o':
      case 'A':
	    case 'E':
      case 'U':
      case 'I':
	    case 'O':
      return true;
	    default:
	    return false;
	}
}



int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {

  /*
   * Copy all the non-vowels from in_buf to out_buf.
   * num_chars indicates how many characters are in in_buf,
   * and this function should return the number of non-vowels that
   * that were copied over.
   */

  int j = 0;
  for(int i = 0; i < num_chars; i++){
    if(!(is_vowel(in_buf[i]))){
        out_buf[j] = in_buf[i];
        j++;
      }
  }
  return j;
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
    /*
     * Copy all the non-vowels from inputFile to outputFile.
     * Create input and output buffers, and use fread() to repeatedly read
     * in a buffer of data, copy the non-vowels to the output buffer, and
     * use fwrite to write that out.
     */

     //Declaring the buffers
     char* in_buf = (char*)calloc(BUF_SIZE, sizeof(char));
     char* out_buf = (char*)calloc(BUF_SIZE, sizeof(char));

     /*
     Reading the text from "inputFile" and copying the
     non-vowels characters to the "outputFile"
     */
     int non_vowels;
     int running = 1;
     int num_chars;
     while(running){
        num_chars = (int)fread(in_buf, sizeof(char), BUF_SIZE, inputFile);

        //When fread reaches EOF it returns 0 so we know when to break
        if(!num_chars){
          break;
        }

        //copying the non_vowels to out_buf and keeping track of the number of non_vowels
        non_vowels = copy_non_vowels(num_chars, in_buf, out_buf);
	      fwrite(out_buf, sizeof(char), non_vowels, outputFile);
     }

     //close files
     fclose(outputFile);
     fclose(inputFile);

     //free allocated memory
     free(in_buf);
     free(out_buf);
}

int main(int argc, char *argv[]) {
    FILE *inputFile;
    FILE *outputFile;

/*
  Checks if we parse files or not,
  if we don't just the programm will just read
  the stadard input and will do the standard output
*/
  if (argc == 1) {
    inputFile = stdin;
    outputFile = stdout;
  }else if(argc == 2){
    inputFile = fopen(argv[1],"r");
    outputFile = stdout;
  }else if(argc == 3){
    inputFile = fopen(argv[1],"r");
    outputFile = fopen(argv[2],"w");
  }else{
    printf("Invalid input!");
    exit(0);
  }
    disemvowel(inputFile, outputFile);

    return 0;
}
