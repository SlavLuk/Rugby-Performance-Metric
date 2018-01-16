


#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
Name :Vyacheslav Lukyanov

ID : G00339839

Program Description :Rugby Performance Metric Ltd.

*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

//login struct
 struct Login {

	char pass[7];
	char userName[7];
};

 //players struct
 struct Players {

	 int pIrfu;
	 char firstName[25];
	 char secondName[25];
	 int age;
	 int height;
	 int weight;
	 char club[25];
	 char email[30];
	 char plyPosit[25];
	 int missedTackle;
	 int madeMetre;

	 struct Players * next;
 };

 //method's prototypes
 void addPlayerAtStart(struct Players **top,int irfu);
 void addPlayerAtPosition(struct Players *top, int irfu,int pos);
 void addPlayerAtEnd(struct Players *top, int irfu, int pos);
 void displayAllPlayers(struct Players *top);
 void displayPlayerDetailsByIrfu(struct Players *top,int irfu);
 void displayPlayerDetailsByName(struct Players *top, char * name);
 void displayPlayerByPosition(struct Players * top, char *pos,int flag);
 void displayPlayerByWeight(struct Players * top, int weight);
 void updatePlayerDetailsByIrfu(struct Players *top, int irfu);
 void updatePlayerDetailsByName(struct Players *top, char * name);
 void deletePlayerAtStart(struct Players **top);
 void deletePlayerAtPosition(struct Players *top, int pos);
 void deletePlayerAtEnd(struct Players *top);
 void printToReportFile(struct Players *top);
 void printToDetailFile(struct Players *top);
 int size(struct Players *top);
 int search(struct Players *top, int irfu);
 void sort(struct Players *top);
 void sortReverse(struct Players *top);
 int searchPos(struct Players *top, int irfu);
 void getDataAtStart(struct Players **top, int irfu, char * fname, char*sname,int age,int height,int weight,char *club, char * email, char*pPos, int missedTack, int metr);
 void getDataAtEnd(struct Players *top, int irfu, char * fname, char*sname, int age, int height, int weight, char *club, char * email, char*pPos, int missedTack, int metr);
 int checkEmail(char *email);

