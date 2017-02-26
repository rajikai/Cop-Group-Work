/* 
 * Terry Parrish
 * Jonathan Rodrigues
 * C Programming COP-2220C
 * Taught by: Professor Dennis Hunchuck
 */

//add quit, modify row.

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
#define CLS system("cls")
#define PAUSE system("pause")
#define FLUSH while (getchar() != '\n')
#define GAMES 10
#define row 10
#define col 10

struct ShipInfo
{
	char name;
	int size;
} Crusor, AirCarrier, Battleship, Submarine, Destroyer;

//Function Prototypes: Add or remove as neccessary.
//void OpenBin(); //Loads save file if it exists.
void assignShipInfo();
int menu();
void resetGame(char[row][col], char[row][col], int *, int *);
void setPieces1(char [row][col], char *);
void setPieces2(char[row][col], struct ShipInfo *);
void BOARD(char [row][col], int);
void target(char [row][col], int *, int *, int);
void BullsEye(int, int, char [row][col], char [row][col], int *, int *);
void topTen(int[], int);
void EXIT();
//void CloseBin(); //Saves file.

//Function Caller
int main() {
	int x = 0, y = 0, menuSelection = 0, topScores[GAMES] = { 0 }, movPlayed = 0, hits = 0;
	char coords[row][col] = { 0 }, ships[row][col] = { 0 }, run = 0;

	assignShipInfo();

	//OpenBin();
	
	// 

	do {
		menuSelection = menu();

		switch (menuSelection) {

		case 1: //Start a game
			if (run == 0) {
				resetGame(ships, coords, &movPlayed, &hits);
				setPieces1(ships, &run);
			}
			while (run == 1) {
				BOARD(coords, movPlayed);
				target(coords, &x, &y, movPlayed);
				BullsEye(x, y, coords, ships, &hits, &movPlayed);
				if (hits == 17)
					run = 0;
			}
			BOARD(coords, movPlayed);
			PAUSE;
			break;

		case 2: //Top 10
			topTen(topScores, movPlayed);
			break;

		case 3:
			//Rules

		case 4: //Print Credits function. 
			EXIT();

		}//End Switch

	} while (menuSelection != 4); //End Do/While for menu selction. 

	//CloseBin();
	
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

//Define Structures for ships
void assignShipInfo() {
	//Crusor Piece
	Crusor.name = 'C';
	Crusor.size = 2;

	//Aircraft Carrier Piece
	AirCarrier.name = 'A';
	AirCarrier.size = 5;

	//Battleship Piece
	Battleship.name = 'B';
	Battleship.size = 4;

	//Submarine Piece
	Submarine.name = 'S';
	Submarine.size = 3;

	//Destroyer Piece
	Destroyer.name = 'D';
	Destroyer.size = 3;
}

//Main Menu
int menu() {
	int menuInput = 0;

	CLS;

	printf("          _____       _    _    _            _    _      \n         | __  | ___ | |_ | |_ | | ___  ___ | |_ |_| ___ \n         | __ -|| .'||  _||  _|| || -_||_ -||   || || . |\n         |_____||__,||_|  |_|  |_||___||___||_|_||_||  _|\n                                                    |_|  \n");
	printf("------------------------------------------------------------------\n");
	printf("\t\t\t1. Start Game.\n");
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

void resetGame(char ships[row][col], char coords[row][col], int *movPlayed, int *hits) {
	int i, j;

	*movPlayed = 0;
	*hits = 0;

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			ships[i][j] = 0;
		}
	}

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			coords[i][j] = 0;
		}
	}
}

//Show the top ten scores
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

//Keep Main neat, and to call multiple structs.
void setPieces1(char ship[row][col], char *run){
	setPieces2(ship, &Crusor);
	setPieces2(ship, &AirCarrier);
	setPieces2(ship, &Battleship);
	setPieces2(ship, &Submarine);
	setPieces2(ship, &Destroyer);


	*run = 1;	// So program knows pieces 
				// have been set.
}

