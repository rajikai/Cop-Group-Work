/*
* Terry Parrish
* Jonathan Rodrigues
* C Programming COP-2220C
* Taught by: Professor Dennis Hunchuck
*/

#pragma once
#ifndef _reduceClutter_(Battleship)_h
#define _reduceClutter_(Battleship)_h

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
	const char * trueName;
	int size;
	int sunken;
} Crusor, AirCarrier, Battleship, Submarine, Destroyer;

//Function Prototypes: Add or remove as neccessary.
void OpenBin(int *, int *, int[], char *, char[row][col], char[row][col]); //Loads save file if it exists.
void assignShipInfo();
int menu();
void resetGame(char[row][col], char[row][col], int *, int *);
void setPieces1(char[row][col], char *);
void setPieces2(char[row][col], struct ShipInfo *);
void BOARD(char[row][col], int);
void havEiSunk();
void youHaveSunk(struct ShipInfo *);
int target(char[row][col], int *, int *, int);
void BullsEye(int, int, char[row][col], char[row][col], int *, int *);
char sortScore(int[], int);
void topTen(int[]);
void EXIT();
void CloseBin(int, int, int[], char, char[row][col], char[row][col]); //Saves file.

#endif