void main() {

	//declare variables
	FILE* filePtr,*ptrSize;
	struct Login *log=NULL;
	struct Players * player = NULL;
	int irfu;
	char fname[25];
	char sname[25];
	int age, height, weigt; 
	int mTack;
	int metr;
	char club[25];
	char email[25];
	char pos[25];
	char blank[6];
	char pass[7];
	char userName[7];
	int found = 0;
	int choice,i=0,j=0;
	
	
	log = (struct Login*)malloc(sizeof(struct Login));

	//default user name and password in case the login file is empty
	strcpy(log->userName, "rootme");
	strcpy(log->pass, "rootme");

	do { //read in user name
		printf("Please enter your user name 6 chracters in length:\n");

		userName[6] = '\0';

		for (int i = 0; i < 6; i++) {

			userName[i] = getch();

			putch(userName[i]);
		}

		getch();
				//read in user pass
		printf("\nEnter your password 6 chracters in length:\n");

		pass[6] = '\0';

		for (int i = 0; i < 6; i++) {

			pass[i] = getch();

			blank[i] = '*';

			putch(blank[i]);
		}

		getch();

		filePtr = fopen("./login.txt", "r");

		if (filePtr == NULL) {

			puts("\nCan not open file...\n");

			exit(0);
		}
		else {
					//check on user details against the login file
			while (!feof(filePtr)) {

				fscanf(filePtr, "%s %s", log->userName, log->pass);
				
				if (strcmp(log->userName, userName) == 0 && strcmp(log->pass, pass) == 0) {

					found = 1;

					printf("\nYou have been logged in\n");
				}

			}//end while

			if (!found) {//if not found

				puts("\nInvalid password or user name...\n");
			}		
		}

		if (filePtr != NULL) {

			fclose(filePtr);
		}

	} while (!found);//end while log in

	filePtr = fopen("./Rugby.txt", "r");//open files for reading
	ptrSize = fopen("./size.txt", "r");

	if (filePtr == NULL || ptrSize==NULL) {//if files don't exist

		puts("\nSorry can not open a file...\n");
	}
	else {

		while (!feof(ptrSize)) {//reading file size on records

			fscanf(ptrSize, "%d", &i);

		}

		fclose(ptrSize);

		if (i == 0) {

			puts("\nSorry no records in the file...\n");

		}
		else if (i > 0) {

			while (j < i) {//populating player struct with data from file

				fscanf(filePtr, "%d %s %s %d %d %d %s %s %s %d %d", &irfu, fname, sname,&age,&height,&weigt,club,email,pos,&mTack,&metr);

				if (player == NULL) {

					getDataAtStart(&player, irfu, fname, sname, age, height, weigt, club,email, pos, mTack, metr);//first data node

				}
				else {

					getDataAtEnd(player, irfu, fname, sname, age, height, weigt, club,email, pos, mTack, metr);//following next nodes after first
	
				}

				j++;
			}

		}

		fclose(filePtr);
		

		printf("\nThere are %d records\n",i);
	}
		//user menu
	puts("Please select a menu number to proceed or -1 to exit\n");
	printf(" 1) Add player\n");
	printf(" 2) Display all players to screen\n");
	printf(" 3) Display player details\n");
	printf(" 4) Update a player's statistic\n");
	printf(" 5) Delete player\n");
	printf(" 6) Generate statistics (a-h) based on the user selection\n");
	printf(" 7) Print all player details into a report file\n");
	printf(" 8) List all players of the following categories in order of height\n");

	scanf("%d", &choice);

	while (choice != -1) {


		switch (choice) {

		case 1:

			puts("\nPlease enter a player IRFU number to add\n");
			scanf("%s", sname);

			irfu = atoi(sname);//validating user input ,if it is an integer or a string being parsed to integer 

			if (irfu <= 0) {

				puts("\nInvalid input...\n");
			}
			else {

				if (player == NULL || search(player, irfu) == 1) {//if it is first node


					addPlayerAtStart(&player, irfu);

				}
				else if (search(player, irfu) == 0) {//if 0 player is already in database

					puts("\nSorry the player already in database...\n");

				}
				else {

					int pos = search(player, irfu);

					if (pos <= size(player)) {//add node at the position

						addPlayerAtPosition(player, irfu, pos);
					}
					else {

						addPlayerAtEnd(player, irfu, pos);//if greater than size
					}
				}

			}

			

			break;
		case 2:

			displayAllPlayers(player);//show all players

			break;
		case 3:

			printf("\n Please enter a player IRFU ID or a second name\n");

			scanf("%s", sname);

			irfu = atoi(sname);//if can not parse to integer goes to find by second name

			if (irfu == 0) {

				displayPlayerDetailsByName(player, sname);

			}
			else {

				displayPlayerDetailsByIrfu(player, irfu);				

			}

			break;

		case 4:

			printf("\n Please enter a player IRFU ID or a second name\n");

			scanf("%s", sname);

			irfu = atoi(sname);//if can not parse to integer goes to find by second name

			if (irfu == 0) {

				updatePlayerDetailsByName(player, sname);

			}
			else {

				updatePlayerDetailsByIrfu(player, irfu);

			}

			
			break;
		case 5:

			puts("\nPlease enter a player IRFU number to delete\n");

			scanf("%s", sname);

			irfu = atoi(sname);//validating user input

			if (irfu == 0) {

				puts("\nInvalid input...\n");

			}

			if (player == NULL) {//no records

				puts("\nThe list is already empty\n");

			}else if (searchPos(player, irfu) == 1){

				printf("\nDeleting player at pos %d\n", searchPos(player, irfu));

				deletePlayerAtStart(&player);
			

			}else{

				int pos = searchPos(player, irfu);

				if (pos <= 0) {//invalid input

					puts("\nSorry no such player in database...\n");
				

				}else if (pos <= size(player)){//less than link size and not the first node

					printf("\nDeleting player at pos %d\n", searchPos(player, irfu));
					deletePlayerAtPosition(player, pos);
					
				
				}else {

					printf("\nDeleting player at pos %d\n", searchPos(player, irfu));
					deletePlayerAtEnd(player);
	
				}
			}

			break;
		case 6:

			printf("\nPlease select one of the criteria\n");
			printf(" 1)Player position (case sensitive)\n");
			printf(" 2)Player weight\n");

			int choice, weight;
			char pos[25];

			scanf("%s", sname);

			choice = atoi(sname);//validating user input
		
			switch (choice){

			case 1:
				puts(" Please enter player position\n");
				scanf("%s", pos);


				displayPlayerByPosition(player, pos,1);

				break;
			case 2:

				puts(" Please enter player weight\n");
				scanf("%s", sname);

				weight = atoi(sname);

				while (weight <= 0) {

					puts("\nInvalid input...\n");

					puts(" Please enter player weight\n");
					scanf("%s", sname);

					weight = atoi(sname);
				}

				displayPlayerByWeight(player, weight);

				break;

			default:

				puts("\nSorry invalid input...\n");

				break;
			}

			break;
		case 7:

			printToReportFile(player);//print into a report file

			break;
		case 8:


			if (player == NULL) {

				puts("\nSorry no data in the database...\n");

			}
			else {

				puts("\nPlease select the following categories\n");
				puts(" 1)Second-row\n");
				puts(" 2)Back-row\n");

				sort(player);//sort link list by height

				scanf("%s", sname);

				choice = atoi(sname);//validate input

				if (choice <= 0) {

					puts("\nSorry invalid input...\n");
				}
				else if (choice == 1) {

					displayPlayerByPosition(player, "Second-row", 0);

				}
				else if (choice == 2) {

					displayPlayerByPosition(player, "Back-row", 0);

				}
				else {

					puts("\nSorry invalid input...\n");

				}

				sortReverse(player);//sort link list back to the original state by irfu number
			}
	
			break;
	
		default:

			puts("\nSorry invalid input...\n");

			break;
		}

		puts("\nPlease select a menu number to procced or -1 to exit\n");
		printf(" 1) Add player\n");
		printf(" 2) Display all players to screen\n");
		printf(" 3) Display player details\n");
		printf(" 4) Update a player's statistic\n");
		printf(" 5) Delete player\n");
		printf(" 6) Generate statistics (a-h) based on the user selection\n");
		printf(" 7) Print all player details into a report file\n");
		printf(" 8) List all players of the following categories in order of height\n");

		scanf("%d", &choice);

		if (choice == -1 && player!=NULL) {//print  or uptade player's file if the player link list has anything in it

			printToDetailFile(player);
		}
	

	}//end while loop

	free(log);//free login memory

	getch();

}//end main method

//method declaration
void displayPlayerDetailsByName(struct Players *top, char * name) {

	struct Players *temp;

	temp = top;

	int found = 0;

	printf(" ---------------------------------------------------------------------------------------------------------------------------------");
	printf("\n|IRFU | First name | Second name | Age | Height | Weight |    Club    |     Email Addr   |  Position | Missed Tackle | Metre Made |\n");
	printf(" ---------------------------------------------------------------------------------------------------------------------------------");

	while (temp != NULL){//go thru all nodes

		if (strcmp(name, temp->secondName) == 0){//if names matched

			
			printf("\n|%5d  %11s  %11s  %4d  %7d  %7d  %11s   %15s  %11s %12d %14d  |\n", temp->pIrfu, temp->firstName, temp->secondName, temp->age,
				temp->height, temp->weight, temp->club, temp->email, temp->plyPosit, temp->missedTackle, temp->madeMetre);

			found = 1;
		}

		temp = temp->next;
	}

	if (!found) {

		puts("\nSorry no such player in database...\n");
	}

}