//Assign pieces to Array.
void setPieces2(char ship[row][col], struct ShipInfo *SHIP)
{
	int i, tempX, tempY, direction, direction2, restartEND = 0;

	srand(time(NULL));

	// Set a SHIP structure

	direction = rand() % 2;	// Decide Row/Col first
	direction2 = rand() % 2; // Decide left/right or up/down second

							 //This sets the piece on the board
	switch (direction)
	{

	case 0: //Direction is set to row
			/*(This Checks to array to make sure not to
			overwrite existing location for row.*/
		while (restartEND != SHIP->size)
		{
			//Set a location
			tempX = rand() % 10;
			tempY = rand() % 10;
			restartEND = 0; //Restart counter.

			switch (direction2) { //Left or Right?
			case 0: //Right
				if ((tempX + (SHIP->size - 1)) <= (row - 1)) //Ensure it can go right
				{
					for (i = 0; i < SHIP->size; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							restartEND--; //No
						else
							restartEND++; //Yes
					}
				}
				else //Can't go right, so it goes left.
				{
					for (i = 0; i < SHIP->size; i++)
					{
						if (ship[tempX - i][tempY] != 0) //Is it empty?
							restartEND--; //No
						else
							restartEND++; //Yes
					}
				}
				direction2 = 1;
				break;
			case 1: //Left
				if ((tempX - (SHIP->size - 1)) >= 0) //Ensure it can go left
				{
					for (i = 0; i < SHIP->size; i++)
					{
						if (ship[tempX - i][tempY] != 0) //Is it empty?
							restartEND--; //No
						else
							restartEND++; //Yes
					}
				}
				else //Can't go left, so it goes right.
				{
					for (i = 0; i < SHIP->size; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							restartEND--; //No
						else
							restartEND++; //Yes
					}

				}
			
				direction2 = 0;
				break;
			}
		}


		if (tempX > (SHIP->size - 2) || tempX < (row - (SHIP->size - 1))) //Ensure Piece does not go out of board
		{

			switch (direction2)
			{

			case 0: //Goes right

				for (i = 0; i < SHIP->size; i++)
				{
					ship[tempX + i][tempY] = SHIP->name;
				}
				break;
			case 1: //Goes Left
				for (i = 0; i < SHIP->size; i++)
				{
					ship[tempX - i][tempY] = SHIP->name;
				}
				break;
			}
		}
		
		else if (tempX == 0) //If at left edge, go right.
		{
			for (i = 0; i < SHIP->size; i++)
			{
				ship[tempX + i][tempY] = SHIP->name;
			}
		}
		else //If at right edge, go left.
		{
			for (i = 0; i < SHIP->size; i++)
			{
				ship[tempX - i][tempY] = SHIP->name;
			}
		}
		break;
	case 1: //Direction is set to col
			/*(This Checks to array to make sure not to
			overwrite existing location for row.*/
		while (restartEND != SHIP->size)
		{
			//Set a location
			tempX = rand() % 10;
			tempY = rand() % 10;
			restartEND = 0; //Restart counter.

			switch (direction2) { //Up or Down?
			case 0: //Right
				if ((tempX + (SHIP->size - 1)) <= (col - 1)) //Ensure it can go Down
				{
					for (i = 0; i < SHIP->size; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							restartEND--; //No
						else
							restartEND++; //Yes
					}
				}
				else //Can't go Down, so it goes Up.
				{
					for (i = 0; i < SHIP->size; i++)
					{
						if (ship[tempX - i][tempY] != 0) //Is it empty?
							restartEND--; //No
						else
							restartEND++; //Yes
					}
					direction2 = 1;
					break;
				}

			case 1: //Up
				if ((tempX - (SHIP->size - 1)) >= 0) //Ensure it can go Up
				{
					for (i = 0; i < SHIP->size; i++)
					{
						if (ship[tempX - i][tempY] != 0) //Is it empty?
							restartEND--; //No
						else
							restartEND++; //Yes
					}
				}
				else //Can't go Up, so it goes Down.
				{
					for (i = 0; i < SHIP->size; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							restartEND--; //No
						else
							restartEND++; //Yes
					}

				}
				direction2 = 0;
				break;
			}
		}

		if (tempY > (SHIP->size - 2) || tempY < (col - (SHIP->size - 1))) //Ensure Piece does not go out of board
		{

			switch (direction2)
			{

			case 0: //Goes Down

				for (i = 0; i < SHIP->size; i++)
				{
					ship[tempX][tempY + i] = SHIP->name;
				}
				break;
			case 1: //Goes Up
				for (i = 0; i < SHIP->size; i++)
				{
					ship[tempX][tempY - i] = SHIP->name;
				}
				break;
			}
		}
		else if (tempY == 0) //If at top edge, go Down.
		{
			for (i = 0; i < SHIP->size; i++)
			{
				ship[tempX][tempY + i] = SHIP->name;
			}
		}
		else //If at bottom edge, go Up.
		{
			for (i = 0; i < SHIP->size; i++)
			{
				ship[tempX][tempY - i] = SHIP->name;
			}
		}
		break;
	}
}

