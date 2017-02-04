#include <stdio.h>
#include <stdlib.h>

#define CLS system("cls")
#define PAUSE system("pause")
#define FLUSH while (getchar() != '\n')


#define students 1000
#define exams 4

//Prototypes
void testFunct();
char MENU(int);
int EnterGrades(int *[students][exams], int);


main() {
	int input = 0, examGrades[students][exams], i, j, studentVID = 0;


	//Menu loop
	do {

		input = MENU(input);

		//Switch for Menu Input. Each case calls function appropriate to operation that is being requested. 
		switch (input) {
		case 1:
			//Enter Grades.
			EnterGrades(examGrades, studentVID);
			studentVID++;
			break;

		case 2:
			//Average scores Student.
			testFunct();
			break;

		case 3:
			//Exam average.
			testFunct();
			break;

		case 4:
			//Class Average.
			testFunct();
			break;

		case 5:
			//Clear Grades.
			testFunct();
			break;

		case 6:
			//Save to TXT.
			testFunct();
			break;

		case 7:
			//Quit.
			break;

		default:
			printf("Invalid Entry!\n");
			scanf_s(" %d", &input);
			break;



		}

	} while (input != 7);

}

void testFunct() {

	printf("Test.\n");

	PAUSE;

}

char MENU(int input) {
	CLS;

	printf("Grade Tracker\n");
	printf("Please choose an option:\n");
	printf("1. Enter Grades.\n");
	printf("2. Find Student Average.\n");
	printf("3. Find Exam Average.\n");
	printf("4. Find Class Average.\n");
	printf("5. Clear Grades.\n");
	printf("6. Save to Text File. \n");
	printf("7. Save and Quit.\n\n");

	printf("Input: ");
	scanf_s(" %d", &input);

	FLUSH;
	CLS;

	return input;
}

int EnterGrades(int *examGrades[students][exams], int studentVID)
{
	int i, counter = 1001;

	//Student VID assigner
	if (counter > 0) {
		printf("Student VID: V%4i\n\n", studentVID + counter);
	}

	printf("Exam grades:\n");

	//Grades loop
	for (i = 0; i < exams; i++)
	{
		printf("Exam #%d, Grade: ", i + 1);
		scanf_s("%d", &examGrades[studentVID][i]);
		FLUSH;
	}

}