void displayPlayerByWeight(struct Players * top, int weight) {

	//declare variables
	struct Players *temp;
	int found = 0;
	int noMissed = 0, missedLess3 = 0, missedLess5 = 0, missedMore5 = 0;
	int noMade = 0, madeLess10 = 0, madeLess20 = 0, madeMore20 = 0;

	printf(" ---------------------------------------------------------------------------------------------------------------------------------");
	printf("\n|IRFU | First name | Second name | Age | Height | Weight |    Club    |     Email Addr   |  Position | Missed Tackle | Metre Made |\n");
	printf(" ---------------------------------------------------------------------------------------------------------------------------------");

	temp = top;

	while (temp != NULL) {

		if (weight <= temp->weight) {//check on weight and print out report if weight greater or equal

			printf("\n|%5d  %11s  %11s  %4d  %7d  %7d  %11s   %15s  %11s %12d %14d  |\n", temp->pIrfu, temp->firstName, temp->secondName, temp->age,
				temp->height, temp->weight, temp->club, temp->email, temp->plyPosit, temp->missedTackle, temp->madeMetre);

			//sum up all info about particular players
			if (temp->missedTackle == 0) {

				noMissed++;

			}
			if (temp->missedTackle >0 && temp->missedTackle < 3) {

				missedLess3++;

			}
			if (temp->missedTackle >0 && temp->missedTackle<5) {

				missedLess5++;
			}
			if (temp->missedTackle >= 5) {

				missedMore5++;

			}

			if (temp->madeMetre == 0) {

				noMade++;
			}
			if (temp->madeMetre>0 && temp->madeMetre < 10) {

				madeLess10++;
			}
			if (temp->madeMetre>0 && temp->madeMetre < 20) {

				madeLess20++;
			}
			if (temp->madeMetre >= 20) {

				madeMore20++;

			}

			found = 1;
		}

		temp = temp->next;

	}

	if (!found) {

		puts("\nSorry no such player in database...\n");
	}
	else {//print out report 

		printf("\n %d of players who miss no tackles\n", noMissed);
		printf(" %d of players who miss less than 3 tackles per match\n", missedLess3);
		printf(" %d of players who miss less than 5 tackles per match\n", missedLess5);
		printf(" %d of players who miss more than 5 tackles per match\n", missedMore5);
		printf(" %d of players who make no metres in a game\n", noMade);
		printf(" %d of players who make less than 10 metres in a game\n", madeLess10);
		printf(" %d of players who make less than 20 metres in a game\n", madeLess20);
		printf(" %d of players who make more than 20 metres in a game\n", madeMore20);
	}
}

void displayPlayerDetailsByIrfu(struct Players *top, int irfu) {

	struct Players *temp;

	temp = top;

	int found = 0;

	while (temp != NULL){

		if (irfu == temp->pIrfu){

		printf(" ---------------------------------------------------------------------------------------------------------------------------------");
		printf("\n|IRFU | First name | Second name | Age | Height | Weight |    Club    |     Email Addr   |  Position | Missed Tackle | Metre Made |\n");
		printf(" ---------------------------------------------------------------------------------------------------------------------------------");
		printf("\n|%5d  %11s  %11s  %4d  %7d  %7d  %11s   %15s  %11s %12d %14d  |\n", temp->pIrfu, temp->firstName, temp->secondName, temp->age,
														temp->height, temp->weight,temp->club, temp->email,temp->plyPosit, temp->missedTackle, temp->madeMetre);

			found = 1;
		}

		temp = temp->next;

	}

	if (!found) {

		puts("\nSorry no such player in database...\n");
	}
}

void addPlayerAtEnd(struct Players *top, int irfu, int pos) {

	//declare variables
	struct Players * temp;
	char email[25];
	char email1[25];
	int parseInt;
	temp = top;

	while (temp->next != NULL) {

		temp = temp->next; // go to the last node

	}

	struct Players * newNode;
	newNode = (struct Players*)malloc(sizeof(struct Players));//allocate memory for a new node

	//read in all info from user
	newNode->pIrfu = irfu;

	puts("\nPlease enter a player first name\n");
	scanf("%s", newNode->firstName);

	puts("\nPlease enter a player second name\n");
	scanf("%s", newNode->secondName);

	puts("\nPlease enter an age\n");
	scanf("%s", email);
	parseInt = atoi(email);//validate input ,just reusing email and parseInt variables

	while (parseInt <= 0) {

		puts("\nInvalid input...\n");

		puts("\nPlease enter an age\n");
		scanf("%s", email);

		parseInt = atoi(email);
	}

	newNode->age = parseInt;

	puts("\nPlease enter a height\n");
	scanf("%s", email);
	parseInt = atoi(email);//validate input ,just reusing email and parseInt variables

	while (parseInt <= 0) {

		puts("\nInvalid input...\n");

		puts("\nPlease enter a height\n");
		scanf("%s", email);

		parseInt = atoi(email);
	}

	newNode->height = parseInt;

	puts("\nPlease enter a weight\n");
	scanf("%s", email);
	parseInt = atoi(email);//validate input ,just reusing email and parseInt variables

	while (parseInt <= 0) {

		puts("\nInvalid input...\n");

		puts("\nPlease enter a weight\n");
		scanf("%s", email);

		parseInt = atoi(email);
	}

	newNode->weight = parseInt;

	puts("\nPlease enter a club name\n");
	scanf("%s", newNode->club);

	puts("\nPlease enter an email address\n");
	scanf("%s", email);
	strcpy(email1, email);

	while (!checkEmail(email)) {//validate e-mail address (must have @ and .com )

		puts("\nInvalid email address...\n");

		puts("\nPlease enter an email address\n");
		scanf("%s", email);
		strcpy(email1, email);
	}

	strcpy(newNode->email, email1);

	puts("\nPlease enter a player positon separated by hyphen(Back-row)\n");
	scanf("%s", newNode->plyPosit);

	puts("\nPlease enter a missed tackle per match\n");
	scanf("%d", &parseInt);
	
	fseek(stdin, 0, SEEK_END);

	while (parseInt < 0) {

		puts("\nInvalid input...\n");

		puts("\nPlease enter a missed tackle per match\n");
		scanf("%d", &parseInt);
		fseek(stdin, 0, SEEK_END);
	}
	newNode->missedTackle = parseInt;

	puts("\nPlease enter  metres made in a game\n");
	scanf("%d", &parseInt);

	fseek(stdin, 0, SEEK_END);

	while (parseInt < 0) {

		puts("\nInvalid input...\n");

		puts("\nPlease enter  metres made in a game\n");
		scanf("%d", &parseInt);
		fseek(stdin, 0, SEEK_END);
	}
	newNode->madeMetre = parseInt;


	newNode->next = NULL;
	temp->next = newNode;

}

