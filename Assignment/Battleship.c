/* 
 * Terry Parrish
 * Jonathan Rodrigues
 * C Programming COP-2220C
 * Taught by: Professor Dennis Hunchuck
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define CLS system("cls")
#define PAUSE system("pause")
#define FLUSH while (getchar() != '\n')
#define GAMES 10
#define row 10
#define col 10

//Function Prototypes: Add or remove as neccessary.
//void OpenBin(); //Loads save file if it exists.
int menu();
void BOARD(char [row][col], int);
void BullsEye(int x, int y, char coords[row][col], char ships[row][col]);
void topTen(int[], int);
//void CloseBin(); //Saves file.

//Done
int main() {
	int x = 0, y = 0, menuSelection = 0, topScores[GAMES] = { 0 }, movPlayed = 0;
	char coords[row][col] = { 0 }, ships[row][col] = { 0 }, run = 0;

	//OpenBin();
	
	// BullsEye(x, y, coords, ships);

	do {
		menuSelection = menu();

		switch (menuSelection) {

		case 1: //Start a game
			BOARD(coords, movPlayed);	
			break;

		case 2: //Top 10
			topTen(topScores, movPlayed);
			break;

		case 3:
			//Rules

		case 4:
			printf("Thanks for playing!\n");
			//Print Credits function. 

		}//End Switch

	} while (menuSelection != 4); //End Do/While for menu selction. 

	//CloseBin();
	
}

//Done
int menu() {
	int menuInput = 0;

	CLS;

	printf("          _____       _    _    _            _    _      \n         | __  | ___ | |_ | |_ | | ___  ___ | |_ |_| ___ \n         | __ -|| .'||  _||  _|| || -_||_ -||   || || . |\n         |_____||__,||_|  |_|  |_||___||___||_|_||_||  _|\n                                                    |_|  \n");
	printf("------------------------------------------------------------------\n");
	printf("\t\t\t1. Start a new game.\n");
	printf("\t\t\t2. View Top 10 Scores.\n");
	printf("\t\t\t3. Rules.\n");
	printf("\t\t\t4. Quit.\n");
	printf("------------------------------------------------------------------\n");

	printf("\t\tInput: ");
	scanf(" %d", &menuInput);
	FLUSH;

	while ((menuInput < 1) || (menuInput > 4)) {
		printf("Invalid Entry, please try again: ");
		scanf(" %d", &menuInput);
		FLUSH;
	}//End small while

	return menuInput;

}

//Done
void topTen(int score[], int newScore) {
	int i, cnt, temp, pass;


	//Checks from top down for zero. Inserts if it is. 
	for (i = 0; i < GAMES; i++) {
		if (score[i] == 0) {
			score[i] = newScore;
			i = 10;
		}//End if
	}//End for loop

	 //Checks newScore against greatest value in score array.
	if (newScore < score[GAMES - 1])
		score[GAMES - 1] = newScore;


	//Bubble sort loop then resorts newScore into appropriate position. 
	for (pass = 1; pass <= (GAMES - 1); pass++) {
		for (cnt = 0; cnt < 9; cnt++) {
			if (score[cnt + 1] == 0) {
				pass = 10;
				break;
			}
			else if (score[cnt] > score[cnt + 1]) {
				temp = score[cnt];
				score[cnt] = score[cnt + 1];
				score[cnt + 1] = temp;
			}
		}//End Bubble Sort (Inner Loop)
	}//End Bubble Sort (Outer Loop)

	CLS;

	printf("          _____       _    _    _            _    _      \n         | __  | ___ | |_ | |_ | | ___  ___ | |_ |_| ___ \n         | __ -|| .'||  _||  _|| || -_||_ -||   || || . |\n         |_____||__,||_|  |_|  |_||___||___||_|_||_||  _|\n                                                    |_|  \n");
	printf("------------------------------------------------------------------\n");
	printf("\t\t\tTop Ten Scores\n");
	printf("------------------------------------------------------------------\n");

	for (i = 0; i < (GAMES); i++) {
		if (score[i] == 0) {
			printf("\t\t\t%02d: Empty Score\n", i + 1);
		}
		else {
			printf("\t%02d: %d Moves\n", i + 1, score[i]);
		}
	}

	printf("------------------------------------------------------------------\n\n");
	PAUSE;
}

//Incomplete: Waiting for End product to get correct variables to export
/*
void OpenBin() {
	int i;
	FILE * fd;

	//Checks if file is there, if not then creates it. 
	fopen_s(&fd, "money.bin", "r+b");

	if (fd == NULL) {
		return 0;
	}

	fread(&*winCounter, sizeof(int), 1, fd);
	fread(money, sizeof(double), 2, fd);
	fread(winRecord, sizeof(double), RaceHistory, fd);
	fread(record, sizeof(int), RaceHistory, fd);


	fclose(fd);
}
*/

//Done
void BOARD(char coords[row][col], int moves){
	int i, j, counter = 1;

	CLS;
	
	printf("\n\t    A   B   C   D   E   F   G   H   I   J");
	printf("\n\t -------------------------------------------");
	for (i = 0; i < row; i++) {
		printf("\n     %2i |", counter);
		for (j = 0; j < col; j++) {
			if (coords[i][j] == 0) {
				printf("   *");
			}
			else {
				printf("   %c", coords[i][j]);
			}
		}
		printf("   |");
		counter++;
	}
	printf("\n\t -------------------------------------------");
	printf("\n\t\t\tMoves Played: %i\n\n", moves);
}

//Incomplete: Waiting for completion of other functions.
void BullsEye(int x, int y, char coords[row][col], char ships[row][col]) {

	if (ships[x][y] != 0) {
		switch (ships[x][y]) {
		case 'a':
			coords[x][y] = ships[x][y];
			break;
		case 's':
			coords[x][y] = ships[x][y];
			break;
		case 'd':
			coords[x][y] = ships[x][y];
			break;
		case 'f':
			coords[x][y] = ships[x][y];
			break;
		case 'g':
			coords[x][y] = ships[x][y];
			break;
		case 'h':
			coords[x][y] = ships[x][y];
			break;
		default:
			break;
		}
	}
	else {
	
	}
}

//Incomplete: Waiting for End product to get correct variables to export
/*
void CloseBin() {
	int i;

	FILE * fd;
	fopen_s(&fd, "money.bin", "wb");

	CLS;

	fwrite(&winCounter, sizeof(int), 1, fd);
	fwrite(money, sizeof(double), 2, fd);
	fwrite(winRecord, sizeof(double), RaceHistory, fd);
	fwrite(record, sizeof(int), RaceHistory, fd);

	fclose(fd);

}
*/