#include <stdio.h>
#include <stdlib.h>

#define CLS system("cls")
#define PAUSE system("pause")
#define FLUSH while (getchar() != '\n')


#define students 1000
#define exams 4

//Prototypes
int OpenBin(int[][exams], int *, int *);

char MENU(int, char *);
int EnterGrades(int [][exams], int);
void StudentAverage(int [][exams], int);
void ExamAverage(int [][exams], int);
void ClassAverage(int [][exams], int);
void ClearGrades(int [][exams], int *, int *);
int SaveAsTXT(int [][exams], int, int);
void TheEXIT();

int CloseBin(int[][exams], int, long long int);


main() {
	char GradesEntered = 0;
	int input = 0, examGrades[students][exams] = { 0 }, i, j, studentVID = 0;
	
	OpenBin(examGrades, &studentVID, &GradesEntered);

	//Menu loop
	do {
		
		input = 0;
		input = MENU(input, &GradesEntered);

		//Switch for Menu Input. Each case calls function appropriate to operation that is being requested. 
		switch (input) {
		case 1:
			//Enter Grades.
			EnterGrades(examGrades, studentVID);
			studentVID++;
			break;

		case 2:
			//Average scores Student.
			StudentAverage(examGrades, studentVID);
			break;

		case 3:
			//Exam average.
			ExamAverage(examGrades, studentVID);
			break;

		case 4:
			//Class Average.
			ClassAverage(examGrades, studentVID);
			break;

		case 5:
			//Clear Grades.
			ClearGrades(examGrades, &studentVID, &GradesEntered);
			break;

		case 6:
			//Save to TXT.
			SaveAsTXT(examGrades, studentVID, GradesEntered);
			break;

		case 7:
			TheEXIT();
			//Quit.
			break;

		default:
			printf("Invalid Entry!\n");
			scanf_s(" %d", &input);
			break;

		}

	} while (input != 7);
	CloseBin(examGrades, studentVID, GradesEntered);
}

int OpenBin(int examGrades[][exams], int *studentVID, int *GradesEntered) {
	int i, temp, loop = students;
	FILE * fd;

	//Checks if file is there, if not then creates it. 
	fopen_s(&fd, "io.bin", "r");
	if (fd == NULL) {
		return 0;
	}

	fread(&temp, sizeof(int), 1, fd);
	*studentVID = temp;
	fread(&temp, sizeof(int), 1, fd);
	*GradesEntered = temp;

	fread(examGrades, sizeof(int), students * exams, fd);

	fclose(fd);
}

//The interactive menu
char MENU(int input, char *GradesEntered) {
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

		scanf_s("%d", &input);
		FLUSH;

		while (*GradesEntered == 0 && input != 1 && input != 7) {
			printf("Please enter in a Student Grade first: "); 
			scanf_s("%d", &input);
			FLUSH;
		}
		if (input == 1) {
			*GradesEntered = 1;
		}

	CLS;

	return input;
}