void displayPlayerByPosition(struct Players * top, char *pos,int flag) {

	//declare variables
	struct Players *temp;
	int noMissed = 0, missedLess3 = 0, missedLess5 = 0, missedMore5 = 0;
	int noMade = 0, madeLess10 = 0, madeLess20 = 0, madeMore20 = 0;

	temp = top;

	int found = 0;

	printf(" ---------------------------------------------------------------------------------------------------------------------------------");
	printf("\n|IRFU | First name | Second name | Age | Height | Weight |    Club    |     Email Addr   |  Position | Missed Tackle | Metre Made |\n");
	printf(" ---------------------------------------------------------------------------------------------------------------------------------");

	while (temp != NULL) {

		if (strcmp(pos, temp->plyPosit) == 0) {//if position match show records and a report
	
			printf("\n|%5d  %11s  %11s  %4d  %7d  %7d  %11s   %15s  %11s %12d %14d  |\n", temp->pIrfu, temp->firstName, temp->secondName, temp->age,
				temp->height, temp->weight, temp->club, temp->email, temp->plyPosit, temp->missedTackle, temp->madeMetre);

			if (temp->missedTackle == 0) {

				noMissed++;
			}

			if (temp->missedTackle >0 && temp->missedTackle < 3) {

				missedLess3++;

			}
			if (temp->missedTackle >0 && temp->missedTackle<5) {

				missedLess5++;
			}
			if (temp->missedTackle >= 5) {

				missedMore5++;

			}

			if (temp->madeMetre == 0) {

				noMade++;
			}
			if (temp->madeMetre>0 && temp->madeMetre < 10) {

				madeLess10++;
			}
			if (temp->madeMetre>0 && temp->madeMetre < 20) {

				madeLess20++;
			}
			if (temp->madeMetre >= 20) {

				madeMore20++;
			}

			found = 1;
		}

		temp = temp->next;

	}//end while loop

	if (!found) {

		puts("\nSorry no such player in database...\n");
	}
	else if(found && flag){//flag variable used just to reuse this method and not to print report

		printf("\n %d of players who miss no tackles\n",noMissed);
		printf(" %d of players who miss less than 3 tackles per match\n", missedLess3);
		printf(" %d of players who miss less than 5 tackles per match\n", missedLess5);
		printf(" %d of players who miss more than 5 tackles per match\n", missedMore5);
		printf(" %d of players who make no metres in a game\n", noMade);
		printf(" %d of players who make less than 10 metres in a game\n", madeLess10);
		printf(" %d of players who make less than 20 metres in a game\n", madeLess20);
		printf(" %d of players who make more than 20 metres in a game\n", madeMore20);

	}

}

void displayAllPlayers(struct Players * top) {

	struct Players *temp;

	temp = top;

	if (top == NULL) {

		puts("\nSorry no players to show...\n");
	}
	else {

		printf(" ---------------------------------------------------------------------------------------------------------------------------------");
		printf("\n|IRFU | First name | Second name | Age | Height | Weight |    Club    |     Email Addr   |  Position | Missed Tackle | Metre Made |\n");
		printf(" ---------------------------------------------------------------------------------------------------------------------------------");
	}

	while (temp != NULL){//go thru all node and print out

		printf("\n|%5d  %11s  %11s  %4d  %7d  %7d  %11s   %15s  %11s %12d %14d  |\n", temp->pIrfu, temp->firstName, temp->secondName, temp->age,
														temp->height, temp->weight,temp->club, temp->email,temp->plyPosit, temp->missedTackle, temp->madeMetre);
	

		temp = temp->next;

	}
}

void getDataAtStart(struct Players **top, int irfu, char * fname, char*sname, int age, int height, int weight, char *club, char * email, char*pPos, int missedTack, int metr) {

	struct Players *newNode;

	newNode = (struct Players*)malloc(sizeof(struct Players));//allocate memory space for a new node

	//copy data from a file into struct
	newNode->pIrfu = irfu;
	strcpy(newNode->firstName, fname);
	strcpy(newNode->secondName, sname);
	newNode->age = age;
	newNode->height = height;
	newNode->weight = weight;
	strcpy(newNode->club, club);
	strcpy(newNode->email, email);
	strcpy(newNode->plyPosit, pPos);
	newNode->missedTackle = missedTack;
	newNode->madeMetre = metr;
	
	newNode->next = *top;

	*top = newNode;
}

void getDataAtEnd(struct Players *top, int irfu, char * fname, char*sname, int age, int height, int weight, char *club, char * email, char*pPos, int missedTack, int metr) {

	struct Players * temp;
	temp = top;

	while (temp->next != NULL) {

		temp = temp->next;//move pointer to last node

	}

	struct Players * newNode;
	newNode = (struct Players*)malloc(sizeof(struct Players));//allocate memory space for a new node

	 //copy data from a file into struct
	newNode->pIrfu = irfu;
	strcpy(newNode->firstName, fname);
	strcpy(newNode->secondName, sname);
	newNode->age = age;
	newNode->height = height;
	newNode->weight = weight;
	strcpy(newNode->club, club);
	strcpy(newNode->email, email);
	strcpy(newNode->plyPosit, pPos);
	newNode->missedTackle = missedTack;
	newNode->madeMetre = metr;

	newNode->next = NULL;
	temp->next = newNode;
}

int checkEmail(const char *email) {

	char email2[25];
	char * check;
	char *checkCom;
	char at[] = "@";
	char fullStop = '.';
	int i = 0;

	strcpy(email2, email);

	check = strtok(email, at);//delimiter is @  if strtok return more than one string means @ exists in that string

	while (check != NULL) {

		i++;

		check = strtok(NULL, at);
	}

	if (i == 1) {//no @ in email address

		return 0;
	}
	else {

		checkCom = strrchr(email2, fullStop);//check on the last occurence of full stop (.) and return a string after (.) inclusive

		if (checkCom != NULL) {

			if (strcmp(checkCom, ".com") == 0) {//if two strings match return 1 email is valid

				return 1;

			}
			else {

				return 0;
			}
		}
	}
}

