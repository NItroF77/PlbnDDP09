#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
/*
underdevelopement note : BOT.
peraturan mengecek posisi menumpuk kata sebelumnya.
membuat bot.
*/

//modular list
void MainMenu();
void Game_Mode();
void ReadSavedData();
void SaveGame();
void HowToPlay();
void Credit();
void SeeHighScore();
void insert_data_player();
void Initiate_boardC();
void Initiate_boardH();
void show_table();
void ChangeTurn();
void InputTiles();
void Set_tiles();
void scramble();
int countLengthH(char word[]);
void SetHTiles();
void FindPos(char temp[],int *x,int *y);
int CheckCommand(char command[]);
void CheckCheat();
int SaveG(char command[]);
int CheckHoV(char letter);
int SetUpperCase(char letter);
int countLength(char word[]);
int starttime();
int endtime();
int CheckTiles(char compare[],char word[],int size_s, char dir, int x, int y);
int PutWord(char wordC[], int size_of_word,char Pos,int LocX,int LocY);
int FindWord(char *search_for_string,int size_s);
int Check_Pos(char Position,int LocX,int LocY,int length);
void add_score(char word[],int Location[][2]);
int Check_MultiT(int score,int LocationX,int LocationY);
int Check_MultiW(int temp_score,char word[],int Location[][2]);
void set_Bot_Pos(int x,int y,int range);
void ComputerTurn();
void BotEasy();
void BotHard();
void Bot_Put_Word(char word[]);
void fix_Bot_Pos(char Position,int LocX,int LocY,int length);
int BotCheckTiles(char Position,char word[]);
int Check_Bot_Pos(char Position,int LocX,int LocY,int length);
void end_game();
void InputScore();
void SortScore();
void OverWriteScore(char name[][30],int score[],int diff[],int idx);
void ResetGame();
// user defined data
typedef struct Player_Data{
	char usr[2][30];
	int scr[2];
}Players;
typedef struct Game_Data{
	int Diffiticulty;
	int GameMode;
	int BoardS[15][15];
	char BoardM[15][15];
}Dat;
typedef struct BotData{
	char Pos;
	int PosX,PosY;
}Bot;
//variabel global
int tcount=0;
int M;
int time_limit;
int turn=1;
int cht=0;
Players p;
Dat dat;
Bot bot;
FILE *ptr_to_file;
char tiles[8];
//modular-modular code
void MainMenu(){
	char empty=' ';
	int i,pilihan;
 	printf("%40.c%c",empty,201);
 	for(i=0;i<29;i++){printf("%c",205);}
	printf("%c",187);
	for(i=0;i<8;i++){
		printf("\n");printf("%40.c",empty);
		if(i==1){printf("%c%8.cSelamat Datang%7.c%c",186,empty,empty,186);}
		else if(i==2){printf("%c%7.cDI Game Scrabble%6.c%c",186,empty,empty,186);}
		else if(i==6){printf("%c%7.cBy NoobMaster69%7.c%c",186,empty,empty,186);}
		else{printf("%c%29.c%c",186,empty,186);}}
	printf("\n%40.c%c",empty,200);
 	for(i=0;i<29;i++){printf("%c",205);}printf("%c",188);
	printf("\n%50.cMain Menu :\n%50.c1.Continue Game \n%50.c2.New Game \n%50.c3.How to play \n%50.c4.HighScore \n%50.c5.Credit \n%50.c6.Exit\n",empty,empty,empty,empty,empty,empty,empty);
	scanf("%d",&pilihan);
	switch(pilihan){
		case 1 : system("cls");ReadSavedData();break;
		case 2 : system("cls");Game_Mode();break;
		case 3 : system("cls");HowToPlay();break;
		case 4 : SeeHighScore();break;
		case 5 : system("cls");Credit();break;
		case 6 : exit(1);break;
		default :system("cls");MainMenu();break;
	}
}
void ReadSavedData(){
	int i,j;
	if((ptr_to_file=fopen("savedat.txt","r"))==NULL){
		printf("Failed load data\n");
		getch();
		system("cls");
		MainMenu();
	}
	fscanf(ptr_to_file,"%d %d %d %d %d %d %s %d %s %d\n",&dat.Diffiticulty,&dat.GameMode,&tcount,&turn,&time_limit, &M,p.usr[0], &p.scr[0], p.usr[1], &p.scr[1]);
	for(i=0;i<M;i++){
		for(j=0;j<M;j++){
			fscanf(ptr_to_file,"%c ",&dat.BoardM[i][j]);
		}
	}
	printf("welcome back! %s and %s\n",p.usr[0], p.usr[1]);
   	fclose(ptr_to_file);
   	getch();
   	system("cls");
   	if(dat.Diffiticulty==2 || dat.Diffiticulty==3){
   		Initiate_boardH();
	   }
	else if (dat.Diffiticulty==1){
   		Initiate_boardC();
	   }
}
void SaveGame(){
	int i,j,cturn;
	if(turn==0){
		cturn=1;
	}
	else if(turn==1){
		cturn=0;
	}
	if((ptr_to_file=fopen("savedat.txt","w"))!=NULL){
		ptr_to_file=fopen("savedat.txt","w+");
	}
	fprintf(ptr_to_file,"%d %d %d %d %d %d %s %d %s %d\n",dat.Diffiticulty,dat.GameMode,tcount,cturn,time_limit, M, p.usr[0], p.scr[0], p.usr[1], p.scr[1]);
	for(i=0;i<M;i++){
		for(j=0;j<M;j++){
			fprintf(ptr_to_file,"%c ",dat.BoardM[i][j]);
		}
		fprintf(ptr_to_file,"\n");
	}
	printf("game saved successfully\n");
   	fclose(ptr_to_file);
   	getch();
}
void Game_Mode(){	
	int pilihan;
	char empty=' ';
	printf("%50.cPilih Game Mode : \n%50.c1. Player Vs Player \n%50.c2.Player Vs bot\n",empty,empty,empty);
	scanf("%d",&pilihan);
	switch(pilihan){
		case 1 : dat.GameMode=1,insert_data_player();break;
		case 2 : dat.GameMode=2;insert_data_player();break;
		default : printf("tidak ada pilihan angka tersebut");getch();system("cls");Game_Mode();break;
	}
}
void HowToPlay(){
	int i;
	char empty=' ';
	printf("\n%46.c%c",empty,201);
 	for(i=0;i<16;i++){printf("%c",205);}
	printf("%c",187);
	printf("\n%47.c%c%2.cHOW TO PLAY%3.c%c",186,empty,empty,186);
	printf("\n%46.c%c",empty,200);
 	for(i=0;i<16;i++){printf("%c",205);}printf("%c",188);
 	printf("\n\nPada Main Menu:");
	printf("\n1. Pilih Game Mode\n   Pilih mode Player Vs Player jika ingin melawan player lain atau pilih mode Player Vs Bot jika ingin\n   melawan bot (Komputer)");
	printf("\n2. Pilih tingkat kesulitan\n   Memilih tingkat kesulitan diantara Casual(Short Mode), Casual, dan Hard");
	printf("\n3. Memasukkan nama pemain");printf("\n\nSetelah pemain memilih mode, tingkat kesulitan, dan mengisi nama pemain maka game akan dimulai.\n\n");
	printf("1. Tiap pemain akan diberikan 7 buah huruf yang harus dirangkai menjadi sebuah kata\n");
	printf("2. Pemain harus menentukan format Vertikal (V) atau Horizontal (H) dan titik awal dengan format (kolom,baris).\n   Contoh: H,8,8 atau h,8,8\n");
	printf("3. Apabila kata yang dimasukkan itu benar maka giliran akan berganti. Namun bila kata yang dimasukkan itu salah,\n   maka player masih memiliki kesempatan untuk"); 
	printf("memasukkan kata lagi sebelum waktu yang dimiliki player habis.\n   Dan jika habis, maka giliran akan berganti.\n");
	printf("4. Pemain harus mengumpulkan skor sebanyak-banyaknya dengan membuat kata sepanjang mungkin, menggunakan huruf\n   yang memiliki skor tinggi, dan memanfaatkan blok yang dapat menggandakan skor\n");
	printf("5. Game akan berakhir apabila 100 huruf sudah terpakai\n6. Pemain yang memiliki skor paling banyak akan menjadi pemenangnya");
	printf("\n\nTekan tombol apapun untuk kembali ke Main Menu..");
	getch();
	system("cls");
	MainMenu();
}
void SeeHighScore(){
	int i,scr,diff;
	char user[30];
	SortScore();
	system("cls");
	if((ptr_to_file=fopen("scorelist.txt","r"))!=NULL){
		while(!feof(ptr_to_file)){
			fscanf(ptr_to_file,"%s %d %d\n",user,&diff,&scr);
			printf("%s %d %d\n",user,diff,scr);
		}
		
	}
	printf("\n\nTekan tombol apapun untuk kembali ke Main Menu..");
	getch();
	system("cls");
	MainMenu();
}
void Credit(){
	char empty=' ';
	printf("%40.c Credit By : \n %40.cFariz Muhammad Ibnu \n %40.cHanri Fajar \n %40.cRaihan Fuad S.",empty,empty,empty,empty);
	printf("\n\nTekan tombol apapun untuk kembali ke Main Menu..");
	getch();
	system("cls");
	MainMenu();
}
void SetDiff(){
	int choose;
	char empty=' ';
	printf("%45cPilih tingkat kesulitan \n%45c1. Casual (Short Mode) \n%45c2. Casual \n%45c3. Hard\n",empty,empty,empty,empty);
	scanf("%d",&choose);
	switch(choose){
		case 1 : dat.Diffiticulty=1;time_limit=80;Initiate_boardC();break;
		case 2 : dat.Diffiticulty=2;time_limit=80;Initiate_boardH();break;
		case 3 : dat.Diffiticulty=3;time_limit=40;Initiate_boardH();break;
		default : printf("maaf tidak ada pilihan angka tersebut");getch();system("cls");SetDiff();break;
	}
}
void Initiate_boardC(){
	int i,j,k=10;
	int boardscr[10][10]={
				{2,1,1,1,1,3,1,1,1,2},
				{1,2,1,1,3,1,1,1,2,1},
				{1,1,2,1,1,1,1,2,1,1},
				{1,1,1,2,1,1,2,1,1,1},
				{3,1,1,1,3,3,1,1,1,2},
				{1,3,1,1,3,3,1,1,3,1},
				{1,1,1,2,1,1,2,1,1,1},
				{1,1,2,1,1,1,1,2,1,1},
				{1,2,1,1,3,1,1,1,2,1},
				{2,1,1,1,1,3,1,1,1,2},
				};
	for(i=0;i<k;i++){
		for(j=0;j<k;j++){
			dat.BoardS[i][j]=boardscr[i][j];
		}
	}
	M=10;
}
void Initiate_boardH(){
	int i,j,k=15;
	int boardscr[15][15]={
				{7,1,1,1,1,7,1,1,1,7,1,1,1,1,7},
				{1,2,1,1,1,1,6,1,6,1,1,1,1,2,1},
				{1,1,2,1,1,1,1,7,1,1,1,1,2,1,1},
				{1,1,1,2,1,1,1,1,1,1,1,2,1,1,1},
				{1,1,1,1,6,1,1,1,1,1,6,1,1,1,1},
				{7,1,1,1,1,6,1,1,1,6,1,1,1,1,7},
				{1,6,1,1,1,1,6,1,6,1,1,1,1,6,1},
				{1,1,7,1,1,1,1,5,1,1,1,1,7,1,1},
				{1,6,1,1,1,1,6,1,6,1,1,1,1,6,1},
				{7,1,1,1,1,6,1,1,1,6,1,1,1,1,7},
				{1,1,1,1,6,1,1,1,1,1,6,1,1,1,1},
				{1,1,1,2,1,1,1,1,1,1,1,2,1,1,1},
				{1,1,2,1,1,1,1,3,1,1,1,1,2,1,1},
				{1,2,1,1,1,1,6,1,6,1,1,1,1,2,1},
				{7,1,1,1,1,7,1,1,1,7,1,1,1,1,7}};
	for(i=0;i<k;i++){
		for(j=0;j<k;j++){
			dat.BoardS[i][j]=boardscr[i][j];
		}
	}
	M=15;
}
void insert_data_player(){
	int i,j;
	char bot_name[]="GAROX";
	if(dat.GameMode==1){
		j=2;
	}
	else{
		j=1;
		strcpy(p.usr[1],bot_name);
	}
	system("cls");
	SetDiff();
		for(i=0;i<j;i++){
			printf("masukan nama Player %d :\n",i+1);
			fflush(stdin);
			gets(p.usr[i]);
		}
		printf("Selamat Datang %s dan %s\n",p.usr[0],p.usr[1]);
		p.scr[0]=0;p.scr[1]=0;
		getch();
		system("cls");
}
void show_board(){
	int i,j;
	char empty=' ';
	printf("%6.c1  ",empty);
	for(i=1;i<M;i++){
		if(i<9){
			printf(" %d  ",i+1);
		}
		else{
		printf(" %d ",i+1);
		}
	}
	printf("\n%4.c",empty);
	printf("%c",201);
	for(i=1;i<M+6;i++){
		printf("%c%c%c",205,205,205);
	}
	printf("\n");
	for(i=0;i<M;i++){
		if(i<9){
			printf(" %d  %c",i+1,186);
		}
		else{
		printf(" %d %c",i+1,186);
		}
		for(j=0;j<M;j++){
			if(dat.BoardM[i][j]=='\0'){
				switch(dat.BoardS[i][j]){
					case 1 : printf(" *  ");break;
					case 6 : printf(" 2W ");break;
					case 7 : printf(" 3W ");break;
					default : printf(" %d  ",dat.BoardS[i][j]);break;
				}
			}
			else{
				printf(" %c  ",dat.BoardM[i][j]);
			}
		}
		printf("\n");
		printf("    %c\n",186);
	}
	switch(dat.Diffiticulty){
		case 1 : printf("Game Difficulty : Casual (Short Mode)\n");break;
		case 2 : printf("Game Difficulty : Casual \n");break;
		case 3 : printf("Game Difficulty : Hard\n");break;
	}
	printf("%s with score : %d Vs %s with score : %d\n",p.usr[0],p.scr[0],p.usr[1],p.scr[1]);
	printf("%d letter left\n",100-tcount);
	InputTiles();
}
void ChangeTurn(){
	if(turn==0){
		turn=1;
	}
	else if(turn==1){
		turn=0;
	}
}
void InputTiles(){	
	char cnfrm,Position;
	int i,PosX,PosY,countL,tempx1,tempx2,tempy1,tempy2;
	int PosWord[7][2];
	int current_time;
	double time_passed;
	char word[1024];
	char temp[7];
	ChangeTurn();
	char ctiles1[8];char ctiles2[8];
	printf("%s's Turn\n",p.usr[turn]);
	if(dat.Diffiticulty==1 || dat.Diffiticulty==2){Set_tiles();strcpy(ctiles1,tiles);}
	else{SetHTiles();strcpy(ctiles1,tiles);
		scramble(ctiles1,countLengthH(ctiles1));}
	menu :
			strcpy(ctiles2,ctiles1);
			CheckCheat();
			for(i=0;i<7;i++){
				printf("%c ",ctiles2[i]);
			}
			printf("\n");
			printf("Vertical (V) or Horizontal (H) and the initial point with format (column,row), ex: H,8,8 or h,8,8\n");
			current_time=starttime();
			printf("your time to input is %d second\n",time_limit);
			fflush(stdin);
			gets(temp);
			Position=temp[0];
			FindPos(temp,&PosX,&PosY);
			if((CheckCommand(temp))==1){turn=1;goto end;}
			if((SaveG(temp))==1){goto menu;}
			Position=SetUpperCase(Position);
			if(CheckHoV(Position)==0){
				printf("incorrect input position\n");
				getch();
				goto menu;
			}
			if(PosX>M || PosY>M){
				printf("Position Exceed board\n");
				getch();
				goto menu;
			}
			fflush(stdin);
			printf("Please input a word\n");
			gets(word);
			current_time=endtime()-current_time;
			time_passed=((double)current_time)/CLOCKS_PER_SEC;
			countL=countLength(word);
			for(i=0;word[i]!='\0';i++){
				word[i]=SetUpperCase(word[i]);
			}
			printf("%s is word you want to input? Y or N\n",word);
			fflush(stdin);
			scanf("%c",&cnfrm);
			if(cnfrm=='N' || cnfrm=='n'){
				goto menu;
			}
			if(CheckTiles(ctiles2,word,countL,Position,PosX-1,PosY-1) && PutWord(word,countL,Position,PosX-1,PosY-1) && time_passed<=time_limit){
				if(Position=='V'){
					for(i=0;word[i]!='\0';i++){
						PosWord[i][0]=PosX-1;
						PosWord[i][1]=PosY-1;
						dat.BoardM[PosY-1][PosX-1]=word[i];
						PosY++;
					}
					PosY-=i;
				}
				else if(Position=='H'){
					for(i=0;word[i]!='\0';i++){
						PosWord[i][0]=PosX-1;
						PosWord[i][1]=PosY-1;
						dat.BoardM[PosY-1][PosX-1]=word[i];
							PosX++;
						}
						PosX-=i;
					}
				add_score(word,PosWord);
				printf("Word that you input has been placed\n");
				tcount+=countL;
				}
			else if(time_passed>time_limit){
				printf("time's up\n");
				getch();
				system("cls");
				show_board();
			}
			else{
				printf("word that you input failed to be placed\n");
				goto menu;
				}
	end :
	if(dat.GameMode==2 && turn==0){
		if(Position=='V'){bot.Pos='H';}else if(Position=='H'){bot.Pos='V';}
		turn=1;
		set_Bot_Pos(PosX-1,PosY-1,countL);
	}
	system("cls");
}
void Set_tiles(){
	int i;
	srand(time(0));
		for(i=0;i<7;i++){
		tiles[i]="AAAAAAAAAABBCCDDDDEEEEEEEEEEFFGGGHHIIIIIIIIIJKLLLLLMMNNNNNNOOOOOOOPPQRRRRRRSSSSTTTTTTUUUUVVWWXYYZ"[rand() % 97];
	}
}
void CheckCheat(){
	if(cht==1 && dat.Diffiticulty==3){
		printf("%s\n",tiles);
	}
}
void scramble(char *ptr, int length){
    int i = 0;

    while(i < length)
    {
        int c1 = (rand() % (length));
        int c2 = (rand() % (length));

        if(c1 != c2)
        {
            ptr[c1] = ptr[c1] ^ ptr[c2];
            ptr[c2] = ptr[c1] ^ ptr[c2];
            ptr[c1] = ptr[c1] ^ ptr[c2];

            i++;
        }
    }
}
int countLengthH(char word[]){
	int i,count=0;
	for(i=0;word[i]!='\n';i++){
		count++;
	}
	return count;
}
void SetHTiles(){
    int i,size_s,cek=0,randomN,count=-1;
    char letter[2];
    char word[1024];
    menu :
    srand(time(0));
    letter[0]="ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand() % 26];
    letter[1]="AIUEO"[rand() % 5];
    randomN=rand() % 3;
    ptr_to_file = fopen("words.txt", "r");
    while (fgets(word, sizeof(word), ptr_to_file) != NULL)
    {
        if (word[0] == letter[0] && word[1]==letter[1])
        {
        	strcpy(tiles,word);
        	size_s=countLengthH(tiles);
            if(size_s==7){
            	count++;
            	if(count==randomN){
				cek=1;
            	fclose(ptr_to_file);
				}
        	}
   		}
	}
	if(cek==0){
		goto menu;
	}
}
int SetUpperCase(char letter){
	if(letter>90){
		return letter-32;
	}
	return letter;
}
void FindPos(char temp[],int *x,int *y){
	int tempx1,tempx2,tempy1,tempy2;
			if(temp[4]==','){
				tempx1=((char)temp[2])-'0';
				tempx2=((char)temp[3])-'0';
				if(temp[6]!='\0'){
					tempy1=((char)temp[5])-'0';
					tempy2=((char)temp[6])-'0';
				}
				else{
					tempy1=((char)temp[5])-'0';
					tempy2=-1;
				}
			}
			else{
				tempx1=((char)temp[2])-'0';
				tempx2=-1;
				if(temp[5]!='\0'){
					tempy1=((char)temp[4])-'0';
					tempy2=((char)temp[5])-'0';
				}
				else{
					tempy1=((char)temp[4])-'0';
					tempy2=-1;
				}
			}
			if(tempx2==-1){
				*x=tempx1;
			}
			else{
				*x=tempx1*10+tempx2;
			}
			if(tempy2==-1){
				*y=tempy1;
			}
			else{
				*y=tempy1*10+tempy2;
			}
}
int CheckHoV(char letter){
	if(letter=='V' || letter=='H'){
		return 1;
	}
	return 0;
}
int countLength(char word[]){
	int i,count=0;
	for(i=0;word[i]!='\0';i++){
		count++;
	}
	return count;
}
int SaveG(char command[]){
	char save[]="!save";
	if((strstr(command,save))!=NULL){
		SaveGame();
		return 1;
	}
	return 0;
}
int CheckCommand(char command[]){
	char pass[]="!pass";
	char forfeit[]="!forfeit";
	char endG[]="!endgame";
	char cheat[]="!debug";
		if((strstr(command,forfeit))!=NULL){
			p.scr[turn]=0;
			tcount+=100;
			return 1;
		}
		else if((strstr(command,pass))!=NULL){
			getch();
			return 1;
		}
		else if((strstr(command,endG))!=NULL){
			tcount+=100;
			return 1;
		}
		else if((strstr(command,cheat))!=NULL){
			if(cht==0){cht=1;}
			else{cht=0;}
			return 1;
		}
	return 0;
}
int CheckTiles(char compare[],char word[],int size_s, char dir, int x, int y){
 	int i,j,check1,check2;
 	for(i=0;word[i]!='\0';i++){
 		check1=0;
 		check2=0;
 		for(j=0;compare[j]!='\0';j++){
 			if(word[i]==compare[j] || word[i]==dat.BoardM[y][x]){
 				compare[j]='*';
 				check1=1;
 				break;
			}
		}
		if(word[i]==dat.BoardM[y][x] || dat.BoardM[y][x]=='\0'){
				check2=1;
			}
		else{
			printf("your word positioning overlap with other\n");
			getch();
		}
		if(check1==0 || check2==0){
			printf("incorrect letter's input\n");
			return 0;
		}
		if(dir=='V'){
 			y++;
		}
		else if(dir=='H'){
			x++;
		}
	 }
	 return 1;
}
int PutWord(char wordC[], int size_of_word,char Pos,int LocX,int LocY){
	if(FindWord(wordC,size_of_word)==1 && Check_Pos(Pos,LocX,LocY,size_of_word)){
		return 1;
	}
	else if(FindWord(wordC,size_of_word)==2){
		printf("exceed limit input\n");
		return 0;
	}
	return 0;
}
int FindWord(char *search_for_string,int size_s){
    int i;
    char word[1024];
    char last_case[]="ZZZS";
    if(dat.Diffiticulty==3){
    	if((strstr(tiles,search_for_string))!=NULL){
    		return 1;
		}
		else{
			return 0;
		}
	}
    else{
    	if(strstr(last_case,search_for_string)!=NULL){
    		return 1;
		}
    	ptr_to_file = fopen("words.txt", "r");
    	while (fgets(word, sizeof(word), ptr_to_file) != NULL)
    	{
        	if (strstr(word, search_for_string) != NULL)
        	{
            	if(size_s>7){
            		fclose(ptr_to_file);
                	return 2;
            	}
            	else if(size_s==7 || size_s<3){
            		fclose(ptr_to_file);
                	return 1;
            	}
            	else if(strlen(word)==size_s+1){
            		fclose(ptr_to_file);
                	return 1;
            	}
        	}
    	}
    	fclose(ptr_to_file);
    	return 0;
	}
}
int Check_Pos(char Position,int LocX,int LocY,int length){
	if(Position=='H'){
		if(LocX+length<=M){
			return 1;
		}
	}
	else if(Position=='V'){
		if(LocY+length<=M){
			return 1;
		}
	}
	printf("exceed board\n");
	return 0;
}
void add_score(char word[],int Location[][2]){
	int i,total_score=0,scoreL=0;
	for(i=0;word[i]!='\0';i++){
		scoreL=0;
		if(word[i]=='A'|| word[i]=='E' || word[i]=='I' || word[i]=='L'  || word[i]=='N' || word[i]=='O' || word[i]=='R' || word[i]=='S' || word[i]=='T' || word[i]=='U'){
			scoreL+=1;
		}
		else if(word[i]=='D' || word[i]=='G'){
			scoreL+=2;
		}
		else if(word[i]=='B' || word[i]=='C' || word[i]=='M' || word[i]=='P'){
			scoreL+=3;
		}
		else if(word[i]=='F' || word[i]=='H' || word[i]=='V' || word[i]=='W' || word[i]=='d' || word[i]=='Y'){
			scoreL+=4;
		}
		else if(word[i]=='K'){
			scoreL+=5;
		}
		else if(word[i]=='J' || word[i]=='X'){
			scoreL+=8;
		}
		else if(word[i]=='Q' || word[i]=='Z'){
			scoreL+=10;
		}
		scoreL=Check_MultiT(scoreL,Location[i][0],Location[i][1]);
		total_score+=scoreL;
	}
	total_score=Check_MultiW(total_score,word,Location);
	p.scr[turn]=p.scr[turn]+total_score;
}
int Check_MultiT(int score,int LocationX,int LocationY){
	if(dat.BoardS[LocationY][LocationX]==1 || dat.BoardS[LocationY][LocationX]==6 || dat.BoardS[LocationY][LocationX]==7){
		return score*1;
	}
	else if(dat.BoardS[LocationY][LocationX]==2){
		return score*2;
	}
	else if(dat.BoardS[LocationY][LocationX]==3){
		return score*3;
	}
	else if(dat.BoardS[LocationY][LocationX]==5){
		return score*5;
	}
}
int Check_MultiW(int temp_score,char word[],int Location[][2]){
	int i;
	for(i=0;word[i]!='\0';i++){
		if(dat.BoardS[Location[i][0]][Location[i][1]]==6){
			temp_score=temp_score*2;
		}
		else if(dat.BoardS[Location[i][0]][Location[i][1]]==7){
			temp_score=temp_score*3;
		}
	}
	if(countLength(word)==7){
		temp_score=temp_score*5;
	}
	return temp_score;
}
void set_Bot_Pos(int x,int y,int range){
	int min=0,max=3,randomN1,randomN2,i;
	srand(time(0));
	randomN1=(rand() % (range-min))+min;
	randomN2=(rand() % (max-min))+min;
	if(bot.Pos=='H'){
		bot.PosY=y+randomN1;
		bot.PosX=x-randomN2;
	}
	else if(bot.Pos=='V'){
		bot.PosX=x+randomN1;
		bot.PosY=y-randomN2;
	}
	if(bot.PosX<0){
		for(i=0;bot.PosX<0;i++){
			bot.PosX++;
		}
	}
	if(bot.PosY<0){
		for(i=0;bot.PosY<0;i++){
			bot.PosY++;
		}
	}
	ComputerTurn();
}
void ComputerTurn(){
	switch(dat.Diffiticulty){
		case 3 : BotHard();break;
		default : BotEasy();break;
	}
}
void BotEasy(){	
	char word[8];
	int min=3,max=5,length;
	menu :
	srand(time(0));
	length=(rand() % (max-min+1))+min;
	fix_Bot_Pos(bot.Pos,bot.PosX,bot.PosY,length);
	if((ptr_to_file=fopen("words.txt","r"))!=NULL){
		while(!feof(ptr_to_file)){
			fscanf(ptr_to_file,"%s\n",word);
			if(countLength(word)==length && Check_Bot_Pos(bot.Pos,bot.PosX,bot.PosY,countLength(word)) && BotCheckTiles(bot.Pos,word)){
				Bot_Put_Word(word);
				break;
			}
		}
	}
	else{
		printf("error load words.txt\n");
		getch();
	}
	fclose(ptr_to_file);
}
void BotHard(){
	char word[8];
	fix_Bot_Pos(bot.Pos,bot.PosX,bot.PosY,7);
	if((ptr_to_file=fopen("words.txt","r"))!=NULL){
		while(!feof(ptr_to_file)){
			fscanf(ptr_to_file,"%s\n",word);
			if(countLength(word)==7 && Check_Bot_Pos(bot.Pos,bot.PosX,bot.PosY,countLength(word)) && BotCheckTiles(bot.Pos,word)){
				Bot_Put_Word(word);
				break;
			}
		}
	}
	else{
		printf("error load words.txt\n");
		getch();
	}
	fclose(ptr_to_file);
}
void fix_Bot_Pos(char Position,int LocX,int LocY,int length){ 
	if(Position=='H'){
		if(LocX+length>M){
			LocX-=length-1;
		}
	}
	else if(Position=='V'){
		if(LocY+length>M){
			LocY-=length-1;
		}
	}
	bot.PosX=LocX;
	bot.PosY=LocY;
}
int Check_Bot_Pos(char Position,int LocX,int LocY,int length){
	if(Position=='H'){
		if(LocX+length<=M){
			return 1;
		}
	}
	else if(Position=='V'){
		if(LocY+length<=M){
			return 1;
		}
	}
	return 0;
}
int BotCheckTiles(char Position,char word[])
{
	int i,check=1;
	if(Position=='H'){
		for(i=0;word[i]!='\0';i++){
			if(word[i]!=dat.BoardM[bot.PosY][bot.PosX+i] && dat.BoardM[bot.PosY][bot.PosX+i]!='\0'){
				check=0;
				break;
			}
		}
	}
	else if(Position=='V'){
		for(i=0;word[i]!='\0';i++){
			if(word[i]!=dat.BoardM[bot.PosY+i][bot.PosX] && dat.BoardM[bot.PosY+i][bot.PosX]!='\0'){
				check=0;
				break;
			}
		}
	}
	if(check==1){
		return 1;
	}
	else{
		return 0;
	}
}
void Bot_Put_Word(char word[])
{
	int i;
	int Loc[7][2];
	if(bot.Pos=='H'){
		for(i=0;word[i]!='\0';i++){
		Loc[i][0]=bot.PosX+i;
		Loc[i][1]=bot.PosY;
		dat.BoardM[bot.PosY][bot.PosX+i]=word[i];
		}
	}
	if(bot.Pos=='V'){
		for(i=0;word[i]!='\0';i++){
		Loc[i][0]=bot.PosX;
		Loc[i][1]=bot.PosY+i;
		dat.BoardM[bot.PosY+i][bot.PosX]=word[i];
		}
	}
	add_score(word,Loc);
	tcount+=countLength(word);
}

