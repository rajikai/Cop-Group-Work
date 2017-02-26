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
#include <string.h>
#include "reduceClutter (BattleShip).h"

//Function Caller
int main() {
	int x = 0, y = 0, menuSelection = 0, topScores[GAMES] = { 0 }, movPlayed = 0, hits = 0;
	char coords[row][col] = { 0 }, ships[row][col] = { 0 }, run = 0;
	
	srand(time(NULL));
	assignShipInfo();

	OpenBin(&movPlayed, &hits,topScores, &run, coords, ships);

	// 

	do {
		menuSelection = menu();

		if (run == 0) { //Reset Data if no game is being played.
			resetGame(ships, coords, &movPlayed, &hits);
			setPieces1(ships, &run);
		}

		switch (menuSelection) {

		case 1: //Start a game
			run = 1; //To continue game if saved for later
			while (run == 1) {
				BOARD(coords, movPlayed);
				run = target(coords, &x, &y, movPlayed);
				if (run != 2) { // So move counter does not go up
					BullsEye(x, y, coords, ships, &hits, &movPlayed);
					if (hits == 17) {
						sortScore(topScores, movPlayed);
						run = 0; //To clear game setting
					}
				}
			}
			BOARD(coords, movPlayed); //Final look at board
			printf("\n");
			PAUSE;
			break;

		case 2: //Top 10
			topTen(topScores);
			break;

		case 3: //Print Credits function. 
			EXIT();
			break;

		}//End Switch

	} while (menuSelection != 3); //End Do/While for menu selction. 

	CloseBin(movPlayed, hits, topScores, run, coords, ships);

}

//Incomplete: Waiting for End product to get correct variables to export
void OpenBin(int *movPlayed, int *hits, int topScores[], char *run, char coords[row][col], char ships[row][col]) {
int i;
FILE * fd;

//Checks if file is there, if not then creates it.
fopen_s(&fd, "battleship.bin", "r+b");

if (fd == NULL) {
return 0;
}

//Struct info (for sinking ship)
fread(&Crusor.sunken, sizeof(int), 1, fd);
fread(&AirCarrier.sunken, sizeof(int), 1, fd);
fread(&Battleship.sunken, sizeof(int), 1, fd);
fread(&Submarine.sunken, sizeof(int), 1, fd);
fread(&Destroyer.sunken, sizeof(int), 1, fd);

//Other game information
fread(&*movPlayed, sizeof(int), 1, fd);
fread(&*hits, sizeof(int), 1, fd);
fread(&*run, sizeof(char), 1, fd);
fread(topScores, sizeof(int), GAMES, fd);
fread(coords, sizeof(char), row * col, fd);
fread(ships, sizeof(char), row * col, fd);


fclose(fd);
}

//Define Structures for ships
void assignShipInfo() {
	//Crusor Piece
	Crusor.name = 'C';
	Crusor.trueName = "Crusor";
	Crusor.size = 2;
	Crusor.sunken = 0;


	//Aircraft Carrier Piece
	AirCarrier.name = 'A';
	AirCarrier.trueName = "Aircraft Carrier";
	AirCarrier.size = 5;
	AirCarrier.sunken = 0;

	//Battleship Piece
	Battleship.name = 'B';
	Battleship.trueName = "Battleship";
	Battleship.size = 4;
	Battleship.sunken = 0;

	//Submarine Piece
	Submarine.name = 'S';
	Submarine.trueName = "Submarine";
	Submarine.size = 3;
	Submarine.sunken = 0;

	//Destroyer Piece
	Destroyer.name = 'D';
	Destroyer.trueName = "Destroyer";
	Destroyer.size = 3;
	Destroyer.sunken = 0;
}

//Title Logo
void gameLogo() {
	CLS;

	printf(CYN
		"          _____       _    _    _            _    _      \n"
		"         | __  | ___ | |_ | |_ | | ___  ___ | |_ |_| ___ \n"
		"         | __ -|| .'||  _||  _|| || -_||_ -||   || || . |\n"
		"         |_____||__,||_|  |_|  |_||___||___||_|_||_||  _|\n"
		"                                                    |_|  \n" RESET);
}

