#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void View (int idnum, char itemname [1000], int cost, int quantity);
void titleSection (char string[100]); //Function for TitleScreen printing
void space (void); //Function for spacing
int AdminMenu (void); //Function for Admin Main Menu
int UserMenu (void); //Function for User Main Menu
int loginAdmin (void); // Function for Login-System (admin)
int CreateAnAccount (void); //Function for creating account
void readFILE (void);
int prompting (void);
int AddStocks (void);
int DeleteStocks (void);
int checkout (void);
char* PasswordMasking (int md); //Function for Password Masking

int idNum [1000];
int quantity [1000];
int cost [1000];
int i = 0;
int j = 0;
int prompt;
int costcpy[1000];
int quantcpy [1000];
int idcpy [1000];
char itemName [1000][100];
char PassCon[1000];
char itemcpy [1000][1000];
char username [26], password[26], repassword[26], first_name[26], last_name[26], favorite_food[26], favorite_pet[26], age[5], prompt2[5], verify [2][26];
char check [10000][50];

int main (void) {
	
	do {
	system ("cls");
	space ();
	titleSection ("Welcome To Our Inventory"); //invoked title screen printing
	space ();
	printf ("\n%72s", "Press 1: Login as Admin\n");  //First prompting, Login as Admin ? Login as User? Create an Account? Exit program?  
	printf ("\n%71s", "Press 2: Login as User\n");
	printf ("\n%75s", "Press 3: Create an Account\n");
	printf ("\n%70s", "Press 4: Exit Program\n");
	space ();
	printf ("\n%64s","Enter choice: ");
	fgets (prompt2, 5, stdin); //prompt (a char type array) used to store the first prompting variable value. 
	
	i = atoi (prompt2); //prompt variable of string type converted to int type. (atoi - alphabet to integer/ascii to integer)
	
	switch (i) { /*switch (i), if the value of i is "1" then proceed to login as admin function w/ parameter of 1, if "2", proceed to login as user function with parameter of 2.
											else if the value of i is "3", proceed to create account function, else exit the program.*/
		case 1: login (1);
					break;
		case 2: login (2);
					break;
		case 3: CreateAnAccount();
					break;
		case 4: return 0;
		
		default: printf ("\t\t\t Invalid Input!"); //if the value of i is not equal to any value in the switch then it is invalid.
		}
	} while (1);			
} 

int login (int menuType) { //LOGIN AS ADMIN OR USER FUNCTION - the type of login (admin or user) depends on the value of parameter.
	
	do {
	system ("cls");
	space ();
		if (menuType==1) //if the value of the parameter (menuType) is equal to 1, then it's title section is "Log in as Admin".
			titleSection ("    Login As Admin     ");
		else 
			titleSection ("    Login As User"); //else it is "Log in as User".
	space ();
	
	printf ("\n%60s", "Enter Username: "); //prompt for username 
		scanf ("%s", username); //username string type variable is used to store the string value from the user input.
		
	printf ("\n%60s", "Enter Password: ");
		strcpy (password, PasswordMasking(0)); /* prompt for password, the PasswordMasking () function is invoked, and it will return a string value of the inputted password of the user
															and it will be copied to password variable */
	FILE*fptr;																								
	if ((fptr = fopen ("USER.txt", "r"))==NULL) { //the "USER.txt" was opened, and it contains the username and password of the user/admin.
		printf ("\n\t\t\tError. Admin records cannot find. Problem with the File"); //if the file "USER.txt" does not exist then the program terminates and returned a value of 1.
		return 1;
	}
		while (!feof(fptr)) { /* Loop for finding the username of the user in the file and compares it with the inputted string value of the user for its username. (This loop will run
																	until it reaches the end of the file !(feof (fptr)) */
			i=0;
				fscanf (fptr, "%s", check[i]); //scans the file and every string value will store to the check array
					if ((strcmp (username, check[i]))==0) { /*if the program finds the identical string value of the inputted username of the user in the file containing it's username and 
																							password, then do the code in the if block (strcmp - string compare)*/
						strcpy (verify[0], check[i]); // copy the string value of the check array (username inputted) to the verify multi-dim array verify[0].
						i++; //increment the value of i to store the next element of the check array the password of the user located at the file
						fscanf (fptr, "%s", check[i]); //get the password of the user from the file
						strcpy (verify[1], check[i]); //copy it to verify[1]
						break; //exit loop
					}
			i++;	
		}
	fclose (fptr); //close the file
	
	if (menuType==1) {
		
		strcpy (verify[0], "admin");
		strcpy (verify[1], "fortunamajor");
	}
	
	system ("cls");
	
	if (strcmp (username, verify[0])==0) /* an if else statement for verification - if the username string value is equal to verify[0] (contains the username of the user in the file).
																then do its if block codes */
		if (strcmp (password, verify[1])==0) { /* if the password inputted is equal to the password of the user in the file then allow the user/admin to login*/
			if (menuType==1){ // if the parameter of the function is equal to 1, proceed to AdminMenu () function.
				AdminMenu ();
				return 1;
			}	
			else { //else proceed to UserMenu () function.
				UserMenu();
				return 1;
			}
		}
							
	space ();
	printf ("\n%75s", "WRONG USERNAME OR PASSWORD!"); /*if the username and password did not matched with the username and password located at file, repeat the process of inputting
																			username and password*/
	space ();
	printf ("\n%69s", "Press 1: Login Again\n"); //prompt for user, admin whether it would like to login again or back to main menu
	printf ("\n%74s", "Press 2: Back to Main Menu");
	space ();
	printf ("\n%64s", "Enter choice: ");
	scanf ("%d", &i); 
	
		if (i==2)
			return 1;
			
	}while (1);
}

