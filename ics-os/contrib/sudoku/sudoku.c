/*
	SUDOKU
	CMSC 125 PROJECT
	AY 2015-2016, SECOND SEMESTER

	CREATED BY:
	REYNALDO BAYETA III
	FRANCIS DEOFERIO
	ROSECHELLE JOY ORAA
*/

#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"
#include "levels.h"

#define START 1
#define INSTRUCTIONS 2
#define HIGHSCORES 3
#define QUIT 4

#define GAME_OVER 1
#define GAME_RESET 'r'
#define GAME_QUIT 'q'
#define TILE_ERASE 'e'

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define ENTER '\n'

#define YELLOW 54
#define PALE_YELLOW 62
#define ROYAL_BLUE 1
#define DARK_BLUE 8
#define GRAY 56
#define GREEN 2
#define WHITE 63

int xIndex = 0;
int yIndex = 0;
int init_state[9][9];
int board_value[9][9];

void erase();
void drawCurrPos();
void drawFixTile();
void initializeBoard();
void Controls();
int StartPage();
int CheckBoard();
int CheckEmpty();
void highlightBoard();
int DifficultyPage();
int LevelPage();
void InstructionsPage();
void DrawBoard();
void ResetGame();
void ViewHighScores();
void UpdateHighscores();

int main(){
	initializeBoard();
	char keypress, temp[10]; 
	
	int choice = 0, difficulty = 0, level = 0;
	int board[9][9];
	set_graphics(VGA_320X200X256);
	
	erase(1,1,400,200); //change page
	Controls();


	do{
		choice = StartPage();

		switch(choice){
			case START : 
				difficulty = DifficultyPage();	//print page
				level = LevelPage();

				generateLevel(init_state,difficulty,level);
				DrawBoard(difficulty, level);
				break;
			case INSTRUCTIONS :
				InstructionsPage();	//print page
				break;
			case HIGHSCORES :
				//ViewHighScores();
				break;
		}

	}while(choice != QUIT);

	
	set_graphics(VGA_TEXT80X25X16);
	clrscr();
}

//lightsout.exe
void erase(int x, int y, int width, int height){
    int i, j;
    for (i = y; i < (y+height); i++){
        for(j = x; j < (x+width); j++){
            write_pixel(j, i, 100);
        }
    }
}

void drawCurrPos(int x, int y){
    int i, j;
    for (i = y; i < y+17; i++){
        for(j = x; j < x+22; j++){
            write_pixel(j, i, GREEN);
        }
    }
}

//for tiles that cannot be modified
void drawFixTile(int x, int y){
    int i, j;
    for (i = y; i < y+17; i++){
        for(j = x; j < x+22; j++){
            write_pixel(j, i, GRAY);
        }
    }
}

void initializeBoard(){
	int i, j;	
	for(i = 0; i < 9; i++)
		for(j = 0; j < 9; j++){
			board_value[i][j] = -1;
		}
}

void Controls(){

	write_text("Controls :",40,40,WHITE,0); 
	write_text("/\\",145,30,WHITE,0); 
	write_text("||",145,45,WHITE,0); 
	write_text("W",150,60,WHITE,0); 
	write_text("S",150,75,WHITE,0); 
	write_text("<== A",80,75,WHITE,0);
	write_text("D ==>",180,75,WHITE,0);
	write_text("||",145,90,WHITE,0);
	write_text("\\/",145,105,WHITE,0);
	write_text("            |",100,120,WHITE,0);
	write_text("  ENTER  <--'",100,130,WHITE,0);
	write_text("SELECT",130,140,WHITE,0);

	write_text("Select to continue . . .",70,180,WHITE,0);

	while((char)getch()!=ENTER){}
}

