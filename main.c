#include "FindWord.h"
#include <stdio.h>
#include <string.h>
int main(){
	char word[30];
	gets(word);
	if(FindWord(word)==1){
		printf("Kata yang dicari ketemu");
	}
	else{
		printf("Kata yang dicari tidak ketemu");
	}
	return 0;
}