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

//Function Prototypes: Add or remove as neccessary.
//void OpenBin(); //Loads save file if it exists.
int menu();
void setPieces(char [row][col], char *);
void BOARD(char [row][col], int);
void target(char [row][col], int *, int *, int *);
void BullsEye(int, int, char [row][col], char [row][col], int *);
void topTen(int[], int);
void EXIT();
//void CloseBin(); //Saves file.

//Done
int main() {
	int x = 0, y = 0, menuSelection = 0, topScores[GAMES] = { 0 }, movPlayed = 0, hits = 0;
	char coords[row][col] = { 0 }, ships[row][col] = { 0 }, run = 0;

	setPieces(ships, &run);

	//OpenBin();
	
	// 

	do {
		menuSelection = menu();

		switch (menuSelection) {

		case 1: //Start a game
			if (run == 0) {
				setPieces(ships, &run);
			}
			while (run == 1) {
				BOARD(coords, movPlayed);
				target(coords, &x, &y, &movPlayed);
				BullsEye(x, y, coords, ships, &hits);
				if (hits == 17)
					run = 0;
			}
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

//INCOMPLETE
void setPieces(char ship[row][col], char *run)
{

	int i, tempX, tempY, direction, direction2, return1 = 0, return2;


	srand(time(NULL));


// Set (C)Crusor(2 Holes)
	tempX = rand() % 10;

	tempY = rand() % 10;

	direction = rand() % 2;	// Determine horzontal or vertical
	direction2 = rand() % 2;	// Determine left/right (if horziontal) 
								// or up/down (if vertial).

	switch (direction)
	{

	case 0: //Direction is set to row

		if (tempX > 0 || tempX < (row - 1)) //Ensure Piece does not go out of board
		{

			switch (direction2)
			{

			case 0: //Goes right

				for (i = 0; i < 2; i++)
				{
					ship[tempX][tempY] = 'C';
					tempX++;
				}
			case 1: //Goes Left
				for (i = 0; i < 2; i++)
				{
					ship[tempX][tempY] = 'C';
					tempX--;
				}
			}
		}
		else if (tempX == 0) //If at left edge, go right.
		{
			for (i = 0; i < 2; i++)
			{
				ship[tempX][tempY] = 'C';
				tempX++;
			}
		}
		else //If at right edge, go left.
		{
			for (i = 0; i < 2; i++)
			{
				ship[tempX][tempY] = 'C';
				tempX--;
			}
		}
	case 1: //Direction is set to col
		if (tempY > 0 || tempY < (col - 1)) //Ensure Piece does not go out of board
		{

			switch (direction2)
			{

			case 0: //Goes Down

				for (i = 0; i < 2; i++)
				{
					ship[tempX][tempY] = 'C';
					tempY++;
				}
			case 1: //Goes Up
				for (i = 0; i < 2; i++)
				{
					ship[tempX][tempY] = 'C';
					tempY--;
				}
			}
		}
		else if (tempY == 0) //If at top edge, go Down.
		{
			for (i = 0; i < 2; i++)
			{
				ship[tempX][tempY] = 'C';
				tempY++;
			}
		}
		else //If at bottom edge, go Up.
		{
			for (i = 0; i < 2; i++)
			{
				ship[tempX][tempY] = 'C';
				tempY--;
			}
		}


	}

// Set (A)Aircraft Carrier(5 Holes)

	direction = rand() % 2;	// Decide Row/Col first
	direction2 = rand() % 2; // Decide left/right or up/down second

	//This sets the piece on the board
	switch (direction)
	{

	case 0: //Direction is set to row
			/*(This Checks to array to make sure not to 
			overwrite existing location for row.*/
		while (return1 != -5)
		{
			//Set a location
			tempX = rand() % 10; 
			tempY = rand() % 10;

			switch (direction2) { //Left or Right?
			case 0: //Right
				if ((tempX + 4) <= (row - 1)) //Ensure it can go right
				{
					for (i = 0; i < 5; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
				else //Can't go right, so it goes left.
				{
					for (i = 0; i < 5; i--)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
			case 1: //Left
				if ((tempX - 4) >= 0) //Ensure it can go left
				{
					for (i = 0; i < 5; i--)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
				else //Can't go left, so it goes right.
				{
					for (i = 0; i < 5; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}

				}
			}
			return1 = 0; //Restart counter.
		}

		if (tempX > 3 || tempX < (row - 4)) //Ensure Piece does not go out of board
		{

			switch (direction2)
			{

			case 0: //Goes right

				for (i = 0; i < 5; i++)
				{
					ship[tempX][tempY] = 'A';
					tempX++;
				}
			case 1: //Goes Left
				for (i = 0; i < 5; i++)
				{
					ship[tempX][tempY] = 'A';
					tempX--;
				}
			}
		}
		else if (tempX == 0) //If at left edge, go right.
		{
			for (i = 0; i < 5; i++)
			{
				ship[tempX][tempY] = 'A';
				tempX++;
			}
		}
		else //If at right edge, go left.
		{
			for (i = 0; i < 5; i++)
			{
				ship[tempX][tempY] = 'A';
				tempX--;
			}
		}
	case 1: //Direction is set to col
			/*(This Checks to array to make sure not to
			overwrite existing location for row.*/
		while (return1 != -5)
		{
			//Set a location
			tempX = rand() % 10;
			tempY = rand() % 10;

			switch (direction2) { //Up or Down?
			case 0: //Right
				if ((tempX + 4) <= (col - 1)) //Ensure it can go Down
				{
					for (i = 0; i < 5; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
				else //Can't go Down, so it goes Up.
				{
					for (i = 0; i < 5; i--)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
			case 1: //Up
				if ((tempX - 4) >= 0) //Ensure it can go Up
				{
					for (i = 0; i < 5; i--)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
				else //Can't go Up, so it goes Down.
				{
					for (i = 0; i < 5; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}

				}
			}
			return1 = 0; //Restart counter.
		}

		if (tempY > 3 || tempY < (col - 4)) //Ensure Piece does not go out of board
		{

			switch (direction2)
			{

			case 0: //Goes Down

				for (i = 0; i < 5; i++)
				{
					ship[tempX][tempY] = 'A';
					tempY++;
				}
			case 1: //Goes Up
				for (i = 0; i < 5; i++)
				{
					ship[tempX][tempY] = 'A';
					tempY--;
				}
			}
		}
		else if (tempY == 0) //If at top edge, go Down.
		{
			for (i = 0; i < 5; i++)
			{
				ship[tempX][tempY] = 'A';
				tempY++;
			}
		}
		else //If at bottom edge, go Up.
		{
			for (i = 0; i < 5; i++)
			{
				ship[tempX][tempY] = 'A';
				tempY--;
			}
		}


	}

// Set (B)Battleship(4 Holes)

	direction = rand() % 2;	// Decide Row/Col first
	direction2 = rand() % 2; // Decide left/right or up/down second

							 //This sets the piece on the board
	switch (direction)
	{

	case 0: //Direction is set to row
			/*(This Checks to array to make sure not to
			overwrite existing location for row.*/
		while (return1 != -4)
		{
			//Set a location
			tempX = rand() % 10;
			tempY = rand() % 10;

			switch (direction2) { //Left or Right?
			case 0: //Right
				if ((tempX + 3) <= (row - 1)) //Ensure it can go right
				{
					for (i = 0; i < 4; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
				else //Can't go right, so it goes left.
				{
					for (i = 0; i < 4; i--)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
			case 1: //Left
				if ((tempX - 3) >= 0) //Ensure it can go left
				{
					for (i = 0; i < 4; i--)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
				else //Can't go left, so it goes right.
				{
					for (i = 0; i < 4; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}

				}
			}
			return1 = 0; //Restart counter.
		}

		if (tempX > 2 || tempX < (row - 3)) //Ensure Piece does not go out of board
		{

			switch (direction2)
			{

			case 0: //Goes right

				for (i = 0; i < 4; i++)
				{
					ship[tempX][tempY] = 'B';
					tempX++;
				}
			case 1: //Goes Left
				for (i = 0; i < 4; i++)
				{
					ship[tempX][tempY] = 'B';
					tempX--;
				}
			}
		}
		else if (tempX == 0) //If at left edge, go right.
		{
			for (i = 0; i < 4; i++)
			{
				ship[tempX][tempY] = 'B';
				tempX++;
			}
		}
		else //If at right edge, go left.
		{
			for (i = 0; i < 4; i++)
			{
				ship[tempX][tempY] = 'B';
				tempX--;
			}
		}
	case 1: //Direction is set to col
			/*(This Checks to array to make sure not to
			overwrite existing location for row.*/
		while (return1 != -5)
		{
			//Set a location
			tempX = rand() % 10;
			tempY = rand() % 10;

			switch (direction2) { //Up or Down?
			case 0: //Right
				if ((tempX + 4) <= (col - 1)) //Ensure it can go Down
				{
					for (i = 0; i < 5; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
				else //Can't go Down, so it goes Up.
				{
					for (i = 0; i < 5; i--)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
			case 1: //Up
				if ((tempX - 4) >= 0) //Ensure it can go Up
				{
					for (i = 0; i < 5; i--)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
				else //Can't go Up, so it goes Down.
				{
					for (i = 0; i < 5; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}

				}
			}
			return1 = 0; //Restart counter.
		}

		if (tempY > 2 || tempY < (col - 3)) //Ensure Piece does not go out of board
		{

			switch (direction2)
			{

			case 0: //Goes Down

				for (i = 0; i < 4; i++)
				{
					ship[tempX][tempY] = 'B';
					tempY++;
				}
			case 1: //Goes Up
				for (i = 0; i < 4; i++)
				{
					ship[tempX][tempY] = 'B';
					tempY--;
				}
			}
		}
		else if (tempY == 0) //If at top edge, go Down.
		{
			for (i = 0; i < 4; i++)
			{
				ship[tempX][tempY] = 'B';
				tempY++;
			}
		}
		else //If at bottom edge, go Up.
		{
			for (i = 0; i < 4; i++)
			{
				ship[tempX][tempY] = 'B';
				tempY--;
			}
		}
	}


// Set(S)Submarine(3 Holes)

	direction = rand() % 2;	// Decide Row/Col first
	direction2 = rand() % 2; // Decide left/right or up/down second

							 //This sets the piece on the board
	switch (direction)
	{

	case 0: //Direction is set to row
			/*(This Checks to array to make sure not to
			overwrite existing location for row.*/
		while (return1 != -3)
		{
			//Set a location
			tempX = rand() % 10;
			tempY = rand() % 10;

			switch (direction2) { //Left or Right?
			case 0: //Right
				if ((tempX + 2) <= (row - 1)) //Ensure it can go right
				{
					for (i = 0; i < 3; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
				else //Can't go right, so it goes left.
				{
					for (i = 0; i < 3; i--)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
			case 1: //Left
				if ((tempX - 2) >= 0) //Ensure it can go left
				{
					for (i = 0; i < 3; i--)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
				else //Can't go left, so it goes right.
				{
					for (i = 0; i < 3; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}

				}
			}
			return1 = 0; //Restart counter.
		}

		if (tempX > 2 || tempX < (row - 3)) //Ensure Piece does not go out of board
		{

			switch (direction2)
			{

			case 0: //Goes right

				for (i = 0; i < 3; i++)
				{
					ship[tempX][tempY] = 'S';
					tempX++;
				}
			case 1: //Goes Left
				for (i = 0; i < 4; i++)
				{
					ship[tempX][tempY] = 'S';
					tempX--;
				}
			}
		}
		else if (tempX == 0) //If at left edge, go right.
		{
			for (i = 0; i < 3; i++)
			{
				ship[tempX][tempY] = 'S';
				tempX++;
			}
		}
		else //If at right edge, go left.
		{
			for (i = 0; i < 3; i++)
			{
				ship[tempX][tempY] = 'S';
				tempX--;
			}
		}
	case 1: //Direction is set to col
			/*(This Checks to array to make sure not to
			overwrite existing location for row.*/
		while (return1 != -3)
		{
			//Set a location
			tempX = rand() % 10;
			tempY = rand() % 10;

			switch (direction2) { //Up or Down?
			case 0: //Right
				if ((tempX + 2) <= (col - 1)) //Ensure it can go Down
				{
					for (i = 0; i < 3; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
				else //Can't go Down, so it goes Up.
				{
					for (i = 0; i < 3; i--)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
			case 1: //Up
				if ((tempX - 2) >= 0) //Ensure it can go Up
				{
					for (i = 0; i < 3; i--)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
				else //Can't go Up, so it goes Down.
				{
					for (i = 0; i < 3; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}

				}
			}
			return1 = 0; //Restart counter.
		}

		if (tempY > 2 || tempY < (col - 3)) //Ensure Piece does not go out of board
		{

			switch (direction2)
			{

			case 0: //Goes Down

				for (i = 0; i < 3; i++)
				{
					ship[tempX][tempY] = 'S';
					tempY++;
				}
			case 1: //Goes Up
				for (i = 0; i < 4; i++)
				{
					ship[tempX][tempY] = 'B';
					tempY--;
				}
			}
		}
		else if (tempY == 0) //If at top edge, go Down.
		{
			for (i = 0; i < 3; i++)
			{
				ship[tempX][tempY] = 'S';
				tempY++;
			}
		}
		else //If at bottom edge, go Up.
		{
			for (i = 0; i < 3; i++)
			{
				ship[tempX][tempY] = 'S';
				tempY--;
			}
		}
	}

// Set (D)Destroyer(3 Holes)
	direction = rand() % 2;	// Decide Row/Col first
	direction2 = rand() % 2; // Decide left/right or up/down second

							 //This sets the piece on the board
	switch (direction)
	{

	case 0: //Direction is set to row
			/*(This Checks to array to make sure not to
			overwrite existing location for row.*/
		while (return1 != -3)
		{
			//Set a location
			tempX = rand() % 10;
			tempY = rand() % 10;

			switch (direction2) { //Left or Right?
			case 0: //Right
				if ((tempX + 2) <= (row - 1)) //Ensure it can go right
				{
					for (i = 0; i < 3; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
				else //Can't go right, so it goes left.
				{
					for (i = 0; i < 3; i--)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
			case 1: //Left
				if ((tempX - 2) >= 0) //Ensure it can go left
				{
					for (i = 0; i < 3; i--)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
				else //Can't go left, so it goes right.
				{
					for (i = 0; i < 3; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}

				}
			}
			return1 = 0; //Restart counter.
		}

		if (tempX > 2 || tempX < (row - 3)) //Ensure Piece does not go out of board
		{

			switch (direction2)
			{

			case 0: //Goes right

				for (i = 0; i < 3; i++)
				{
					ship[tempX][tempY] = 'D';
					tempX++;
				}
			case 1: //Goes Left
				for (i = 0; i < 3; i++)
				{
					ship[tempX][tempY] = 'D';
					tempX--;
				}
			}
		}
		else if (tempX == 0) //If at left edge, go right.
		{
			for (i = 0; i < 3; i++)
			{
				ship[tempX][tempY] = 'D';
				tempX++;
			}
		}
		else //If at right edge, go left.
		{
			for (i = 0; i < 3; i++)
			{
				ship[tempX][tempY] = 'D';
				tempX--;
			}
		}
	case 1: //Direction is set to col
			/*(This Checks to array to make sure not to
			overwrite existing location for row.*/
		while (return1 != -3)
		{
			//Set a location
			tempX = rand() % 10;
			tempY = rand() % 10;

			switch (direction2) { //Up or Down?
			case 0: //Right
				if ((tempX + 2) <= (col - 1)) //Ensure it can go Down
				{
					for (i = 0; i < 3; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
				else //Can't go Down, so it goes Up.
				{
					for (i = 0; i < 3; i--)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
			case 1: //Up
				if ((tempX - 2) >= 0) //Ensure it can go Up
				{
					for (i = 0; i < 3; i--)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}
				}
				else //Can't go Up, so it goes Down.
				{
					for (i = 0; i < 3; i++)
					{
						if (ship[tempX + i][tempY] != 0) //Is it empty?
							return1++; //No
						else
							return1--; //Yes
					}

				}
			}
			return1 = 0; //Restart counter.
		}

		if (tempY > 2 || tempY < (col - 3)) //Ensure Piece does not go out of board
		{

			switch (direction2)
			{

			case 0: //Goes Down

				for (i = 0; i < 3; i++)
				{
					ship[tempX][tempY] = 'D';
					tempY++;
				}
			case 1: //Goes Up
				for (i = 0; i < 3; i++)
				{
					ship[tempX][tempY] = 'D';
					tempY--;
				}
			}
		}
		else if (tempY == 0) //If at top edge, go Down.
		{
			for (i = 0; i < 3; i++)
			{
				ship[tempX][tempY] = 'D';
				tempY++;
			}
		}
		else //If at bottom edge, go Up.
		{
			for (i = 0; i < 3; i++)
			{
				ship[tempX][tempY] = 'D';
				tempY--;
			}
		}
	}

		*run = 1;	// So program knows pieces 
					// have been set.
}

//Done
void BOARD(char coords[row][col], int moves){
	int i, j, counter = 1;

	CLS;
	coords[9][9] = 'M';
	
	printf("\n\t    A   B   C   D   E   F   G   H   I   J");
	printf("\n\t -------------------------------------------");
	for (i = 0; i < row; i++) {
		printf("\n     %2i |", counter);
		for (j = 0; j < col; j++) {
			if (coords[i][j] == 0) {
				printf("   *");
			}
			else {
				switch (toupper(coords[i][j])) {
				case 'A':
					printf(GRN "   %c" RESET, coords[i][j]);
				case 'B':
					printf(YEL "   %c" RESET, coords[i][j]);
				case 'C':
					printf(MAG "   %c" RESET, coords[i][j]);
				case 'D':
					printf(BLU "   %c" RESET, coords[i][j]);
				case 'S':
					printf(CYN "   %c" RESET, coords[i][j]);
				default:
					printf(RED "   %c" RESET, coords[i][j]);
				}
			}
		}
		printf("   |");
		counter++;
	}
	printf("\n\t -------------------------------------------");
	printf("\n\t\t\tMoves Played: %i\n\n", moves);
}

//Done
void target(char coords[row][col], int *x, int *y, int *moves) {
	int targetCol, targetRow;
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
				targetRow = row + 10;
				targetCol = col + 10;
			}

		invalid = 0;

	} while ((targetCol > col || targetCol < 1) && targetRow == 10);

	*x = targetRow;
	*y = targetCol - 1;
	*moves++;

}

//Incomplete: Waiting for completion of other functions.
void BullsEye(int x, int y, char coords[row][col], char ships[row][col], int *hits) {

	if (ships[x][y] != 0) {
		*hits++;
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
		coords[x][y] = 'M';
	}
}

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