//display homepage
int StartPage(){

	erase(1,1,400,200); //change page

	char key, temp[10];
	int i,j, choice=1, xcoord=150, ycoord=80;

	for (i = 0; i < 400; i++){
        for(j = 0; j < 200; j++){
        	if(i==20 || i==180) write_pixel(j, i, YELLOW);
        	if(j==20 || i==380) write_pixel(j, i, YELLOW);
        }
    }

	write_text("SUDOKU!",45,50,WHITE,1);

	write_text("Start",180,80,WHITE,0); 
	write_text("Instructions",180,100,WHITE,0);
	write_text("High Scores",180,120,WHITE,0);
	write_text("Quit",180,140,WHITE,0);

	write_text(">>",150,80,WHITE,0); 

	do{
		key = (char) getch();

		switch(key){
			case UP:
			case LEFT:
				choice--;
				erase(xcoord,ycoord,30,20);
				ycoord-=20;
				break;
			case DOWN:
			case RIGHT:
				choice++;
				erase(xcoord,ycoord,30,20);
				ycoord+=20;
				break;
		}

		if(choice==0){
			choice=4;
			ycoord=140;
		}else if(choice==5){
			choice=1;
			ycoord=80;
		}

		write_text(">>",xcoord,ycoord,WHITE,0); 

	}while(key!=ENTER);

	return choice;
}


int CheckBoard(int xcoord, int ycoord){
	int i, j;
	int a, b;
	char str[10];

	//x / row checker
	for(i = 0; i < 9; i++){
		for(j = i + 1; j < 9; j++){
			if(board_value[i][xIndex] == -1)
				continue;
			if(board_value[i][xIndex] == board_value[j][xIndex]){
				highlightBoard(xcoord, ycoord);
				return -1;
			}
		}	
	}

	//y / column checker
	for(i = 0; i < 9; i++){
		for(j = i + 1; j < 9; j++){
			if(board_value[yIndex][i] == -1)
				continue;
			if(board_value[yIndex][i] == board_value[yIndex][j]){
				highlightBoard(xcoord, ycoord);
				return -1;
			}
		}
	}


	/*******************
	 CLUSTER ORIENTATION 
		 1   2   3
		 4   5   6
		 7   8   9
	********************/


	//first cluster checking
	if(yIndex <= 2 && xIndex <= 2){

		//looping the array to get a value
		for(i = 0; i <= 2; i++){
			for(j = 0; j <= 2; j++){

				//looping the array to compare the value to all values in the array
				for(a = 0; a <= 2; a++){
					for(b = 0; b <= 2; b++){

						//will compare empty index
						if(board_value[i][j] == -1)
							continue;
						//will compare with itself
						if(i == a && j == b)
							continue;
						if(board_value[i][j] == board_value[a][b]){
							highlightBoard(xcoord, ycoord);
							return -1;
						}
					}
				}
			}
		}
	}

	//second cluster checking
	else if(yIndex <= 2 && xIndex <= 5 && xIndex > 2){

		for(i = 0; i <= 2; i++){
			for(j = 3; j <= 5; j++){

				for(a = 0; a <= 2; a++){
					for(b = 3; b <= 5; b++){

						if(board_value[i][j] == -1)
							continue;
						if(i == a && j == b)
							continue;
						if(board_value[i][j] == board_value[a][b]){
							highlightBoard(xcoord, ycoord);
							return -1;
						}

					}
				}
			}
		}	
	}

	//third cluster checking
	else if(yIndex <= 2 && xIndex <= 8 && xIndex > 5){

		for(i = 0; i <= 2; i++){
			for(j = 6; j <= 8; j++){

				for(a = 0; a <= 2; a++){
					for(b = 6; b <= 8; b++){

						if(board_value[i][j] == -1)
							continue;
						if(i == a && j == b)
							continue;
						if(board_value[i][j] == board_value[a][b]){
							highlightBoard(xcoord, ycoord);
							return -1;
						}
					}
				}
			}
		}	
	}

	//fourth cluster checking
	else if(yIndex <= 5 && yIndex > 2 && xIndex <= 2){
		
		for(i = 3; i <= 5; i++){
			for(j = 0; j <= 2; j++){

				for(a = 3; a <= 5; a++){
					for(b = 0; b <= 2; b++){

						if(board_value[i][j] == -1)
							continue;
						if(i == a && j == b)
							continue;
						if(board_value[i][j] == board_value[a][b]){
							highlightBoard(xcoord, ycoord);
							return -1;
						}
					}
				}
			}
		}
	}

	//fifth cluster checking
	else if(yIndex <= 5 && yIndex > 2 && xIndex <= 5 && xIndex > 2){

		for(i = 3; i <= 5; i++){
			for(j = 3; j <= 5; j++){

				for(a = 3; a <= 5; a++){
					for(b = 3; b <= 5; b++){

						if(board_value[i][j] == -1)
							continue;
						if(i == a && j == b)
							continue;
						if(board_value[i][j] == board_value[a][b]){
							highlightBoard(xcoord, ycoord);
							return -1;
						}
					}
				}
			}
		}	
	}

	//sixth cluster checking
	else if(yIndex <= 5 && yIndex > 2 && xIndex <= 8 && xIndex > 5){

		for(i = 3; i <= 5; i++){
			for(j = 6; j <= 8; j++){

				for(a = 3; a <= 5; a++){
					for(b = 6; b <= 8; b++){

						if(board_value[i][j] == -1)
							continue;
						if(i == a && j == b)
							continue;
						if(board_value[i][j] == board_value[a][b]){
							highlightBoard(xcoord, ycoord);
							return -1;
						}
					}
				}
			}
		}	
	}

	//seventh cluster checking
	else if(yIndex <= 8 && yIndex > 5 && xIndex <= 2){

		for(i = 6; i <= 8; i++){
			for(j = 0; j <= 2; j++){

				for(a = 6; a <= 8; a++){
					for(b = 0; b <= 2; b++){

						if(board_value[i][j] == -1)
							continue;
						if(i == a && j == b)
							continue;
						if(board_value[i][j] == board_value[a][b]){
							highlightBoard(xcoord, ycoord);
							return -1;
						}
					}
				}
			}
		}	
	}

	//eighth cluster checking
	else if(yIndex <= 8 && yIndex > 5 && xIndex <= 5 && xIndex > 2){

		for(i = 6; i <= 8; i++){
			for(j = 3; j <= 5; j++){

				for(a = 6; a <= 8; a++){
					for(b = 3; b <= 5; b++){

						if(board_value[i][j] == -1)
							continue;
						if(i == a && j == b)
							continue;
						if(board_value[i][j] == board_value[a][b]){
							highlightBoard(xcoord, ycoord);
							return -1;
						}
					}
				}
			}
		}	
	}

	//ninth cluster checking
	else if(yIndex <= 8 && yIndex > 5 && xIndex <= 8 && xIndex > 5){
		
		for(i = 6; i <= 8; i++){
			for(j = 6; j <= 8; j++){

				for(a = 6; a <= 8; a++){
					for(b = 6; b <= 8; b++){

						if(board_value[i][j] == -1)
							continue;
						if(i == a && j == b)
							continue;
						if(board_value[i][j] == board_value[a][b]){
							highlightBoard(xcoord, ycoord);
							return -1;
						}
					}
				}
			}
		}
	}

	return 0;
}
//returns 0 if all cells in the board has been filled, otherwise return -1
int CheckEmpty(){
	int i, j;

	for(i = 0; i < 9; i++){		
		for(j = 0; j < 9; j++){
			if(board_value[i][j] == -1)
				return -1;
		}
	}

	return 0;
}