//Main Menu
int menu() {
	int menuInput = 0;

	gameLogo();

	printf("------------------------------------------------------------------\n");
	printf("\t\t\t1. Start Game.\n");
	printf("\t\t\t2. View Top 10 Scores.\n");
	printf("\t\t\t3. Quit.\n");
	printf("------------------------------------------------------------------\n");

	printf("\t\tInput: ");
	scanf(" %d", &menuInput);
	FLUSH;

	while ((menuInput < 1) || (menuInput > 3)) {
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
void sortScore(int score[], int newScore) {
	int i, cnt, temp, pass, colorNewScore;

	//Checks from top down for zero. Inserts if it is. 
	for (i = 0; i < GAMES; i++) {
		if (score[i] == 0) {
			score[i] = newScore;
			i = GAMES;
			return NULL;
		}//End if
	}//End for loop

	 //Checks newScore against greatest value in score array (lowest score).
	if (newScore > score[GAMES - 1])
		score[GAMES - 1] = newScore;


	//Bubble sort loop then resorts newScore into appropriate position. 
	for (pass = 1; pass < GAMES; pass++) {
		for (cnt = 9; cnt > 0; cnt--) {
			if (score[cnt] > score[cnt - 1]) {
				temp = score[cnt];
				score[cnt] = score[cnt - 1];
				score[cnt - 1] = temp;
			}
		}//End Bubble Sort (Inner Loop)
	}//End Bubble Sort (Outer Loop)
}

//Show the top ten scores
void topTen(int score[]) {
		int i;

		gameLogo();

		printf("------------------------------------------------------------------\n");
		printf("\t\t\tTop Ten Scores\n");
		printf("------------------------------------------------------------------\n");

		for (i = 0; i < (GAMES); i++) {
			if (score[i] == 0) {
				printf("\t\t\t%02d: Empty Score\n", i + 1);
			}
			else {
				printf("\t\t\t%02d: %d Moves\n", i + 1, score[i]);
			}
		}

		printf("------------------------------------------------------------------\n\n");
		PAUSE;
	}

//Keep Main neat, and to call multiple structs.
void setPieces1(char ship[row][col], char *run) {
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

	// Set a SHIP structure

	direction = rand() % 2;	// Decide Row/Col

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

			if ((tempX + SHIP->size) <= row) //Ensure it can go right
			{
				for (i = 0; i < SHIP->size; i++)
				{
					if (ship[tempX + i][tempY] != 0) //Is it empty?
						restartEND--; //No
					else
						restartEND++; //Yes
				}
			}
			else //If it can't go right, checks if it can go Left.
			{
				for (i = 0; i < SHIP->size; i++)
				{
					if (ship[tempX - i][tempY] != 0) //Is it empty?
						restartEND--; //No
					else
						restartEND++; //Yes
				}
			}
		}


		if ((tempX + SHIP->size)  <= row) //Ensure Piece does not go out of board (Right)
		{
			for (i = 0; i < SHIP->size; i++)
			{
				ship[tempX + i][tempY] = SHIP->name;
			}
		}
		else //Ensure Piece does not go out of board (LEft)
		{
			for (i = 0; i < SHIP->size; i++)
			{
				ship[tempX - i][tempY] = SHIP->name;
			}
		}
		break;
	case 1: //Direction is set to col
			/*(This Checks to array to make sure not to
			overwrite existing location for col.*/
		while (restartEND != SHIP->size)
		{
			//Set a location
			tempX = rand() % 10;
			tempY = rand() % 10;
			restartEND = 0; //Restart counter.

			if ((tempY + SHIP->size) <= col) //Ensure it can go Down
			{
				for (i = 0; i < SHIP->size; i++)
				{
					if (ship[tempX][tempY + i] != 0) //Is it empty?
						restartEND--; //No
					else
						restartEND++; //Yes
				}
			}
			else //If it can't go Down, checks if it can go Up.
			{
				for (i = 0; i < SHIP->size; i++)
				{
					if (ship[tempX][tempY - i] != 0) //Is it empty?
						restartEND--; //No
					else
						restartEND++; //Yes
				}
			}
		}

		if ((tempY + SHIP->size) <= col) //Ensure Piece does not go out of board (Down)
		{
			for (i = 0; i < SHIP->size; i++)
			{
				ship[tempX][tempY + i] = SHIP->name;
			}
		}
		else //Ensure Piece does not go out of board (Up)
		{
			for (i = 0; i < SHIP->size; i++)
			{
				ship[tempX][tempY - i] = SHIP->name;
			}
		}
		break;
	}
}

