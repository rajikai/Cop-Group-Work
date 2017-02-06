#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define CLS system("cls")
#define PAUSE system("pause")
#define FLUSH while (getchar() != '\n')
#define WALLET 0
#define BANK 300
#define RaceHistory 1000

//Function Prototypes: Add or remove as neccessary.
void OpenBin(int *, double [], double[], int []); //Loads save file if it exists.
void moneyHeader(double[]); //Changed this to a header.
int Navigation(double []); //Main menu.
void bankMenu(double[]); //Bank Menu: Withdraw/Deposit.
void delay(unsigned int); //Delay for race function.
void oddsHeader(); //Header for horse function.
char makeBet(double *, double[], double *); //Choose amount of bet.
void race(double *, double *, int, int [], char); //Probably should return an int. 
int addWin(double); //Returns a bool win value.
void printWin(double [], double[], int[], int, int); //Checks to see if Morse won. 
void winningHorses(); //Track winning horses.
void GoHome(); //Exit the Program.
void CloseBin(int, double[], double[], int[]); //Saves file.

//Done
int main() {
	char horse = 0;
	int winCounter = 0, input = 0, valid = 0, raceCounter = 0, record[RaceHistory] = { 0 };
	double bet = 0, winnings = 0, money[2] = { WALLET , BANK }, winRecord[RaceHistory] = { 0 };
	
	OpenBin(&winCounter, money, winRecord, record);

	//Menu loop
	do {
		
		input = Navigation(money);

		//Switch for Menu Input. Each case calls function appropriate to operation that is being requested. 
		while (valid == 0) {

			if (winCounter == 0 && input == 4) {
				printf("\nNo bets have been won, pick another option: ");
				scanf_s(" %d", &input);
				FLUSH;
			}

			switch (input) {
			case 1:
				//Go To Bank
				valid = 1;
				bankMenu(money);
				break;

			case 2:
				//Make a Bet
				horse = makeBet(&bet, money, &winnings);
				valid = 1;
				break;

			case 3:
				//Go to the track to watch horse
				valid = 1;
				race(&winnings, &bet, raceCounter, record, horse);
				money[0] += winnings + bet;
				record[raceCounter] = horse;
				winRecord[raceCounter] = winnings;
				raceCounter++;
				winCounter += addWin(winnings);
				bet = 0;
				horse = 0;
				winnings = 0;
				break;

			case 4:
				//See Past Wins
				if (winCounter != 0) {
					printWin(money, winRecord, record, raceCounter, winCounter);
					valid = 1;
				}
				break;

			case 5:
				//Quit.
				valid = 1;
				GoHome();
				break;

			default:
				input = 0;
				printf("Invalid Entry!, try again: ");
				scanf_s(" %d", &input);
				FLUSH;
				continue;
			}

		}
		valid = 0;
	} while (input != 5);

	CloseBin(winCounter, money, winRecord, record);
	
}