void end_game(){
	char empty=' ';
	char cnfrm;
	if(p.scr[0]>p.scr[1]){
	printf("The winner is %s with score %d\n",p.usr[0],p.scr[0]);
	}
	else if(p.scr[0]<p.scr[1]){
	printf("The winner is %s with score %d\n",p.usr[1],p.scr[1]);
	}
	else{
		printf("Draw with score %d\n",p.scr[0]);
	}
	getch();
	InputScore();
	printf("Want to play Again? (Y/N)\n");
	fflush(stdin);
	scanf("%c",&cnfrm);
	if(cnfrm=='Y' || cnfrm=='y'){
		ResetGame();
	}
	else{
			system("cls");
	printf("%55c%s",empty,"Good Bye\n");
	getch();
	exit(1);
	}
}
void ResetGame(){
	int i,j;
	p.scr[0]=0;p.scr[1]=0;
	tcount=0;
	turn=1;
	for(i=0;i<M;i++){
		for(j=0;j<M;j++){
			dat.BoardM[i][j]='\0';
		}
	}
}
void InputScore(){
	ptr_to_file=fopen("scorelist.txt","a+");
	fprintf(ptr_to_file,"%s %d %d\n%s %d %d\n",p.usr[0],dat.Diffiticulty,p.scr[0],p.usr[1],dat.Diffiticulty,p.scr[1]);
	fclose(ptr_to_file);
}
void SortScore(){
	int idx=0,i,j;
	int scr_t;
	int diff_t;
	char name_t[30];
	int score[100];
	char name[100][30];
	int diff[100];
	ptr_to_file=fopen("scorelist.txt","r");
	while(!feof(ptr_to_file)){
		fscanf(ptr_to_file,"%s %d %d\n",name[idx],&diff[idx],&score[idx]);
		idx++;
	}
	for(j=0;j<idx;j++){
		for(i=0;i<idx;i++){
			if(score[i+1]>score[i]){
				strcpy(name_t,name[i+1]);
				scr_t=score[i+1];
				diff_t=diff[i+1];
				strcpy(name[i+1],name[i]);
				score[i+1]=score[i];
				diff[i+1]=diff[i];
				strcpy(name[i],name_t);
				score[i]=scr_t;
				diff[i]=diff_t;
			}
		}
	}
	
	OverWriteScore(name,score,diff,idx);
}
void OverWriteScore(char name[][30],int score[],int diff[],int idx){
	int i;
	ptr_to_file=fopen("scorelist.txt","w+");
	for(i=0;i<=idx;i++){
		fprintf(ptr_to_file,"%s %d %d\n",name[i],diff[i],score[i]);
	}
	fclose(ptr_to_file);
}
int starttime(){
    clock_t t;
    t = clock();
    return t;
}
int endtime(){
    clock_t t;
    t = clock();
    return t;
}
int main(){
	int tilesLimit;
	dat.Diffiticulty=5;
	MainMenu();
	switch(dat.Diffiticulty){
		case 1 : tilesLimit=30;break;
		default : tilesLimit=100;break;
	}
	menu :
	if(dat.Diffiticulty<=3){
		while(tcount<tilesLimit){
			show_board();
		}
		end_game();
	}
	if(tcount==0){
		goto menu;
	}
	return 0;
}