void havEiSunk() {
	youHaveSunk(&Crusor);
	youHaveSunk(&AirCarrier);
	youHaveSunk(&Battleship);
	youHaveSunk(&Submarine);
	youHaveSunk(&Destroyer);
}

void youHaveSunk(struct ShipInfo *SHIP) {
	if (SHIP->sunken == SHIP->size) {
		printf("\t\You have sunken the enemy's %s.\n\n", (SHIP->trueName));
		(SHIP->sunken)++;
	}
}

//Print the Array as a Board
void BOARD(char coords[row][col], int moves) {
	int i, j;
	char letter = 'A';

	gameLogo();

	printf("\n\t    "); //For Formating purpose

	for (i = 0; i < row; i++) { //For the row labels (A B C D) etch.
		printf("%c   ", letter);
		letter++;
	}

	printf("\n\t ---"); //For formating purpose

	for (i = 0; i < row; i++) { // The top of the game border's length
		printf("----");
		letter++;
	}

	for (j = 0; j < row; j++) { //Length of Row
		printf("\n     %2i |", j + 1);
		for (i = 0; i < col; i++) { //Length of Col
			if (coords[i][j] == 0) { //Hidden Locations (Unhit)
				printf("   *"); 
			}
			else { //There was a hit, which one is it?
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
	}

	printf("\n\t ---"); //For formating purpose

	for (i = 0; i < row; i++) { // The top of the game border's length
		printf("----");
		letter++;
	}

	printf("\n\t\tType \"EXIT\" to save game for later");
	printf("\n\t\t\tMoves Played: %i\n", moves);

	havEiSunk();
}

//Take User Input
int target(char coords[row][col], int *x, int *y, int moves) {
	int targetCol, targetRow = row;
	char usrInput[5], targetColTemp, invalid = 0;

	printf("\nFire missle at (example: a1): ");

	do {

		scanf(" %4s", &usrInput); //Takes an input
		FLUSH;

		if (strcmp(usrInput, "EXIT") == 0) {
			return 2;
		}

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
	return 1;
}

//Check to see if User Input hit a ship
void BullsEye(int x, int y, char coords[row][col], char ships[row][col], int *hits, int *moves) {


	if (ships[x][y] != 0) {
		(*hits)++;
		coords[x][y] = ships[x][y];
		switch (coords[x][y]) {
		case 'A':
			AirCarrier.sunken++;
			break;
		case 'B':
			Battleship.sunken++;
			break;
		case 'C':
			Crusor.sunken++;
			break;
		case 'D':
			Destroyer.sunken++;
			break;
		case 'S':
			Submarine.sunken++;
			break;
		}
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

void CloseBin(int movPlayed, int hits, int topScores[], char run, char coords[row][col], char ships[row][col]) {
int i;

FILE * fd;
fopen_s(&fd, "battleship.bin", "wb");

//Struct info (for sinking ship)
fwrite(&Crusor.sunken, sizeof(int), 1, fd);
fwrite(&AirCarrier.sunken, sizeof(int), 1, fd);
fwrite(&Battleship.sunken, sizeof(int), 1, fd);
fwrite(&Submarine.sunken, sizeof(int), 1, fd);
fwrite(&Destroyer.sunken, sizeof(int), 1, fd);

//Other game information
fwrite(&movPlayed, sizeof(int), 1, fd);
fwrite(&hits, sizeof(int), 1, fd);
fwrite(&run, sizeof(char), 1, fd);
fwrite(topScores, sizeof(int), GAMES, fd);
fwrite(coords, sizeof(char), row * col, fd);
fwrite(ships, sizeof(char), row * col, fd);

fclose(fd);

}