void highlightBoard(int x, int y){
    int i, j;
    for (i = y; i < y+17; i++){
        for(j = x; j < x+22; j++){
            write_pixel(j, i, RED);
        }
    }
}

//display difficulty picking
int DifficultyPage(){
	//difficulty options
	erase(1,1,400,200); //change page

	char key;
	int choice=1, xcoord=50, ycoord=83;

	write_text("Select Dificulty",80,40,WHITE,0);

	write_text("Easy",50,80,WHITE,0); 
	write_text("Medium",130,80,WHITE,0);
	write_text("Hard",220,80,WHITE,0);
	write_text("_____",xcoord,ycoord,WHITE,0); 

	do{
		key = (char) getch();

		switch(key){
			case LEFT:
				choice--;
				erase(xcoord,ycoord+5,80,3);
				xcoord-=80;
				break;
			case RIGHT:
				choice++;
				erase(xcoord,ycoord+5,80,3);
				xcoord+=80;
				break;
		}

		if(choice==0){
			choice=3;
			xcoord=210;
		}else if(choice==4){
			choice=1;
			xcoord=50;
		}

		write_text("_____",xcoord,ycoord,WHITE,0); 

	}while(key!=ENTER);

	return choice;
}

int LevelPage(){
	//level options

	char key;
	int choice=1, xcoord=50, ycoord=143;

	write_text("Select Level",95,120,WHITE,0);

	write_text("1",50,140,WHITE,0); 
	write_text("2",70,140,WHITE,0); 
	write_text("3",90,140,WHITE,0); 
	write_text("4",110,140,WHITE,0); 
	write_text("5",130,140,WHITE,0); 
	write_text("6",150,140,WHITE,0); 
	write_text("7",170,140,WHITE,0); 
	write_text("8",190,140,WHITE,0); 
	write_text("9",210,140,WHITE,0); 
	write_text("10",230,140,WHITE,0); 
	write_text("_",xcoord,ycoord,WHITE,0); 

	do{
		key = (char) getch();

		switch(key){
			case LEFT:
				choice--;
				erase(xcoord,ycoord+5,20,3);
				xcoord-=20;
				break;
			case RIGHT:
				choice++;
				erase(xcoord,ycoord+5,20,3);
				xcoord+=20;
				break;
		}

		if(choice==0){
			choice=10;
			xcoord=230;
		}else if(choice==11){
			choice=1;
			xcoord=50;
		}

		write_text("_",xcoord,ycoord,WHITE,0); 

	}while(key!=ENTER);

	return choice;
}