void addPlayerAtStart(struct Players **top,int irfu) {
	
	struct Players *newNode;
	char email[25];
	char email1[25];
	int parseInt;

	newNode = (struct Players*)malloc(sizeof(struct Players));//allocate a memory space for a new node

	newNode->pIrfu = irfu;

	//read in a user input and validate it
	puts("\nPlease enter a player first name\n");
	scanf("%s", newNode->firstName);

	puts("\nPlease enter a player second name\n");
	scanf("%s", newNode->secondName);

	puts("\nPlease enter an age\n");
	scanf("%s", email);
	parseInt = atoi(email);

	while (parseInt <= 0) {

		puts("\nInvalid input...\n");

		puts("\nPlease enter an age\n");
		scanf("%s", email);

		parseInt = atoi(email);
	}

	newNode->age = parseInt;

	puts("\nPlease enter a height\n");
	scanf("%s", email);
	parseInt = atoi(email);

	while (parseInt <= 0) {

		puts("\nInvalid input...\n");

		puts("\nPlease enter a height\n");
		scanf("%s", email);

		parseInt = atoi(email);
	}

	newNode->height = parseInt;

	puts("\nPlease enter a weight\n");
	scanf("%s", email);
	parseInt = atoi(email);

	while (parseInt <= 0) {

		puts("\nInvalid input...\n");

		puts("\nPlease enter a weight\n");
		scanf("%s", email);

		parseInt = atoi(email);
	}

	newNode->weight = parseInt;

	puts("\nPlease enter a club name\n");
	scanf("%s", newNode->club);

	puts("\nPlease enter an email address\n");
	scanf("%s", email);
	strcpy(email1, email);

	while (!checkEmail(email)) {

		puts("\nInvalid email address...\n");

		puts("\nPlease enter an email address\n");
		scanf("%s", email);
		strcpy(email1, email);
	}

	strcpy(newNode->email, email1);

	puts("\nPlease enter a player positon separated by hyphen(Back-row)\n");
	scanf("%s", newNode->plyPosit);

	puts("\nPlease enter a missed tackle per match\n");
	scanf("%d", &parseInt);

	fseek(stdin, 0, SEEK_END);

	while (parseInt < 0) {

		puts("\nInvalid input...\n");

		puts("\nPlease enter a missed tackle per match\n");
		scanf("%d", &parseInt);
		fseek(stdin, 0, SEEK_END);
	}
	newNode->missedTackle = parseInt;

	puts("\nPlease enter  metres made in a game\n");
	scanf("%d", &parseInt);

	fseek(stdin, 0, SEEK_END);

	while (parseInt < 0) {

		puts("\nInvalid input...\n");

		puts("\nPlease enter  metres made in a game\n");
		scanf("%d", &parseInt);
		fseek(stdin, 0, SEEK_END);
	}
	newNode->madeMetre = parseInt;

	newNode->next = *top;

	*top = newNode;
}


void addPlayerAtPosition(struct Players *top, int irfu,int pos) {

	//declare variables
	int i, parseInt, result;
	char email[25];
	char email1[25];
	struct Players *temp;
	struct Players *prev;
	struct Players *newNode;

	
		temp = top;

		
		for (i = 0; i<pos-1; i++){// loop until the position required by the user

			prev = temp;
			temp = temp->next;

		}

		newNode = (struct Players*)malloc(sizeof(struct Players));//aloccate a memory
	
		newNode->pIrfu = irfu;

		//read in inputs
		puts("\nPlease enter a player first name\n");
		scanf("%s", newNode->firstName);

		puts("\nPlease enter a player second name\n");
		scanf("%s", newNode->secondName);

		puts("\nPlease enter an age\n");
		scanf("%s", email);
		parseInt = atoi(email);

		while (parseInt <= 0) {

			puts("\nInvalid input...\n");

			puts("\nPlease enter an age\n");
			scanf("%s", email);

			parseInt = atoi(email);
		}

		newNode->age = parseInt;

		puts("\nPlease enter a height\n");
		scanf("%s", email);
		parseInt = atoi(email);

		while (parseInt <= 0) {

			puts("\nInvalid input...\n");

			puts("\nPlease enter a height\n");
			scanf("%s", email);

			parseInt = atoi(email);
		}

		newNode->height = parseInt;

		puts("\nPlease enter a weight\n");
		scanf("%s", email);
		parseInt = atoi(email);

		while (parseInt <= 0) {

			puts("\nInvalid input...\n");

			puts("\nPlease enter a weight\n");
			scanf("%s", email);

			parseInt = atoi(email);
		}

		newNode->weight = parseInt;

		puts("\nPlease enter a club name\n");
		scanf("%s", newNode->club);

		puts("\nPlease enter an email address\n");
		scanf("%s", email);
		strcpy(email1, email);

		while (!checkEmail(email)) {

			puts("\nInvalid email address...\n");

			puts("\nPlease enter an email address\n");
			scanf("%s", email);
			strcpy(email1, email);
		}

		strcpy(newNode->email, email1);

		puts("\nPlease enter a player positon separated by hyphen(Back-row)\n");
		scanf("%s", newNode->plyPosit);

		puts("\nPlease enter a missed tackle per match\n");
		scanf("%d", &parseInt);

		fseek(stdin, 0, SEEK_END);
	
		while (parseInt < 0) {

			puts("\nInvalid input...\n");

			puts("\nPlease enter a missed tackle per match\n");
			scanf("%d", &parseInt);
			fseek(stdin, 0, SEEK_END);
		}
		newNode->missedTackle = parseInt;

		puts("\nPlease enter  metres made in a game\n");
		scanf("%d", &parseInt);

		fseek(stdin, 0, SEEK_END);

		while (parseInt < 0) {

			puts("\nInvalid input...\n");

			puts("\nPlease enter  metres made in a game\n");
			scanf("%d", &parseInt);
			fseek(stdin, 0, SEEK_END);
		}
		newNode->madeMetre = parseInt;
		
		//link up the node after the last node in the list.
		prev->next = newNode;
		newNode->next = temp;
}

//searching a player by the position
int searchPos(struct Players *top, int irfu) {

	struct Players *temp;

	temp = top;

	int pos = 0;

	int found = 0;

	while (temp != NULL) {//go thru all the nodes

		pos++;

		if (irfu == temp->pIrfu)//if pos found return a position
		{
			found = pos;

			return found;
		}

		temp = temp->next;

	}

	return found;//not found return 0
}

void deletePlayerAtStart(struct Players **top) {//deleting a first node

	struct Players * temp;

	temp = *top;
	*top = temp->next;

	free(temp);
}

int search(struct Players *top, int irfu) {

	struct Players *temp;

	temp = top;

	int pos = 0;

	int found = 0;


	while (temp != NULL){

		pos++;

		if (irfu == temp->pIrfu)
		{
			
			return 0;
		}
		else if (irfu < temp->pIrfu) {

			found = pos;

			return found;

		}else if(pos == size(top)) {

			found = pos;

			found++;

			return found;
		}

		temp = temp->next;

	}
}