//Print the Array as a Board
void BOARD(char coords[row][col], int moves){
	int i, j, counter = 1;

	CLS;
	
	printf("\n\t    A   B   C   D   E   F   G   H   I   J");
	printf("\n\t -------------------------------------------");
	for (j = 0; j < row; j++) {
		printf("\n     %2i |", counter);
		for (i = 0; i < col; i++) {
			if (coords[i][j] == 0) {
				printf("   *");
			}
			else {
				switch (toupper(coords[i][j])) {
				case 'A':
					printf(GRN "   %c" RESET, coords[i][j]);
					continue;
				case 'B':
					printf(YEL "   %c" RESET, coords[i][j]);
					continue;
				case 'C':
					printf(MAG "   %c" RESET, coords[i][j]);
					continue;
				case 'D':
					printf(BLU "   %c" RESET, coords[i][j]);
					continue;
				case 'S':
					printf(CYN "   %c" RESET, coords[i][j]);
					continue;
				default:
					printf(RED "   %c" RESET, coords[i][j]);
					continue;
				}
			}
		}
		printf("   |");
		counter++;
	}
	printf("\n\t -------------------------------------------");
	printf("\n\t\t\tMoves Played: %i\n\n", moves);
}

//Take User Input
void target(char coords[row][col], int *x, int *y, int moves) {
	int targetCol, targetRow = row;
	char usrInput[5], targetColTemp, invalid = 0;

		printf("Fire missle at: ");

	do {

		scanf(" %4s", &usrInput, 5); //Takes an input
		FLUSH;

		if (strlen(usrInput) == 3 || strlen(usrInput) == 2) //Check if Input is Valid Length
		{

			targetColTemp = usrInput[0];

			if (strlen(usrInput) == 3) //Check if input has a length of 2 or 3.
			{

				targetCol = ((usrInput[1] - '0') * 10) + usrInput[2] - '0'; //Converting two digit string into intenger

			}
			else
			{

				targetCol = usrInput[1] - '0'; //Converting single digit string into intenger

			}
		}
		else { //Invalid entry, restart now.
			printf("Invalid entry, input valid entry: ");
			continue;

		}

		switch (toupper(targetColTemp)) {

		case 'A':
			targetRow = 0;
			break;

		case 'B':
			targetRow = 1;
			break;

		case 'C':
			targetRow = 2;
			break;

		case 'D':
			targetRow = 3;
			break;

		case 'E':
			targetRow = 4;
			break;

		case 'F':
			targetRow = 5;
			break;

		case 'G':
			targetRow = 6;
			break;

		case 'H':
			targetRow = 7;
			break;

		case 'I':
			targetRow = 8;
			break;

		case 'J':
			targetRow = 9;
			break;

		default:
			printf("Invalid Entry. Please Enter a Column A-G: ");
			targetRow = 10;
			invalid = 1;

		}

		if ((targetCol > col || targetCol < 1) && invalid != 1) {
			printf("Invalid Target. Please enter a Row 1-10: ");
			invalid = 1;
		}

			if (coords[targetRow][targetCol - 1] != 0 && invalid != 1) {
				printf("You already entered that target, try again: ");
				targetCol = col + 1;
			} 

		invalid = 0;

	} while (targetCol > col || targetCol < 1);

	*x = targetRow;
	*y = targetCol - 1;
}

//Check to see if User Input hit a ship
void BullsEye(int x, int y, char coords[row][col], char ships[row][col], int *hits, int *moves) {


	if (ships[x][y] != 0) {
		(*hits)++;
		coords[x][y] = ships[x][y];
		(*moves)++;
	}
	else {
		coords[x][y] = 'M';
		(*moves)++;
	}
	
}

//Leaving the Program
void EXIT() {

	CLS;

	printf("Created by: TJ Parrish, Jonathan Rodrigues \n");
	printf("Class: C Programming COP-2220C (Spring 2017)\n");
	printf("Taught by: Professor Dennis Hunchuck\n\n");
	printf("\t\tGoodbye!\n\n");

	PAUSE;
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