//display instructions
void InstructionsPage(){
	erase(1,1,400,200); //change page

	write_text(">> NEXT",10,180,WHITE,0);

	write_text("Instructions",100,10,GREEN,0);
	write_text("The user will pick the difficulty",10,30,WHITE,0);
	write_text("of the game",90,40,WHITE,0);
	while((char)getch()!=ENTER){}
	write_text("Choices of difficulty are:",10,60,WHITE,0);
	while((char)getch()!=ENTER){}
	write_text("Easy",50,75,WHITE,0);
	while((char)getch()!=ENTER){}
	write_text("Medium",130,75,WHITE,0);
	while((char)getch()!=ENTER){}
	write_text("Hard",220,75,WHITE,0);
	while((char)getch()!=ENTER){}
	write_text("User will picked the level of ",10,95,WHITE,0);
	write_text("difficulty (1-10)",90,115,WHITE,0);
	while((char)getch()!=ENTER){}
	write_text("Navigate using 'W' 'A' 'S' 'D' keys",8,140,WHITE,0);
	while((char)getch()!=ENTER){}
	write_text("Input answers using keys (1-9)",10,160,WHITE,0);
	erase(10,180,100,40);
	write_text(">> BACK",10,180,WHITE,0);
	while((char)getch()!=ENTER){}
}