int size(struct Players *top) {

	struct Players * temp;
	int counter = 0;

	temp = top;

	while (temp != NULL) {//go thru all node and count

		counter++;

		temp = temp->next;

	}

	return counter;
}
void updatePlayerDetailsByName(struct Players *top, char * name) {

	//declare variables
	struct Players *temp;
	int choice;
	char fname[25];
	char sname[25];
	int age, height, weight;
	int missed;
	int metre;
	char club[25];
	char email[25];
	char email1[25];
	char position[25];

	temp = top;

	int found = 0;

	while (temp != NULL) {//go thru all nodes

		if (strcmp(name, temp->secondName) == 0) {//a match found


			printf(" ---------------------------------------------------------------------------------------------------------------------------------");
			printf("\n|IRFU | First name | Second name | Age | Height | Weight |    Club    |     Email Addr   |  Position | Missed Tackle | Metre Made |\n");
			printf(" ---------------------------------------------------------------------------------------------------------------------------------");

			printf("\n|%5d  %11s  %11s  %4d  %7d  %7d  %11s   %15s  %11s %12d %14d  |\n", temp->pIrfu, temp->firstName, temp->secondName, temp->age,
				temp->height, temp->weight, temp->club, temp->email, temp->plyPosit, temp->missedTackle, temp->madeMetre);

			//ask what to update
			printf("\nPlease enter number what you would like to update or -1 to cancel\n");
			puts("\n 1) First name\n");
			puts(" 2) Second name\n");
			puts(" 3) Age\n");
			puts(" 4) Height\n");
			puts(" 5) Weight\n");
			puts(" 6) Club\n");
			puts(" 7) Email Addr \n");
			puts(" 8) Position\n");
			puts(" 9) Missed Tackle\n");
			puts(" 10) Metre Made");
			scanf("%d", &choice);

			while (choice != -1) {//updating based on a choice above

				switch (choice) {

				case 1:
					puts(" Please enter a new first name\n");
					scanf("%s", fname);

					strcpy(temp->firstName, fname);

					break;
				case 2:
					puts(" Please enter a new second name\n");
					scanf("%s", sname);

					strcpy(temp->secondName, sname);

					break;
				case 3:
					puts(" Please enter a new age\n");
					scanf("%s", sname);

					age = atoi(sname);//validate input if atoi function can not parse to a integer,input is invalid

					while (age <= 0) {

						puts("\nInvalid input...\n");

						puts(" Please enter a new age\n");
						scanf("%s", sname);

						age = atoi(sname);
					}

					temp->age = age;

					break;
				case 4:
					puts(" Please enter a new height\n");
					scanf("%s", sname);

					height = atoi(sname);//validate input if atoi function can not parse to a integer,input is invalid

					while (height <= 0) {

						puts("\nInvalid input...\n");

						puts(" Please enter a new height\n");
						scanf("%s", sname);

						height = atoi(sname);
					}

					temp->height = height;

					break;
				case 5:
					puts(" Please enter a new weight\n");
					scanf("%s", sname);

					weight = atoi(sname);//validate input if atoi function can not parse to a integer,input is invalid

					while (weight <= 0) {

						puts("\nInvalid input...\n");

						puts(" Please enter a new weight\n");
						scanf("%s", sname);

						weight = atoi(sname);
					}

					temp->weight = weight;

					break;
				case 6:
					puts(" Please enter a new club name\n");
					scanf("%s", club);

					strcpy(temp->club, club);

					break;
				case 7:
					puts(" Please enter a new email addr\n");
					scanf("%s", email);
					strcpy(email1, email);

					while (!checkEmail(email)) {//validate e-mail

						puts("\nPlease enter a new email addr\n");
						scanf("%s", email);
						strcpy(email1, email);
					}

					strcpy(temp->email, email1);

					break;
				case 8:
					puts(" Please enter a new position\n");
					scanf("%s", position);

					strcpy(temp->plyPosit, position);
					break;
				case 9:

					puts(" Please enter a new missed tackles\n");
					scanf("%s", sname);

					missed = atoi(sname);

					while (missed < 0) {

						puts("\nInvalid input...\n");

						puts(" Please enter a new missed tackles\n");
						scanf("%s", sname);

						missed = atoi(sname);
					}

					temp->missedTackle = missed;

					break;
				case 10:

					puts(" Please enter a new metres made\n");
					scanf("%s", sname);

					metre = atoi(sname);

					while (metre < 0) {

						puts("\nInvalid input...\n");

						puts(" Please enter a new metres made\n");
						scanf("%s", sname);

						metre = atoi(sname);
					}

					temp->madeMetre = metre;

					break;	


				default:
					puts("\nInvalid input....\n");

					break;
				}

				printf("\nPlease enter number what you would like to update or -1 to cancel\n");
				puts("\n 1) First name\n");
				puts(" 2) Second name\n");
				puts(" 3) Age\n");
				puts(" 4) Height\n");
				puts(" 5) Weight\n");
				puts(" 6) Club\n");
				puts(" 7) Email Addr \n");
				puts(" 8) Position\n");
				puts(" 9) Missed Tackle\n");
				puts(" 10) Metre Made");
				scanf("%d", &choice);
			}

			found = 1;
		}

		temp = temp->next;
	}

	if (!found) {

		puts("\nSorry no such player in database...\n");
	}

}

