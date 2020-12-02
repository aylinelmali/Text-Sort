#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "word.h"

//Finds all words in file
void parseFile(int f, struct Word* start){
 char buffer[30];
 int k = 0;
 char ch;
 while(read(f, &ch, 1) != 0){
   if(isalpha(ch) != 0){
   buffer[k] = ch;
   k++;
  }
  else{
    if(k != 0){
     buffer[k] = '\0';
     k = 0;
     char *newBuffer = (char*) malloc(sizeof(char) * 30);
     for(int a = 0; a < 30; a++){newBuffer[a] = buffer[a];}
     struct Word* pointer = start;
     while(pointer != NULL){
      if(strcmp(newBuffer, pointer->text) == 0){
       pointer->count = pointer->count + 1;
       break;
      }
      if(pointer->next == NULL){
       struct Word* newWord = word(newBuffer, 1, NULL);
       pointer->next = newWord;
       break;
      }
      else{pointer = pointer->next;}
     }
    for(int j = 0; j < 30; j++){buffer[j] = '\0';}
    }
   }
  }
 }

//converts int to string with /n at the end
char* convertInt(int num){
 int rem = 0;
 int div = num;
 char *number = (char*) malloc(sizeof(char) * 10);
 char *number1 = (char*) malloc(sizeof(char) * 11);
 for(int j = 0; j < 10; j++){number[j] = ' ';}
 for(int k = 0; k < 11; k++){number1[k] = '\0';}
 if(num == 0){
  number1[0] = '0';
  number1[1] = '\n';
  return number1;
 }
 int i = 9;
 while(i >= 0 && div != 0){
  rem = div % 10;
  number[i] = '0' + rem;
  i--;
  div = div / 10; 
 }
 int b = 0;
 for(int a = 0; a < 10; a++){
  if(number[a] != ' '){
  number1[b] = number[a];
  b++;
  }
 }
 number1[b] = '\n';
 return number1;
}

//runs program
int main(int argc, char *argv[]){
 extern int errno;
 const char *name = "WORD_FREAK";
 struct Word* first = word("", 0, NULL);
 char* nFile = getenv(name);
 if(nFile != NULL){
  int fd = open(nFile, O_RDONLY);
  if(fd < 0){
   write(2, strerror(errno), strlen(strerror(errno)));
   exit(EXIT_FAILURE);  
   }
  parseFile(fd, first);
  if(close(fd) < 0){
   write(2, strerror(errno), strlen(strerror(errno))); 
   exit(EXIT_FAILURE);
  }
 }
 else{
   for(int i = 1; i < argc; i++){
    int fd1 = open(argv[i], O_RDONLY);
    if(fd1 < 0){
     write(2, strerror(errno), strlen(strerror(errno)));
     exit(EXIT_FAILURE);
     }
    parseFile(fd1, first);
    if(close(fd1) < 0){
     write(2, strerror(errno), strlen(strerror(errno)));
      exit(EXIT_FAILURE);
     }
    }
  if(argc == 1){parseFile(0, first);}
 }
  struct Word* pointer1 = first->next;
  while(pointer1 != NULL){
   char outS[32];
   char* outI = convertInt(pointer1->count);
   strcpy(outS, pointer1->text);
   int sLen = 20 - strlen(pointer1->text);
   for(int s1 = sLen; s1 > 0; s1--){strcat(outS, " ");}
   strcat(outS, ":");
   int nLen = 10 - strlen(outI);
   for(int s2 = nLen; s2 > 0; s2--){strcat(outS, " ");}
   strcat(outS, outI);
   write(1, outS, strlen(outS));
   pointer1 = pointer1->next;
 }
 free(first);
 return 0;
}