void DrawBoard(int difficulty, int level){
	initializeBoard();
	erase(1,1,400,200); //change page

	char key, str[10], timer[5];
	int i,j, xcoord=17, ycoord=17, row=1, col=1, input_key=0, check=0, t1, t2, elapsed_time, min, sec;

	for (i = 240; i <= 310; i++){			
        for(j = 60; j <= 105; j++){
    		write_pixel(i, j, PALE_YELLOW);
        }
    }

	if(difficulty==1){
		write_text("EASY",250,70,DARK_BLUE,0);
	}else if(difficulty==2){
		write_text("MEDIUM",250,70,DARK_BLUE,0);
	}else if(difficulty==3){
		write_text("HARD",250,70,DARK_BLUE,0);
	}

    sprintf(str, "LVL %d", level);
	write_text(str,255,90,DARK_BLUE,0);

	write_text("[R] eset",242,120,WHITE,0);
	write_text("[Q] uit",242,140,WHITE,0);
	write_text("[E] rase",242,160,WHITE,0);

	for (i = 10; i <= 235; i++){			//draw board
        for(j = 10; j <= 190; j++){

        	if((i+40)%25==0 || (j+10)%20==0){
        		write_pixel(i, j, WHITE);
        	}
        	
        	if(i==85 || i==160){
        		write_pixel(i-1, j, WHITE);
        		write_pixel(i+1, j, WHITE);
        	}

        	if(j==70 || j==130){
        		write_pixel(i, j-1, WHITE);
        		write_pixel(i, j+1, WHITE);
        	}

        }
    }
	//start game
    ResetGame();
	t1 = time();
    drawCurrPos(xcoord-5,ycoord-5);	

	do{
		input_key = 0;
		key = (char) getch();


		if(init_state[row-1][col-1]!=0){
			drawFixTile(xcoord-5,ycoord-5);	
		}else{
			erase(xcoord-5,ycoord-5,22,17);
		}

		if(board_value[row-1][col-1]!=-1){
    		sprintf(str,"%d",board_value[row-1][col-1]);
			write_text(str,xcoord,ycoord,WHITE,0);
    	}

		switch(key){		//switch case for the key inputs
			case UP:
				yIndex--;
				row--;
				ycoord-=20;
				break;
			case DOWN:
				yIndex++;
				row++;
				ycoord+=20;
				break;
			case LEFT:
				xIndex--;
				col--;
				xcoord-=25;
				break;
			case RIGHT:
				xIndex++;
				col++;
				xcoord+=25;
				break;
			case TILE_ERASE:			//erases the value at the current cell
				if(init_state[row-1][col-1]!=0)break;
				board_value[row-1][col-1] = -1;
				erase(xcoord-5,ycoord-5,22,17);
				break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if(init_state[row-1][col-1]!=0)break;			//input number
				board_value[row-1][col-1] = key-'0';
				input_key=1;
				break;
			case GAME_RESET:
				ResetGame();
				t1 = time();
				break;
			case GAME_QUIT:
				break;
		}

		if(row==0){	
			yIndex = 8;
			row=9;
			ycoord=177;
		}else if(row==10){
			yIndex = 0;
			row=1;
			ycoord=17;
		}

		if(col==0){
			xIndex = 8;
			col=9;
			xcoord=217;
		}else if(col==10){
			xIndex = 0;
			col=1;
			xcoord=17;
		}
		t2 = time();		//for the timer, counts elapsed_time
		elapsed_time = t2-t1;
		erase(244,30,80,30);
		write_text("Timer:", 244, 20, WHITE, 0);
		sprintf(timer,"%d",elapsed_time/60);
		write_text(timer, 244, 30, WHITE, 0);
		write_text("m", 265, 30, WHITE, 0);
		sprintf(timer,"%d",elapsed_time%60);
		write_text(timer,280, 30, WHITE,0);
		write_text("s", 300, 30, WHITE, 0);
    	check = CheckBoard(xcoord-5,ycoord-5);

		if(check!=-1){
    		drawCurrPos(xcoord-5,ycoord-5);
		}


    	if(board_value[row-1][col-1]!=-1){
    		sprintf(str,"%d",board_value[row-1][col-1]);
			write_text(str,xcoord,ycoord,WHITE,0);
    	}

		if(check == 0){	
			int checkIfWin = CheckEmpty();
			if(checkIfWin == 0){		//if the player has finished the game
				erase(1,1,400,200); //change page
				write_text("You Win!",100,80,GREEN,0);
				t2 = time();
				elapsed_time = t2-t1;
				write_text("Time used:", 100, 100, WHITE, 0);
				sprintf(timer,"%d",elapsed_time/60);
				write_text(timer, 120, 130, WHITE, 0);
				write_text("mins", 141, 130, WHITE, 0);
				sprintf(timer,"%d",elapsed_time%60);
				write_text(timer,200, 130, WHITE,0);
				write_text("seconds", 221, 130, WHITE, 0);			
				key = GAME_QUIT;
				getch();
			}
		}
	}while(key!=GAME_QUIT);
}
//loads the initial state of the game
void ResetGame(){
	char str[10];
	int i,j, x, y;
	for (i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
        	if(init_state[i][j]==0){
        		board_value[i][j] = -1;
        	}else{
        		board_value[i][j] = init_state[i][j];
       		}
    	}
    }

    for(j = 0, y=17; j < 9; j++, y+=20){
    	for (i = 0, x=17; i < 9; i++, x+=25){
        	erase(x-5,y-5,22,17);
        	if(board_value[j][i]!=-1){
        		drawFixTile(x-5,y-5);
	    		sprintf(str,"%d",board_value[j][i]);
				write_text(str,x,y,WHITE,0);
    		}
    	}
    }
}


/********************
FUNCTIONS FOR VIEWING AND UPDATING HIGHSCORES
BUT SOME VERSIONS OF OS CANT DETECT FILE READING AND FILE WRITING
*********************/