void updatePlayerDetailsByIrfu(struct Players *top, int irfu) {//the same method as update by name

	//declare local variables
	struct Players *temp;
	int choice;
	char fname[25];
	char sname[25];
	int age, height, weight;
	int missed;
	int metre;
	char club[25];
	char email[25];
	char email1[25];
	char position[25];

	temp = top;

	int found = 0;

	while (temp != NULL) {

		if (irfu == temp->pIrfu) {//matched irfu found


			printf(" ---------------------------------------------------------------------------------------------------------------------------------");
			printf("\n|IRFU | First name | Second name | Age | Height | Weight |    Club    |     Email Addr   |  Position | Missed Tackle | Metre Made |\n");
			printf(" ---------------------------------------------------------------------------------------------------------------------------------");
			printf("\n|%5d  %11s  %11s  %4d  %7d  %7d  %11s   %15s  %11s %12d %14d  |\n", temp->pIrfu, temp->firstName, temp->secondName, temp->age,
				temp->height, temp->weight, temp->club, temp->email, temp->plyPosit, temp->missedTackle, temp->madeMetre);

			printf("\nPlease enter number what you would like to update or -1 to cancel\n");
			puts("\n 1) First name\n");
			puts(" 2) Second name\n");
			puts(" 3) Age\n");
			puts(" 4) Height\n");
			puts(" 5) Weight\n");
			puts(" 6) Club\n");
			puts(" 7) Email Addr \n");
			puts(" 8) Position\n");
			puts(" 9) Missed Tackle\n");
			puts(" 10) Metre Made");
			scanf("%d", &choice);

			while (choice!=- 1) {

				switch (choice){

				case 1:
					puts(" Please enter a new first name\n");
					scanf("%s", fname);

					strcpy(temp->firstName,fname);

						break;
				case 2:
					puts(" Please enter a new second name\n");
					scanf("%s", sname);

					strcpy(temp->secondName, sname);

					break;
				case 3:
					puts(" Please enter a new age\n");
					scanf("%s", sname);

					age = atoi(sname);
					
					while(age<=0){

						puts("\nInvalid input...\n");

						puts(" Please enter a new age\n");
						scanf("%s", sname);

						age = atoi(sname);
					}

					temp->age = age;

					break;
				case 4:
					puts(" Please enter a new height\n");
					scanf("%s", sname);

					height = atoi(sname);

					while (height <= 0) {

						puts("\nInvalid input...\n");

						puts(" Please enter a new height\n");
						scanf("%s", sname);

						height = atoi(sname);
					}

					temp->height = height;

					break;
				case 5:
					puts(" Please enter a new weight\n");
					scanf("%s", sname);

					weight = atoi(sname);

					while (weight <= 0) {

						puts("\nInvalid input...\n");

						puts(" Please enter a new weight\n");
						scanf("%s", sname);

						weight = atoi(sname);
					}

					temp->weight = weight;

					break;
				case 6:
					puts(" Please enter a new club name\n");
					scanf("%s", club);

					strcpy(temp->club, club);

					break;
				case 7:
					puts(" Please enter a new email addr\n");
					scanf("%s", email);
					strcpy(email1, email);

					while (!checkEmail(email)) {

						puts("\nPlease enter a new email addr\n");
						scanf("%s", email);
						strcpy(email1, email);
					}

					strcpy(temp->email, email1);
		
					break;
				case 8:
					puts(" Please enter a new position\n");
					scanf("%s", position);

					strcpy(temp->plyPosit, position);
					break;
				case 9:

					puts(" Please enter a new missed tackles\n");
					scanf("%s", sname);

					missed = atoi(sname);

					while (missed < 0) {

						puts("\nInvalid input...\n");

						puts(" Please enter a new missed tackles\n");
						scanf("%s", sname);

						missed = atoi(sname);
					}

					temp->missedTackle = missed;

					break;
				case 10:

					puts(" Please enter a new metres made\n");
					scanf("%s", sname);

					metre = atoi(sname);

					while (metre <0) {

						puts("\nInvalid input...\n");

						puts(" Please enter a new metres made\n");
						scanf("%s", sname);

						metre = atoi(sname);
					}

					temp->madeMetre = metre;

					break;


				default:
					puts("\nInvalid input....\n");

					break;
				}

				printf("\nPlease enter number what you would like to update or -1 to cancel\n");
				puts("\n 1) First name\n");
				puts(" 2) Second name\n");
				puts(" 3) Age\n");
				puts(" 4) Height\n");
				puts(" 5) Weight\n");
				puts(" 6) Club\n");
				puts(" 7) Email Addr \n");
				puts(" 8) Position\n");
				puts(" 9) Missed Tackle\n");
				puts(" 10) Metre Made");
				scanf("%d", &choice);
			}

			found = 1;
		}

		temp = temp->next;

	}

	if (!found) {

		puts("\nSorry no such player in database...\n");
	}
}

void deletePlayerAtPosition(struct Players *top, int pos){

	int i;
	struct Players *temp;
	struct Players *prev;

	temp = top;

	// loop until the position required by the user
	for (i = 0; i<pos - 1; i++) {

		prev = temp;
		temp = temp->next;

	}

	prev->next = temp->next;//temp deleted

	free(temp);//temp memory deallocated

}
void sortReverse(struct Players *top) {//reverse sorting by irfu number

	//declare local variables
	struct Players* temp;
	struct Players* temp1;
	char fname[25];
	char sname[25];
	int irfu, age, height, weight;
	int missed;
	int metre;
	char club[25];
	char email[25];
	char position[25];

	temp = top;

	//looping thru the link list and comparing two neibouring nodes
	for (; temp->next != NULL; temp = temp->next) {

		for (temp1 = temp->next; temp1 != NULL; temp1 = temp1->next) {

			if (temp->pIrfu > temp1->pIrfu) {//comparing by irfu numbers and copying into temp variable and swaping values

				irfu = temp->pIrfu;
				height = temp->height;
				strcpy(fname, temp->firstName);
				strcpy(sname, temp->secondName);
				strcpy(club, temp->club);
				strcpy(email, temp->email);
				strcpy(position, temp->plyPosit);
				age = temp->age;
				weight = temp->weight;
				missed = temp->missedTackle;
				metre = temp->madeMetre;

				temp->height = temp1->height;
				temp->pIrfu = temp1->pIrfu;
				strcpy(temp->firstName, temp1->firstName);
				strcpy(temp->secondName, temp1->secondName);
				strcpy(temp->club, temp1->club);
				strcpy(temp->email, temp1->email);
				strcpy(temp->plyPosit, temp1->plyPosit);
				temp->age = temp1->age;
				temp->weight = temp1->weight;
				temp->missedTackle = temp1->missedTackle;
				temp->madeMetre = temp1->madeMetre;

				temp1->height = height;
				temp1->pIrfu = irfu;
				strcpy(temp1->firstName, fname);
				strcpy(temp1->secondName, sname);
				strcpy(temp1->club, club);
				strcpy(temp1->email, email);
				strcpy(temp1->plyPosit, position);
				temp1->age = age;
				temp1->weight = weight;
				temp1->missedTackle = missed;
				temp1->madeMetre = metre;

			}
		}
	}

}
void sort(struct Players *top) {//the same sort method as reverse just comparison based on height

	struct Players* temp;
	struct Players* temp1;
	char fname[25];
	char sname[25];
	int irfu,age, height, weight;
	int missed;
	int metre;
	char club[25];
	char email[25];
	char position[25];

	temp = top;

	for (; temp->next != NULL; temp = temp->next){

		for (temp1 = temp->next; temp1 != NULL; temp1 = temp1->next){

			if (temp->height > temp1->height){

				irfu = temp->pIrfu;
				height = temp->height;
				strcpy(fname, temp->firstName);
				strcpy(sname, temp->secondName);
				strcpy(club, temp->club);
				strcpy(email, temp->email);
				strcpy(position, temp->plyPosit);
				age = temp->age;
				weight = temp->weight;
				missed = temp->missedTackle;
				metre = temp->madeMetre;

				temp->height = temp1->height;
				temp->pIrfu = temp1->pIrfu;
				strcpy(temp->firstName, temp1->firstName);
				strcpy(temp->secondName, temp1->secondName);
				strcpy( temp->club, temp1->club);
				strcpy(temp->email, temp1->email);
				strcpy( temp->plyPosit, temp1->plyPosit);
				temp->age = temp1->age;
				temp->weight = temp1->weight;
				temp->missedTackle = temp1->missedTackle;
				temp->madeMetre = temp1->madeMetre;

				temp1->height = height;
				temp1->pIrfu = irfu;
				strcpy(temp1->firstName,fname);
				strcpy(temp1->secondName,sname);
				strcpy(temp1->club,club);
				strcpy(temp1->email,email);
				strcpy(temp1->plyPosit,position);
				temp1->age = age;
				temp1->weight = weight;
				temp1->missedTackle = missed;
				temp1->madeMetre = metre;

			}
		}
	}
}