int CreateAnAccount (void) { //CREATE AN ACCOUNT FUNCTION
	
	do { 
	
	system ("cls");
	space ();
	titleSection ("   Create An Account"); //title printing
	printf ("\n\t\t(Note: All the infos you are going to enter below can be use to recover your account.)");
	space ();
	
	printf ("\n%65s", "Enter your First Name: "); //get the first name of the user
		fgets (first_name, 26, stdin);
	
	printf ("\n%66s", "Enter your Family Name: "); //" " the last name
		fgets (last_name, 26, stdin);
	
	printf ("\n%58s","Enter your Age: "); // " " the age 
		fgets (age, 5, stdin);
	
	printf ("\n%68s", "Enter your Favorite Food: "); // " " favorite food 
		fgets (favorite_food, 26, stdin);
	
	printf ("\n%67s", "Enter your Favorite Pet: "); // " " favorite pet
		fgets (favorite_pet, 26, stdin);
	
		while (1) { //Loop for the decision whether the user wants to proceed to the next section of the program (registering his/her account username/password)
			printf ("\n\n%76s","Proceed now to next section? ");
			printf ("\n\n%56s", "Press 1: Yes");
			printf ("\n\n%76s", "Press 2: No (Enter infos again.)");
			printf ("\n\n%65s", "Enter choice: ");
			fgets (prompt2, 5, stdin); //get the string value
		
			i = atoi (prompt2); //convert it to integer
		
			if (i==1)
				break;
			else if (i==2)
				break;
			else 
				printf ("\n\n%67s", "INVALID INPUT!"); // if i value does not equal to the value of the i defined in the if else statement then repeat the process
		}
		
	}while (i!=1); // the code above will run continuously until the value of i is equal to 1, since 1 is the value for the proceeding to the next section of creating an account
	
	do { //next section loop
		
	system ("cls"); 
	FILE *fptr = fopen ("USER.txt", "r"); //open the file "USER.txt"
	space ();
	titleSection ("   Create An Account"); //title section
	space ();
	
	printf ("%60s", "Enter Username: "); //prompt for username 
		scanf ("%s", username);
	
		while (!feof(fptr)) { //loop for verifying if the username inputted is already existed, this loop will run until it reaches the end of the file !feof(fptr)
			i=0; //set i is equal to 0
			fscanf (fptr, "%s", check[i]); //scan the file and save it to check array[i]
				if ((strcmp (username, check[i]))==0) { //check if the string value got by the check array is equal to the username inputted by the user then the username is already exist
					printf ("\n\n%73s","USERNAME ALREADY EXIST!");
					printf ("\n\n%75s", "Press any key to try again ");
					getch (); //get character before it proceeds again
					break;	//exit from the loop and repeat the process of getting the username from the user
				}
			i++; //increments the value of i to save the next string from the file to check array
		}
	fclose (fptr); //close the file
	
	} while ((strcmp (username, check[i]))==0); /* the whole loop for getting the username will run until the username inputted of the user is not equal to any already existed username in the
														the file */
	
	do {	
	printf ("\n%60s", "Enter Password: "); //prompt for password
	strcpy (password, PasswordMasking(0));  /* prompt for password, the PasswordMasking () function is invoked, and it will return a string value of the inputted password of the user
												 			and it will be copied to password variable */
	printf ("\n\n%61s", "Retype Password: ");//prompt to retype the password 
	strcpy (repassword, PasswordMasking(0)); /* prompt for password, the PasswordMasking () function is invoked, and it will return a string value of the inputted password of the user
												 			and it will be copied to password variable */
		if ((strcmp(password, repassword))!=0){ //compare each string of password, if they are not equal then, do the if-block
			printf ("\n\n%73s", "PASSWORD NOT MATCHED!");
			printf ("\n\n%75s\n", "Press any key to try again ");
			getch();//take character before proceeding
		}		
	} while ((strcmp(password, repassword))!=0); //the whole process of verifying the password will run until the password and retyped password is equal
	
	FILE *fptr = fopen ("USER.txt", "a"); //open file (this section include saving the infos of the user into the defined file-USER.txt)
		fprintf (fptr, "\n%s", username); //each fprintf will print its argument to the defined file
		fprintf (fptr, "\n%s", password);
		fprintf (fptr, "\n%s", first_name);
		fprintf (fptr,  last_name);
		fprintf (fptr, age);
		fprintf (fptr, favorite_food);
		fprintf (fptr, favorite_pet);
	fclose (fptr);
	
	printf ("\n\n%80s", "You've Created An Account Successfully !"); //the account is succcessfully created
	printf ("\n\n%73s", "Press any key to Login "); //get character 
	getch (); //back to main menu
	
	return 0;
}
	