void ViewHighScores(){
	erase(1,1,400,200); //change page

	char easy[10][255];
	char medium[10][255];
	char hard[10][255];
	char buff[255];

	int i = 0;

	FILE *fp;

	fp = fopen("scores.txt", "r");

	//when first time opeaning and reading the file will take around 3-5 seconds.
	if(fp!=NULL){

		int easyChecker = -1;
		int mediumChecker = -1;
		int hardChecker = -1;
		while(fgets(buff, 255, (FILE*)fp) != NULL){

			//remove trailing newline
			size_t i = strlen(buff) - 1;
			if(buff[i] == '\n')
				buff[i] = '\0';

			//checks where the pointer is reading in the file, in what difficulty
			if(strcmp(buff, "1") == 0){
				easyChecker = 1;
				mediumChecker = -1;
				hardChecker = -1;
				i = 0;
				continue;
			}

			if(strcmp(buff, "2") == 0){
				easyChecker = -1;
				mediumChecker = 1;
				hardChecker = -1;
				i = 0;
				continue;
			}

			if(strcmp(buff, "3") == 0){
				easyChecker = -1;
				mediumChecker = -1;
				hardChecker = 1;
				i = 0;
				continue;
			}

			//stores the values in the correct array
			if(easyChecker == 1 && mediumChecker == -1 && hardChecker == -1){
				strcpy(easy[i], buff);
			}

			if(easyChecker == -1 && mediumChecker == 1 && hardChecker == -1)
				strcpy(medium[i], buff);

			if(easyChecker == -1 && mediumChecker == -1 && hardChecker == 1)
				strcpy(hard[i], buff);

			i++;
		}

		fclose(fp);
	}


	
	write_text("Press Enter To Go Back",60,40,GREEN,0);
	while((char)getch()!=ENTER){}
}