void deletePlayerAtEnd(struct Players *top) {

	struct Players *temp;
	struct Players *prev;

	temp = top;

	while (temp->next != NULL) {//go to the last node

		prev = temp;//one before last
		temp = temp->next;//the last node
	}

	prev->next = NULL;//the last node is gone
	free(temp);//free the memory
}

void printToReportFile(struct Players *top) {

	//declare local variables
	struct Players *temp;
	FILE * ptrFile;
	int noMissed = 0, missedLess3 = 0, missedLess5 = 0, missedMore5 = 0;
	int noMade = 0, madeLess10 = 0, madeLess20 = 0, madeMore20 = 0;

	temp = top;
	ptrFile = fopen("./report.txt", "w");//open a file to write a report

	if (ptrFile == NULL) {

		puts("\nSorry can not open file...\n");
	}
	else {

		if (top == NULL) {//not able to open the file

			fprintf(ptrFile,"\nSorry no players to show...\n");
		}
		else {

			puts("\nPrinting a report to a file...\n");

			fprintf(ptrFile," ---------------------------------------------------------------------------------------------------------------------------------");
			fprintf(ptrFile,"\n|IRFU | First name | Second name | Age | Height | Weight |    Club    |     Email Addr   |  Position | Missed Tackle | Metre Made |\n");
			fprintf(ptrFile," ---------------------------------------------------------------------------------------------------------------------------------");
		}

		while (temp != NULL) {//go thru all nodes

			//print into the file
			fprintf(ptrFile,"\n|%5d  %11s  %11s  %4d  %7d  %7d  %11s   %15s  %11s %12d %14d  |\n", temp->pIrfu, temp->firstName, temp->secondName, temp->age,
				temp->height, temp->weight, temp->club, temp->email, temp->plyPosit, temp->missedTackle, temp->madeMetre);

			if (temp->missedTackle == 0) {

				noMissed++;
			}

			if (temp->missedTackle >0 && temp->missedTackle < 3) {

				missedLess3++;

			}
			if (temp->missedTackle >0 && temp->missedTackle<5) {

				missedLess5++;
			}
			if (temp->missedTackle >= 5) {

				missedMore5++;

			}

			if (temp->madeMetre == 0) {

				noMade++;
			}
			if (temp->madeMetre>0 && temp->madeMetre < 10) {

				madeLess10++;
			}
			if (temp->madeMetre>0 && temp->madeMetre < 20) {

				madeLess20++;
			}
			if (temp->madeMetre >= 20) {

				madeMore20++;
			}

			temp = temp->next;

		}//end while loop

		//print into the file
		fprintf(ptrFile,"\n %d of players who miss no tackles\n", noMissed);
		fprintf(ptrFile," %d of players who miss less than 3 tackles per match\n", missedLess3);
		fprintf(ptrFile," %d of players who miss less than 5 tackles per match\n", missedLess5);
		fprintf(ptrFile," %d of players who miss more than 5 tackles per match\n", missedMore5);
		fprintf(ptrFile," %d of players who make no metres in a game\n", noMade);
		fprintf(ptrFile," %d of players who make less than 10 metres in a game\n", madeLess10);
		fprintf(ptrFile," %d of players who make less than 20 metres in a game\n", madeLess20);
		fprintf(ptrFile," %d of players who make more than 20 metres in a game\n", madeMore20);

		puts("\nDone...\n");

		fclose(ptrFile);//close file

		}
	}



void printToDetailFile(struct Players *top) {//print into a file all player's details

	struct Players *temp;
	FILE * ptrFile,*ptrSize;
	int j = 0;

	ptrFile = fopen("./Rugby.txt", "w");//open the files
	ptrSize = fopen("./size.txt", "w");

	temp = top;

	if (temp == NULL) {

		puts("\nSorry no data to print...\n");

		fclose(ptrFile);
		fclose(ptrSize);

		exit(0);
	}
	else {

		puts("\nPrinting details to file...\n");
	}

	if (ptrFile == NULL || ptrSize == NULL) {

		puts("\nSorry can not open a file...\n");
	}
	else {

		fprintf(ptrSize, "%d",size(top));

		while (temp != NULL) {

			//print out into the files
			fprintf(ptrFile, "%d %s %s %d %d %d %s %s %s %d %d\n", temp->pIrfu, temp->firstName, temp->secondName, temp->age, temp->height, 
												temp->weight,temp->club,temp->email, temp->plyPosit, temp->missedTackle, temp->madeMetre);	
		
			temp = temp->next;

		}
	}
	
	printf("Done...\n");

	if (ptrFile != NULL) {

		fclose(ptrFile);
	}

	if (ptrSize != NULL) {

		fclose(ptrSize);
	}
}