//Done
void OpenBin(int *winCounter, double money[], double winRecord[], int record[]) {
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

//Done
void moneyHeader(double money[]) {

	CLS;

	printf("\t\t================= Funds Available ================\n");
	printf("\t\t\tWallet: $%.2lf      Bank: $%.2lf\n", money[0], money[1]);
	printf("\t\t==================================================\n");


}

//Done
int Navigation(double money[]) {
	int input;

	moneyHeader(money);

	printf("\n\tMenu options:\n");
	printf("\t\tPlease choose an option:\n");
	printf("\t\t1. Bank\n");
	printf("\t\t2. Bet\n");
	printf("\t\t3. Track\n");
	printf("\t\t4. Past Winners\n");
	printf("\t\t5. Go Home\n\n");

	printf("Input: ");

	scanf_s("%d", &input);
	FLUSH;

	while (money[0] == 0 && input == 2) {
		printf("You cannot bet without money, try another input: ");
		scanf_s("%d", &input);
		FLUSH;
	}

	return input;

}

//Done
void bankMenu(double money[]) {
	char valid = 0;
	int bankInput = 0;
	double moneyMoved = 0;

	do {
		moneyHeader(money);

		printf("\n\tWelcome to the Bank! \n");
		printf("\t\tPlease select an option from the following menu: \n");
		printf("\t\t1. Withdrawl Funds.\n");
		printf("\t\t2. Deposit Funds.\n");
		printf("\t\t3. Check Account Balance.\n");
		printf("\t\t4. Leave the Bank.\n\n");

		printf("Input: ");
		valid = 0;

		scanf_s(" %d", &bankInput);
		FLUSH;

		while (valid == 0) {
			switch (bankInput) {

			case 1: //Withdrawl

				if (money[1] == 0) {
					printf("Oops, no money in bank.\n\n");
					PAUSE;
					valid = 1;
					break;
				}

				printf("Enter Amount to be Withdrawn: $");
				scanf_s("%lf", &moneyMoved);
				FLUSH;

				if (money[1] < moneyMoved) {
					printf("Insufficent Funds. Transaction Cancelled.\n\n");
					PAUSE;
				}
				else {
					money[1] -= moneyMoved;
					money[0] += moneyMoved;
				}

				valid = 1;
				break;

			case 2: //Deposit

				if (money[0] == 0) {
					printf("Oops, no money in wallet.\n\n");
					PAUSE;
					valid = 1;
					break;
				}


				printf("Enter Amount to be Deposited: $");
				scanf_s("%lf", &moneyMoved);

				if (money[0] < moneyMoved) {
					printf("Insufficent Funds. Transaction Cancelled.\n");
					PAUSE;
				}
				else {
					money[0] -= moneyMoved;
					money[1] += moneyMoved;
				}
				valid = 1;
				break;

			case 3:

				printf("\nWallet = $%.2lf\n", money[0]);
				printf("Bank = $%.2lf\n\n", money[1]);
				PAUSE;
				valid = 1;
				break;

			case 4:

				printf("\nThank you for visiting the bank\n\n");
				PAUSE;
				valid = 1;
				break;

			default:
				printf("Invalid Entry, Please try again!: ");
				scanf_s("%d", &bankInput);
				break;

			}
		} //End Switch
	} while (bankInput != 4);

}

//Done
void oddsHeader() {
	printf("\n\t\t***********************************************\n");
	printf("\t\tWhat horse would you like to place your bet on?\n");
	printf("\t\t***********************************************\n");
	printf("\t\t**\t1: Horse 1: Payout 2-1  | 30%%\t     **\n");
	printf("\t\t**\t2: Horse 2: Payout 5-1  | 10%%\t     **\n");
	printf("\t\t**\t3: Horse 3: Payout 10-1 | 8%%\t     **\n");
	printf("\t\t**\t4: Horse 4: Payout 15-1 | 6%%\t     **\n");
	printf("\t\t**\t5: Horse 5: Payout 50-1 | 2%%\t     **\n");
	printf("\t\t**\t6: Horse 6: Payout 20-1 | 4%%\t     **\n");
	printf("\t\t**\t7: Horse 7: Payout 10-1 | 8%%\t     **\n");
	printf("\t\t**\t8: Horse 8: Payout 5-1  | 10%%\t     **\n");
	printf("\t\t**\t9: Horse 9: Payout 3-1  | 22%%\t     **\n");
	printf("\t\t***********************************************\n\n");
}

//Done
char makeBet(double *bet, double money[], double *winnings) {

	int choice, valid = 0;

	if (*bet == 0) {
		while (valid != 1) {

			moneyHeader(money);
			oddsHeader();

			if (valid == 2) {
				valid = 1;
			}

			while (valid == 0) {
				printf("Place you bet: $");
				scanf_s("%lf", &*bet);
				FLUSH;
				if (money[0] < *bet) {
					printf("You don't have enough money for that bet, try again.\n");
				}
				else {
					valid = 2;
				}
			}
		}

		money[0] -= *bet;
		printf("You entered $%.2lf as your bet\n", *bet);



		printf("Which horse are you horse on? (1-9): ");
		scanf_s("%i", &choice);
		FLUSH;

		valid = 1;

		while (valid == 1) {

			moneyHeader(money);
			oddsHeader();

			switch (choice) {

			case 1:
				printf("You bet $%.2lf on Horse 1\n", *bet);
				*winnings = *bet * 2;
				printf("Payout could be: $%.2lf \n\n", *winnings);
				valid = 0;
				break;
			case 2:
				printf("You bet $%.2lf on Horse 2\n", *bet);
				*winnings = *bet * 5;
				printf("Payout could be: $%.2lf \n\n", *winnings);
				valid = 0;
				break;
			case 3:
				printf("You bet $%.2lf on Horse 3\n", *bet);
				*winnings = *bet * 10;
				printf("Payout could be: $%.2lf \n\n", *winnings);
				valid = 0;
				break;
			case 4:
				printf("You bet $%.2lf on Horse 4\n", *bet);
				*winnings = *bet * 15;
				printf("Payout could be: $%.2lf \n\n", *winnings);
				valid = 0;
				break;
			case 5:
				printf("You bet $%.2lf on Horse 5\n", *bet);
				*winnings = *bet * 50;
				printf("Payout could be: $%.2lf \n\n", *winnings);
				valid = 0;
				break;
			case 6:
				printf("You bet $%.2lf on Horse 6\n", *bet);
				*winnings = *bet * 20;
				printf("Payout could be: $%.2lf \n\n", *winnings);
				valid = 0;
				break;
			case 7:
				printf("You bet $%.2lf on Horse 7\n", *bet);
				*winnings = *bet * 10;
				printf("Payout could be: $%.2lf \n\n", *winnings);
				valid = 0;
				break;
			case 8:
				printf("You bet $%.2lf on Horse 8\n", *bet);
				*winnings = *bet * 5;
				printf("Payout could be: $%.2lf \n\n", *winnings);
				valid = 0;
				break;
			case 9:
				printf("You bet $%.2lf on Horse 9\n", *bet);
				*winnings = *bet * 3;
				printf("Payout could be: $%.2lf \n\n", *winnings);
				valid = 0;
				break;
				// Error if an invalid error is selected
			default:
				printf("You entered an invalid choice, try again: ");
				scanf_s("%i", &choice);
				FLUSH;
				break;
			}
		}

		system("pause");
		return choice;
	}
 else {
	 moneyHeader(money);
	 printf("\nA bet has already been made.\n\n");
	 PAUSE;
}
}

//Done
int addWin(double winnings) {
	if (winnings != 0) {
		return 1;
	}
	else {
		return 0;
	}
}

//Done
void printWin(double money[], double winRecord[], int record[], int raceCounter, int wins) {
	int i = 0, entry = 0, count, forward = 0, forwardLimit = ((wins - 1) / 10) + 2;

	while (i < raceCounter) {

		moneyHeader(money);

		printf("\n\t**************************************************");
		printf("\n\t**    Game #    **     Horse    **      Won     **");
		printf("\n\t**************************************************");
		for (count = 0; count < 10; i = i + 2) {
			if (record[i] < 10 && winRecord[i] > 0) {
				printf("\n\t**\t%d\t**\t%d\t**\t%.2lf\t**", i + 1, record[i], winRecord[i]);
				count++;
				if (i < forwardLimit) {
					forwardLimit = i;
				}
			}
			if (i >= raceCounter) {
				count = 10;
			}
		}

		entry = 0;
		printf("\n\t**************************************************");
		printf("\n\t**\tTotal Games:    \t**\t%d/%d\t** ", wins, raceCounter);
		printf("\n\t**************************************************\n\n");

		if (forward == 0 || wins == 10) {
			if (forwardLimit != 2) {
				printf("\n\nEnter 1 to page to forward. ");
				while (entry != 1) {
					while (scanf_s("%i", &entry) != 1) {
						printf("Invalid Entry, try again:  ");
						FLUSH;
					}
					switch (entry) {
					case 1:
						forward++;
						break;
					default:
						printf("Invalid Entry, try again:  ");
					}
				}
			}
			else {
				printf("\n\n");
				PAUSE;
			}
		}
		else if (forward <= forwardLimit && wins > 10) {
			if (forward == forwardLimit) {
				printf("\n\nEnter 1 to page to exit, 2 to page back. ");
			}
			else {
				printf("\n\nEnter 1 to page to forward, 2 to page back. ");
			}
			while (entry == 0) {
				while (scanf_s("%i", &entry) != 1) {
					printf("Invalid Entry, try again:  ");
					FLUSH;
				}
				switch (entry) {
				case 1:
					forward++;
					getchar();
					break;
				case 2:
					getchar();
					i = i - 20;
					forward--;
					break;
				default:
					printf("Invalid Entry, try again:  ");
				}
			}
		}
	}
}

//Done
void delay(unsigned int mseconds) {
	clock_t goal = mseconds + clock();
	while (goal > clock());
}

//Done
void race(double *winnings, double *bet, int tracker, int record[], char horse) {

	time_t t;
	int winCheck = 0, movement = 0;
	int horseNum[9] = { 0 };
	char raceDisplay[9][25] = { ' ' }, winner;


	raceDisplay[0][0] = '1';
	raceDisplay[1][0] = '2';
	raceDisplay[2][0] = '3';
	raceDisplay[3][0] = '4';
	raceDisplay[4][0] = '5';
	raceDisplay[5][0] = '6';
	raceDisplay[6][0] = '7';
	raceDisplay[7][0] = '8';
	raceDisplay[8][0] = '9';

	printf("\nFinal bets have been placed...\n");

	delay(2000);

	CLS;

	printf("AND THEY'RE OFF!!");

	delay(1000);

	do {

		srand((unsigned)time(&t));

		int x = rand() % 100 + 1; // Variable X for RNG.

		CLS;

		printf("\t\t\tRace %d\n", tracker + 1);
		printf("===============================================\n");

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 25; j++) {
				printf("%c ", raceDisplay[i][j]);
			}
			printf("\n");
		}

		printf("===============================================\n");

		//RNG Movement check with built in odds...




		if (x >= 1 && x <= 30) {	    //30% Chance
			movement = 1;
		}
		else if (x >= 31 && x <= 40) {	//10% Chance 
			movement = 2;
		}
		else if (x >= 41 && x <= 48) {	//08% Chance
			movement = 3;
		}
		else if (x >= 49 && x <= 54) {	//06% Chance 
			movement = 4;
		}
		else if (x >= 55 && x <= 56) {	//02% Chance
			movement = 5;
		}
		else if (x >= 57 && x <= 60) {	//04% Chance
			movement = 6;
		}
		else if (x >= 61 && x <= 68) {	//08% Chance
			movement = 7;
		}
		else if (x >= 69 && x <= 78) {	//10% Chance
			movement = 8;
		}
		else if (x >= 79 && x <= 100) {	//22% Chance
			movement = 9;
		}
		//End of RNG Movement Check

		int k;

		for (k = 0; k < 9; k++) {
			horseNum[k]++;
		}

		raceDisplay[0][(horseNum[0] - 1)] = '-';
		raceDisplay[0][(horseNum[0])] = '1';
		raceDisplay[1][(horseNum[1] - 1)] = '-';
		raceDisplay[1][(horseNum[1])] = '2';
		raceDisplay[2][(horseNum[2] - 1)] = '-';
		raceDisplay[2][(horseNum[2])] = '3';
		raceDisplay[3][(horseNum[3] - 1)] = '-';
		raceDisplay[3][(horseNum[3])] = '4';
		raceDisplay[4][(horseNum[4] - 1)] = '-';
		raceDisplay[4][(horseNum[4])] = '5';
		raceDisplay[5][(horseNum[5] - 1)] = '-';
		raceDisplay[5][(horseNum[5])] = '6';
		raceDisplay[6][(horseNum[6] - 1)] = '-';
		raceDisplay[6][(horseNum[6])] = '7';
		raceDisplay[7][(horseNum[7] - 1)] = '-';
		raceDisplay[7][(horseNum[7])] = '8';
		raceDisplay[8][(horseNum[8] - 1)] = '-';
		raceDisplay[8][(horseNum[8])] = '9';

		//===


		//Display Update based on RNG Check
		if (movement == 1) {
			horseNum[0]++;
			raceDisplay[0][(horseNum[0] - 1)] = '-';
			raceDisplay[0][(horseNum[0])] = '1';
		}
		else if (movement == 2) {
			horseNum[1]++;
			raceDisplay[1][(horseNum[1] - 1)] = '-';
			raceDisplay[1][(horseNum[1])] = '2';
		}
		else if (movement == 3) {
			horseNum[2]++;
			raceDisplay[2][(horseNum[2] - 1)] = '-';
			raceDisplay[2][(horseNum[2])] = '3';
		}
		else if (movement == 4) {
			horseNum[3]++;
			raceDisplay[3][(horseNum[3] - 1)] = '-';
			raceDisplay[3][(horseNum[3])] = '4';
		}
		else if (movement == 5) {
			horseNum[4]++;
			raceDisplay[4][(horseNum[4] - 1)] = '-';
			raceDisplay[4][(horseNum[4])] = '5';
		}
		else if (movement == 6) {
			horseNum[5]++;
			raceDisplay[5][(horseNum[5] - 1)] = '-';
			raceDisplay[5][(horseNum[5])] = '6';
		}
		else if (movement == 7) {
			horseNum[6]++;
			raceDisplay[6][(horseNum[6] - 1)] = '-';
			raceDisplay[6][(horseNum[6])] = '7';
		}
		else if (movement == 8) {
			horseNum[7]++;
			raceDisplay[7][(horseNum[7] - 1)] = '-';
			raceDisplay[7][(horseNum[7])] = '8';
		}
		else if (movement == 9) {
			horseNum[8]++;
			raceDisplay[8][(horseNum[8] - 1)] = '-';
			raceDisplay[8][(horseNum[8])] = '9';
		}

		movement = 0;
		//End of Display Update

		//Checking for a winner
		if (raceDisplay[0][24] == '1') {
			winCheck = 1;
			winner = 1;
			printf("And the winner is...LANE 1!\n");
		}
		else if (raceDisplay[1][24] == '2') {
			winCheck = 1;
			winner = 2;
			printf("And the winner is...LANE 2!\n");
		}
		else if (raceDisplay[2][24] == '3') {
			winCheck = 1;
			winner = 3;
			printf("And the winner is...LANE 3!\n");
		}
		else if (raceDisplay[3][24] == '4') {
			winCheck = 1;
			winner = 4;
			printf("And the winner is...LANE 4!\n");
		}
		else if (raceDisplay[4][24] == '5') {
			winCheck = 1;
			winner = 5;
			printf("And the winner is...LANE 5!\n");
		}
		else if (raceDisplay[5][24] == '6') {
			winCheck = 1;
			winner = 6;
			printf("And the winner is...LANE 6!\n");
		}
		else if (raceDisplay[6][24] == '7') {
			winCheck = 1;
			winner = 7;
			printf("And the winner is...LANE 7!\n");
		}
		else if (raceDisplay[7][24] == '8') {
			winCheck = 1;
			winner = 8;
			printf("And the winner is...LANE 8!\n");
		}
		else if (raceDisplay[8][24] == '9') {
			winCheck = 1;
			winner = 9;
			printf("And the winner is...LANE 9!\n");
		}

		delay(1000);
		//End of Win Check

	} while (winCheck != 1);

	if (horse != 0) {
		if (winner != horse) {
			*winnings = 0;
			*bet = 0;
		}
		record[(tracker - 1)] = winner;
	}
	else {
		record[(tracker - 1)] = winner + 10;
	}

	PAUSE;

}

//Done
void GoHome() {

	CLS;

	printf("Created by: Robert Gay, TJ Parrish, Jonathan Rodrigues \n");
	printf("Class: C Programming COP-2220C (Spring 2017)\n");
	printf("Taught by: Professor Dennis Hunchuck\n\n");
	printf("\t\tGoodbye!\n\n");

	PAUSE;
}

//Done
void CloseBin(int winCounter, double money[], double winRecord[], int record[]) {
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