//updates highscores given the elapsed_time and difficulty of the finished game
void UpdateHighscores(int elapsed_time, int difficulty){
	typedef struct scores{
		char name[255];
		char time[255];
		struct scores *next;
	}scores;

	scores *easy = NULL;
	scores *medium = NULL;
	scores *hard = NULL;

	char buffName[255];
	char buffTime[255];
	size_t length;

	FILE *fp;

	fp = fopen("scores.txt", "r");

	//get all scores in the file, to compare
	if(fp!=NULL){

		int easyChecker = -1;
		int mediumChecker = -1;
		int hardChecker = -1;
		while(fgets(buffName, 255, (FILE*)fp) != NULL){

			//remove trailing newline
			length = strlen(buffName) - 1;
			if(buffName[length] == '\n')
				buffName[length] = '\0';


			if(strcmp(buffName, "1") == 0){
				easyChecker = 1;
				mediumChecker = -1;
				hardChecker = -1;
				continue;
			}

			if(strcmp(buffName, "2") == 0){
				easyChecker = -1;
				mediumChecker = 1;
				hardChecker = -1;
				continue;
			}

			if(strcmp(buffName, "3") == 0){
				easyChecker = -1;
				mediumChecker = -1;
				hardChecker = 1;
				continue;
			}

			//will only execute when not 1 or 2 or 3
			fgets(buffTime, 255, (FILE*)fp);
			length = strlen(buffTime) - 1;
			if(buffTime[length] == '\n')
				buffTime[length] = '\0';


			if(easyChecker == 1 && mediumChecker == -1 && hardChecker == -1){
				scores *newNode = malloc(sizeof(scores));
				strcpy(newNode->name,buffName);
				strcpy(newNode->time,buffTime);
				newNode->next = NULL;

				if(easy == NULL)
					easy = newNode;
				else{
					scores *mover;
					mover = easy;
					while(mover->next != NULL)
						mover = mover->next;

					mover->next = newNode;
				}
			}

			if(easyChecker == -1 && mediumChecker == 1 && hardChecker == -1){
				scores *newNode = malloc(sizeof(scores));
				strcpy(newNode->name,buffName);
				strcpy(newNode->time,buffTime);
				newNode->next = NULL;

				if(medium == NULL)
					medium = newNode;
				else{
					scores *mover;
					mover = medium;
					while(mover->next != NULL)
						mover = mover->next;

					mover->next = newNode;
				}

			}

			if(easyChecker == -1 && mediumChecker == -1 && hardChecker == 1){
				scores *newNode = malloc(sizeof(scores));
				strcpy(newNode->name,buffName);
				strcpy(newNode->time,buffTime);
				newNode->next = NULL;

				if(hard == NULL)
					hard = newNode;
				else{
					scores *mover;
					mover = hard;
					while(mover->next != NULL)
						mover = mover->next;

					mover->next = newNode;
				}
			}
		}

		fclose(fp);
	}

	char name[255];
	char elapsed_time_string[255];
	sprintf(elapsed_time_string,"%d",elapsed_time);	
	
	scores *newNode = malloc(sizeof(scores));		//create new "scores" node to be inserted in the list of highscores
	strcpy(newNode->name,name);
	strcpy(newNode->time,elapsed_time_string);
	newNode->next = NULL;


	if(difficulty == 1){
		scores *mover;
		mover = easy;

		//if the list is empty, first high score at the difficulty
		if(mover == NULL)
			mover = newNode;

		//traverse the whole list and insert
		else{
			while(mover != NULL){
				int mover_time = atoi(mover->time);
				int mover_time_next;
				if(mover->next != NULL)
					mover_time_next = atoi(mover->next->time);

				//insert at head
				if(mover_time > elapsed_time && mover == easy){
					newNode->next = easy;
					easy = newNode;
					break;
				}

				//insert at middle
				else if(mover_time < elapsed_time && mover_time_next > elapsed_time){
					newNode->next = mover->next;
					mover->next = newNode;
					break;
				}

				//insert at tail
				else if(mover->next == NULL && mover_time < elapsed_time){
					mover->next = newNode;
					break;
				}

				else
					mover = mover->next;
			}		
		}		
		
	}

	if(difficulty == 2){
		scores *mover;
		mover = medium;

		//if the list is empty, first high score at the difficulty
		if(mover == NULL)
			mover = newNode;

		//traverse the whole list and insert
		else{
			while(mover != NULL){
				int mover_time = atoi(mover->time);
				int mover_time_next;
				if(mover->next != NULL)
					mover_time_next = atoi(mover->next->time);

				//insert at head
				if(mover_time > elapsed_time && mover == medium){
					newNode->next = medium;
					medium = newNode;
					break;
				}

				//insert at middle
				else if(mover_time < elapsed_time && mover_time_next > elapsed_time){
					newNode->next = mover->next;
					mover->next = newNode;
					break;
				}

				//insert at tail
				else if(mover->next == NULL && mover_time < elapsed_time){
					mover->next = newNode;
					break;
				}

				else
					mover = mover->next;
			}		
		}
	}

	if(difficulty == 3){
		scores *mover;
		mover = hard;

		//if the list is empty, first high score at the difficulty
		if(mover == NULL)
			mover = newNode;

		//traverse the whole list and insert
		else{
			while(mover != NULL){
				int mover_time = atoi(mover->time);
				int mover_time_next;
				if(mover->next != NULL)
					mover_time_next = atoi(mover->next->time);

				//insert at head
				if(mover_time > elapsed_time && mover == hard){
					newNode->next = hard;
					hard = newNode;
					break;
				}

				//insert at middle
				else if(mover_time < elapsed_time && mover_time_next > elapsed_time){
					newNode->next = mover->next;
					mover->next = newNode;
					break;
				}

				//insert at tail
				else if(mover->next == NULL && mover_time < elapsed_time){
					mover->next = newNode;
					break;
				}

				else
					mover = mover->next;
			}		
		}
	}
	scores *mover;		//writes all the current highscores from each difficulty to scores.txt
	fp = fopen("scores.txt", "w");
	fwrite("1", 1, 1, fp);
	for(mover=easy; mover!=NULL; mover=mover->next){
		fwrite(mover->name, 255, 1, fp);
		fwrite(mover->time, 255, 1, fp);
	}
	fwrite("2", 1, 1, fp);
	for(mover=medium; mover!=NULL; mover=mover->next){
		fwrite(mover->name, 255, 1, fp);
		fwrite(mover->time, 255, 1, fp);
	}
	fwrite("3", 1, 1, fp);
	for(mover=hard; mover!=NULL; mover=mover->next){
		fwrite(mover->name, 255, 1, fp);
		fwrite(mover->time, 255, 1, fp);
	}

	fclose(fp);

}