//Enter Grades in Gradebook
int EnterGrades(int examGrades[][exams], int studentVID)
{
	int i, counter = students + 1;

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

//Give an average for a student
void StudentAverage(int examGrades[][exams], int studentVID) {
	int sum = 0, sum1, i, STUDENT = 0;
	float average;

	printf("Insert Student ID number: V");

	while (STUDENT < (students + studentVID)) {
		scanf_s("%i", &STUDENT);
		FLUSH;

		while ((STUDENT - students) > studentVID || (STUDENT - students) < 0) {
			printf("That student does not exist, try again: V");
			scanf_s("%i", &STUDENT);
			FLUSH;
		}
	}

		for (i = 0; i < exams; i++) {
			sum1 = examGrades[STUDENT - (students + 1)][i];
			sum += sum1;
		}
		average = (float)sum / exams;
		printf("The average grade for the student with the id V%i is: %.2f\n\n", STUDENT, average);
		PAUSE;
	}

//Give an exam average for class
void ExamAverage(int examGrades[][exams], int studentVID) {
	int i, sum = 0, sum1, finder = 0;
	float average;

	printf("Which Exam Average do you want? (1-4): ");

	scanf_s("%i", &finder);
	FLUSH;

	while (finder < 1 || finder > 4) {
		printf("invalid entry, try again: ");
		scanf_s("%i", &finder);
		FLUSH;
	}

	for (i = 0; i < students; i++) {
		sum1 = examGrades[i][finder];
		sum += sum1;
	}

	average = (float)sum / studentVID;
	printf("Exam %i average is: %.2f\n\n", finder, average);
	PAUSE;
}

//Give Class average grade
void ClassAverage(int examGrades[][exams], int studentVID) {
	int i, j, sum = 0, sum1;
	float average;

	for (i = 0; i < exams; i++) {
		for (j = 0; j < students; j++) {
			sum1 = examGrades[j][i];
			sum += sum1;

		}
	}
	average = (float)sum / (exams * studentVID);
	printf("The Class average is: %.2f\n\n", average);
	PAUSE;
}

//Empty Values to restart program
void ClearGrades(int examGrades[][exams], int *studentVID, int *GradesEntered) {
	int i, j;
	char EXIT = 0, input;

	printf("Are you sure you want to clear? (y/n): ");
	

	while (EXIT == 0) {
		scanf_s("%c", &input);
		FLUSH;

		switch (input) {
		case 'y':
		case 'Y':
			for (i = 0; i < exams; i++) {
				for (j = 0; j < students; j++) {
					examGrades[j][i] = 0;
					*studentVID = 0;
					*GradesEntered = 0;
				}
			}
			EXIT = 1;
			break;
		case 'n':
		case 'N':
			EXIT = 1;
			break;
		default:
			printf("invalid entry, try again: ");
			break;
		}
	}
	printf("The grades have been cleared\n\n");
	PAUSE;
}

//Export Grades as a Txt
int SaveAsTXT(int examGrades[][exams], int studentVID, int GradesEntered) {
	int ID = students + 1, i, j;

	FILE * filetemp;


	//Checks if file is there, if not then creates it. 
	fopen_s(&filetemp, "gradebook.txt", "a");

	fprintf_s(filetemp, "**********************************************************************************\n");
	fprintf_s(filetemp, "**  Student ID\t**   Grade 1\t**   Grade 2\t**   Grade 3\t**   Grade 4\t**");

	for (i = 0; i < studentVID; i++) {
		fprintf_s(filetemp, "\n**********************************************************************************\n");
			fprintf_s(filetemp, "**\t%i\t**", ID);
		for (j = 0; j < exams; j++) {
			fprintf_s(filetemp, "\t%i\t**", examGrades[i][j]);
		}
		ID++;
	}
	fprintf_s(filetemp, "\n**********************************************************************************\n\n\n");
	fclose(filetemp);

	printf("Grades has been exported as gradebook.txt.\n\n");
	PAUSE;

}

void TheEXIT() {
	CLS;

	printf("Created by: Rory Corn, Robert Gay, TJ Parrish, Jonathan Rodrigues \n");
	printf("Class: C Programming COP-2220C (Spring 2017)\n");
	printf("Taught by: Professor Dennis Hunchuck\n\n");
	printf("\t\tGoodbye!\n\n");

	PAUSE;
}

int CloseBin(int examGrades[][exams], int studentVID, long long int GradesEntered) {
	FILE * fd;

	//Checks if file is there, if not then creates it. 
	int i;
	
	fopen_s(&fd, "io.bin", "wb");

	fwrite(&studentVID, sizeof(int), 1, fd);
	fwrite(&GradesEntered, sizeof(int), 1, fd);
	fwrite(examGrades, sizeof(int), students * exams, fd);


	fclose(fd);

}