int AdminMenu (void) { //ADMIN MENU FUNCTION
	
	system ("cls");
	space ();
	printf ("\n%68s","Login Successful.");
	printf ("\n\n%73s", "Press any key to continue. ");
	getch ();
	
	while (1) {
		
	system ("cls");
	
	readFILE ();
		
	space ();
	printf ("\n%70s", "Press 1: Add Stocks\n");
	printf ("\n%71s", "Press 2: Edit Stocks\n");
	printf ("\n%73s", "Press 3: Delete Stocks\n");
	printf ("\n%77s", "Press 4: Back to Main Menu\n");
	printf ("\n%64s", "Enter choice: ");
	
	prompt = prompting ();
	
	if (prompt==1)
		AddStocks ();
	else if (prompt==2)
		EditStocks ();
	else if (prompt==3)
		DeleteStocks ();
	else 
		return 1;
	}
	
	return 0;
}
int AddStocks (void){ //FUNCTION FOR ADDING STOCKS
	
	system ("cls");
	
	char ItemName[1000];
	int quanti;
	int c0st;
	int storeid;
	
	space ();
	printf ("\n%64s", "Enter Item Name: ");
	strcpy (ItemName, PasswordMasking(1));
	
	printf ("\n\n%59s", "Enter cost: ");
	scanf ("%d", &c0st);
	
	printf ("\n%63s", "Enter quantity: ");
	scanf ("%d", &quanti);
	
	FILE *fptr = fopen ("inventory.txt", "r");
	
	i = 0;
	
	while (!feof(fptr)) {
		
		fscanf (fptr, "%d", &idNum[i]);
		fscanf (fptr, "%s", itemName[i]);
		fscanf (fptr, "%d", &cost[i]);
		fscanf (fptr, "%d", &quantity[i]);
		storeid = idNum[i];
		++i;
	}
	fclose (fptr);
	
	FILE *fqtr = fopen ("inventory.txt", "a");
	
	fprintf (fqtr, "\n%d", ++storeid);
	fprintf (fqtr, "\n%s", ItemName);
	fprintf (fqtr, "\n%d", c0st);
	fprintf (fqtr, "\n%d", quanti);
		
	fclose (fqtr);
	
	printf ("\n\n\t\t\t\t\tItem with id no. %d was successfuly added.", storeid);
	printf ("\n\n\t\t\t\t\t\tPress any key to continue ");
	
	getch ();
	
	return 0;
}
int EditStocks (void) { //FUNCTION FOR EDITING STOCKS
		
	char ItemName[1000];
	int quanti;
	int c0st;
	
	system ("cls");
	readFILE ();
	
	int idnumb;
	
	do {
	space ();
	
	i = 0;
	
	FILE*fptr = fopen ("inventory.txt", "r");
	
	printf ("\n\n%88s", "Enter the Id number of the item you want to edit: " );
	scanf ("%d", &idnumb);

	while (!feof(fptr)) {
		
		fscanf (fptr, "%d", &idNum[i]);
		fscanf (fptr, "%s", itemName[i]);
		fscanf (fptr, "%d", &cost[i]);
		fscanf (fptr, "%d", &quantity[i]);
		
		if (idNum[i] == idnumb)
			break;
			
		++i;
	}
	fclose (fptr);
	
	if (idNum[i] != idnumb) {
		
		space ();
		printf ("%75s\n", "Id Number does not exist!" );
		printf ("\n%75s\n", "Press any key to try again " );	
		getch ();	
	}
	
	} while (idNum[i] != idnumb);
	
	system ("cls");
	printf ("\n\n%18s %30s %29s %31s", "ID Number", "Item Name", " Cost", "Quantity\n");
	printf ("\t==========================================================================================================");
	View (idNum[i], itemName[i], cost[i], quantity[i]);
	printf ("\n\n%73s", "Press 1: Edit Item Name\n");
	printf ("\n%68s", "Press 2: Edit Cost\n");
	printf ("\n%72s", "Press 3: Edit Quantity\n");
	printf ("\n\n%65s", "Enter choice: ");
	
	int strid = idNum[i];
	prompt = prompting ();
	
	if (prompt == 1) {
		
		printf ("\n\n%64s", "Enter Item Name: ");
		strcpy (ItemName, PasswordMasking(1));

		i = 0;
		j = 0;
	
		FILE*fqtr = fopen ("inventory.txt", "r");
	
		while (!feof(fqtr)) {
		
			fscanf (fqtr, "%d", &idNum[i]);
			fscanf (fqtr, "%s", itemName[i]);
			fscanf (fqtr, "%d", &cost[i]);
			fscanf (fqtr, "%d", &quantity[i]);
	
			if (idNum[i]==strid) 
				strcpy (itemName[i], ItemName);
			
			idcpy[j] = idNum[i];
			strcpy (itemcpy[j], itemName[i]);
			costcpy[j] = cost[i];
			quantcpy[j] = quantity[i];	
			++j;
			++i;	
		}	
		fclose (fqtr);
	
		system ("cls");
	
		FILE*fztr = fopen ("inventory.txt", "w");
		
		for (j=0; j<i; j++) {
		
			fprintf (fztr, "\n%d", idcpy[j]);
			fprintf (fztr, "\n%s", itemcpy[j]);
			fprintf (fztr, "\n%d", costcpy[j]);
			fprintf (fztr, "\n%d", quantcpy[j]);
		}
	
	fclose (fztr);
		
	}
	
	if (prompt==2) {
		
		printf ("\n\n%59s", "Enter cost: ");
		scanf ("%d", &c0st);
	
		i = 0;
		j = 0;
	
		FILE*fqtr = fopen ("inventory.txt", "r");
	
		while (!feof(fqtr)) {
		
			fscanf (fqtr, "%d", &idNum[i]);
			fscanf (fqtr, "%s", itemName[i]);
			fscanf (fqtr, "%d", &cost[i]);
			fscanf (fqtr, "%d", &quantity[i]);
	
			if (idNum[i]==strid) 
				cost[i]=c0st;
			
			idcpy[j] = idNum[i];
			strcpy (itemcpy[j], itemName[i]);
			costcpy[j] = cost[i];
			quantcpy[j] = quantity[i];	
			++j;
			++i;	
		}	
		fclose (fqtr);
	
		system ("cls");
	
		FILE*fztr = fopen ("inventory.txt", "w");
		
		for (j=0; j<i; j++) {
		
			fprintf (fztr, "\n%d", idcpy[j]);
			fprintf (fztr, "\n%s", itemcpy[j]);
			fprintf (fztr, "\n%d", costcpy[j]);
			fprintf (fztr, "\n%d", quantcpy[j]);
		}
	
	fclose (fztr);
			
	}
	
	if (prompt==3) {
		
		printf ("\n%63s", "Enter quantity: ");
		scanf ("%d", &quanti);  
		
		i = 0;
		j = 0;
	
		FILE*fqtr = fopen ("inventory.txt", "r");
	
		while (!feof(fqtr)) {
		
			fscanf (fqtr, "%d", &idNum[i]);
			fscanf (fqtr, "%s", itemName[i]);
			fscanf (fqtr, "%d", &cost[i]);
			fscanf (fqtr, "%d", &quantity[i]);
	
			if (idNum[i]==strid) 
				quantity[i] = quanti;
			
			idcpy[j] = idNum[i];
			strcpy (itemcpy[j], itemName[i]);
			costcpy[j] = cost[i];
			quantcpy[j] = quantity[i];	
			++j;
			++i;	
		}	
		fclose (fqtr);
	
		system ("cls");
	
		FILE*fztr = fopen ("inventory.txt", "w");
		
		for (j=0; j<i; j++) {
		
			fprintf (fztr, "\n%d", idcpy[j]);
			fprintf (fztr, "\n%s", itemcpy[j]);
			fprintf (fztr, "\n%d", costcpy[j]);
			fprintf (fztr, "\n%d", quantcpy[j]);
		}
	
	fclose (fztr);
	
	}
	 
	return 0;
}
int DeleteStocks (void) { //FUNCTION FOR DELETING STOCKS
	
	system ("cls");
	readFILE ();
	
	int idnumb;
	
	do {
	space ();
	
	i = 0;
	
	FILE*fptr = fopen ("inventory.txt", "r");
	
	printf ("%88s", "Enter the Id number of the item you want to delete: " );
	scanf ("%d", &idnumb);

	while (!feof(fptr)) {
		
		fscanf (fptr, "%d", &idNum[i]);
		fscanf (fptr, "%s", itemName[i]);
		fscanf (fptr, "%d", &cost[i]);
		fscanf (fptr, "%d", &quantity[i]);
		
		if (idNum[i] == idnumb)
			break;
			
		++i;
	}
	fclose (fptr);
	
	if (idNum[i] != idnumb) {
		
		space ();
		printf ("%75s\n", "Id Number does not exist!" );
		printf ("\n%75s\n", "Press any key to try again " );	
		getch ();	
	}
	
	} while (idNum[i] != idnumb);

	system ("cls");
	printf ("\n\n%18s %30s %29s %31s", "ID Number", "Item Name", " Cost", "Quantity\n");
	printf ("\t==========================================================================================================");
	View (idNum[i], itemName[i], cost[i], quantity[i]);
	printf ("\n\n\n%85s\n", "Are you sure you want to delete the item above?" );
	printf ("\n\n%68s", "Press 1: Yes\n");
	printf ("\n%67s", "Press 2: No\n");
	printf ("\n\n%64s", "Enter choice: ");
	
	prompt = prompting ();
	
	if (prompt == 2)
		return 1;
		
	int strid = idNum[i];
	int idcpy [1000];
	char itemcpy [1000][1000];
	int costcpy[1000];
	int quantcpy [1000];
	
	i = 0;
	j = 0;
	
	FILE*fqtr = fopen ("inventory.txt", "r");
	
	while (!feof(fqtr)) {
		
		fscanf (fqtr, "%d", &idNum[i]);
		fscanf (fqtr, "%s", itemName[i]);
		fscanf (fqtr, "%d", &cost[i]);
		fscanf (fqtr, "%d", &quantity[i]);
	
		if (idNum[i]==strid) {
			i++;
			continue;
		}
		
		idcpy[j] = idNum[i];
		strcpy (itemcpy[j], itemName[i]);
		costcpy[j] = cost[i];
		quantcpy[j] = quantity[i];	
		++j;
		++i;	
	}	
	fclose (fqtr);
	
	system ("cls");
	
	FILE*fztr = fopen ("inventory.txt", "w");
	
	i--;
	
	for (j=0; j<i; j++) {
		
		fprintf (fztr, "\n%d", idcpy[j]);
		fprintf (fztr, "\n%s", itemcpy[j]);
		fprintf (fztr, "\n%d", costcpy[j]);
		fprintf (fztr, "\n%d", quantcpy[j]);
	}
	
	fclose (fztr);
	
	return 0;
}
int UserMenu (void) { //FUNCTION FOR USER MENU

	system ("cls");
	space ();
	printf ("\n%68s","Login Successful.");
	printf ("\n\n%73s", "Press any key to continue. ");
	getch ();
	
	while (1) {
		
	system ("cls");
	readFILE ();
	
	space ();
	printf ("\n%78s", "Press 1: Purchase a Product\n");
	printf ("\n%77s", "Press 2: Back to Main Menu\n");
	printf ("\n%64s", "Enter choice: ");
	
	prompt = prompting ();
	
	if (prompt==2)
		return 1;
	else 
		checkout ();	
	}
	
}
int checkout (void) {
	
	system ("cls");
	readFILE ();
	
	int idnumb;
	
	do {
	space ();
	
	i = 0;
	
	FILE*fptr = fopen ("inventory.txt", "r");
	
	printf ("%88s", "Enter the Id number of the item you want to purchase: " );
	scanf ("%d", &idnumb);

	while (!feof(fptr)) {
		
		fscanf (fptr, "%d", &idNum[i]);
		fscanf (fptr, "%s", itemName[i]);
		fscanf (fptr, "%d", &cost[i]);
		fscanf (fptr, "%d", &quantity[i]);
		
		if (idNum[i] == idnumb)
			break;
			
		++i;
	}
	fclose (fptr);
	
	if (idNum[i] != idnumb) {
		
		space ();
		printf ("%75s\n", "Id Number does not exist!" );
		printf ("\n%75s\n", "Press any key to try again " );	
		getch ();	
	}
	
	} while (idNum[i] != idnumb);
	
	int itemquanti;
	int amount;
	int strid = idNum[i];
	
	system ("cls");
	printf ("\n\n%18s %30s %29s %31s", "ID Number", "Item Name", " Cost", "Quantity\n");
	printf ("\t==========================================================================================================");
	View (idNum[i], itemName[i], cost[i], quantity[i]);
	printf ("\n\n\n%73s", "Enter the quantity you want: ");
	scanf ("%d", &itemquanti);
	
	if (quantity[i] < itemquanti) {
		
		printf ("\n\n%90s\n", "I'm sorry, we don't have enough stock of this item." );
		printf ("\n%75s\n", "Press any key to continue " );
		getch ();
		return 1;
	}
	
	amount = itemquanti*cost[i];
	
	printf ("\n\n%66s", "Amount to be paid: ");
	printf ("%c%d", 'P', amount);
	
	printf ("\n\n\n%85s\n", "Are you sure you want to purchase the item above?" );
	printf ("\n\n%68s", "Press 1: Yes\n");
	printf ("\n%67s", "Press 2: No\n");
	printf ("\n\n%64s", "Enter choice: ");
	
	prompt = prompting ();
	
	if (prompt==2)
		return 1;
	
	i = 0;
	j = 0;
	
	FILE*fqtr = fopen ("inventory.txt", "r");
	
	while (!feof(fqtr)) {
		
		fscanf (fqtr, "%d", &idNum[i]);
		fscanf (fqtr, "%s", itemName[i]);
		fscanf (fqtr, "%d", &cost[i]);
		fscanf (fqtr, "%d", &quantity[i]);
	
		if (idNum[i]==strid) {
			quantity[i]-=itemquanti;
		}
		
		idcpy[j] = idNum[i];
		strcpy (itemcpy[j], itemName[i]);
		costcpy[j] = cost[i];
		quantcpy[j] = quantity[i];	
		++j;
		++i;	
	}	
	fclose (fqtr);
	
	system ("cls");
	
	FILE*fztr = fopen ("inventory.txt", "w");
	
	for (j=0; j<i; j++) {
		
		fprintf (fztr, "\n%d", idcpy[j]);
		fprintf (fztr, "\n%s", itemcpy[j]);
		fprintf (fztr, "\n%d", costcpy[j]);
		fprintf (fztr, "\n%d", quantcpy[j]);
	}
	
	fclose (fztr);
	
	printf ("\n\n%76s", "THANK YOU FOR THE PURCHASE! ");
	printf ("\n\n%75s", "Press any key to continue. ");
	getch ();
	
	return 0;
	
}
char* PasswordMasking (int md) { //FUNCTION FOR PASSWORD MASKING, return type - a char pointer/address
	
	char ch;
	
	int j = 0; 
	
		while (1) { 
		
		ch = getch (); 
		
		if (ch==13) { 
			PassCon[j] = '\0';
			break;
		}
		else if (ch==8) {
			
			if (j>0) {
				j--;
				printf ("\b \b");
			}
		}
		else if (ch==9 || ch==32) {
			
			if (md==1) {
				
				PassCon[j] = '_';
				printf ("%c", PassCon[j]); 
				j++;
			}
			else
				continue;
		}
		else { 
			if (md==1) {
				
				PassCon [j]=ch;
				printf ("%c", PassCon[j]); 
				j++;
			}
			else {
			
				PassCon[j] = ch;
				j++;
				printf ("*");
			}
		}	
	}
	
	return PassCon; 
}

