#include <stdio.h>

int main () {
   FILE *fp;
   char str[]="THIS";

   /* opening file for reading */
   fp = fopen("words.txt" , "r");
   if(fp == NULL) {
      perror("Error opening file");
      return(-1);
   }
   while(!feof(fp))
   {
      if( fgets (str, 60, fp)!=NULL ) {
      puts(str);
    }
   }
   fclose(fp);
   return(0);
}