int prompting (void) {
	
	int prompt;
	
		while (1) {
		
			scanf ("%d", &prompt);
		
			if (prompt==1 || prompt==2 || prompt==3 || prompt ==4)
				break;
			else {
				printf ("\n%68s", "Invalid Input!\n");
				printf ("\n%64s", "Enter choice: ");
			}		
		}
		
	return prompt;
}
void View (int idnum, char itemname [1000], int cost, int quantity) {
	
	printf ("\n\n%15d %32s %27c%d %27d", idnum, itemname, 'P', cost,  quantity);
}

void readFILE (void) {
	
		space ();
		printf ("\t\t\t\t\t    ================================");
		printf ("\n\t\t\t\t\t\t    INVENTORY STOCKS");
		printf ("\n\t\t\t\t\t    ================================\n");
		space ();
		printf ("%18s %30s %29s %31s", "ID Number", "Item Name", " Cost", "Quantity\n");
		printf ("\t==========================================================================================================");
	
		FILE*fptr = fopen ("inventory.txt", "r");
		
		i = 0;
		
		while (!feof(fptr)) {
		
			fscanf (fptr, "%d", &idNum[i]);
			fscanf (fptr, "%s", itemName[i]);
			fscanf (fptr, "%d", &cost[i]);
			fscanf (fptr, "%d", &quantity[i]);
			View (idNum[i],  itemName[i], cost[i], quantity[i]);	
			++i;
		}
		fclose (fptr);	
}
void titleSection (char string[100]) { //Title printing function
	
	space ();
	printf ("\t\t\t\t\t    ================================");
	printf ("\n\t\t\t\t\t\t %s", string);
	printf ("\n\t\t\t\t\t    ================================\n");
	
}

void space (void) { //Function for spacing
	
	for (i=0; i<4; i++);
		puts ("\n");
		
}

