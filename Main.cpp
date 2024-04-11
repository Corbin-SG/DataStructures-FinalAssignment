#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CREATE_ACCOUNT	1
#define DELETE_ACCOUNT	2
#define CHANGE_USER		3
#define CHANGE_PASSWORD	4
#define CHANGE_PROFILE	5
#define MIN_PASS_LENGTH	6
#define SEE_ACCOUNTS	6
#define SEE_HISTORY		7
#define DELETE_HISTORY	8
#define EXIT			9
#define MAX_ARRAY_SIZE	101

typedef struct Account {
	char* username;
	char* password;
	char* profilePicURL;
	struct Account* next;
}Account;

typedef struct StackNode {
	int action;
	char* username;
	char* password;
	char* profilePicUrl;
	struct Stack* next;
}StackNode;

typedef struct Stack {
	struct StackNode* top;
}Stack;

typedef struct QueueNode {
	int action;
	char* heldUser;
	char* heldPass;
	char* heldURL;
	struct Node* next;
}QueueNode;

typedef struct Queue {
	struct QueueNode* front;
	struct QueueNode* back;
}Queue;

bool isPasswordValid(char* pass);
bool correctPass(Account account, char* pass);
char* removeNewLine(char* userInput);
char* collectUserInput(void);
void createAccount(Stack* stack, Account* head);
void deleteAccount(Stack* stack, Account* head);
void changeUserName(Account* head, Stack* stack);
void changePassword(Account* head, Stack* stack);
void changeProfilePicture(Account* head, Stack* stack);
void viewAccounts(Account* head);

int main(void) {

	int exitLoop = 0;
	int userNum = 0;
	char userInput[MAX_ARRAY_SIZE] = "";
	struct Stack* stack = (Stack*)malloc(sizeof(Stack));
	if (stack == NULL) {
		printf("No memory.");
		exit(EXIT);
	}
	stack->top = NULL;
	struct Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (queue == NULL) {
		printf("No memory.");
		exit(EXIT);
	}
	queue->front = NULL;
	queue->back = NULL;
	
	struct Account* head = NULL;

	while (exitLoop != EXIT) {
		printf(" ===YOUR ACCOUNT MANAGER=== \n");
		printf("1.\t Create Account\n");
		printf("2.\t Delete Account\n");
		printf("3.\t Change an Account's Username\n");
		printf("4.\t Change an Account's Password\n");
		printf("5.\t Change an Account's Profile Picture\n");
		printf("6.\t See Accounts\n");
		printf("7.\t See History\n");
		printf("8.\t Delete History\n");
		printf("9.\t Exit Program\n");

		strcpy(userInput, collectUserInput());
		userNum = atoi(userInput);
		if (userNum < 1 || userNum > 7) {
			printf("Invalid input\n");
			continue;
		}

		switch (userNum) {
		case CREATE_ACCOUNT:
			createAccount(stack, head);
			break;
			
		case DELETE_ACCOUNT:
			deleteAccount(stack, head);
			break;

		case CHANGE_USER:
			changeUserName(head, stack);
			break;

		case CHANGE_PASSWORD:
			changePassword(head, stack);
			break;

		case CHANGE_PROFILE:
			changeProfilePicture(head, stack);
			break;
		case SEE_ACCOUNTS:
			viewAccounts(head);
		}
	}

	return 0;
}

bool isPasswordValid(char* pass) 
{
	char nums[11] = "0123456789";
	char symbols[15] = "!@#$%&*_+=-,.?";
	char upper[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char lower[27] = "abcdefghijklmnopqrstuvwxyz";

	if (strlen(pass) < MIN_PASS_LENGTH) {
		return false;
	}
	else if (strpbrk(pass, nums) == NULL) {
		return false;
	}
	else if (strpbrk(pass, symbols) == NULL) {
		return false;
	}
	else if (strpbrk(pass, upper) == NULL) {
		return false;
	}
	else if (strpbrk(pass, lower) == NULL) {
		return false;
	}
	else {
		return true;
	}
}

bool correctPass(Account account, char* pass) 
{
	if (strcmp(account.password, pass) == 0) {
		return true;
	}
	else {
		return false;
	}
}

char* removeNewLine(char* userInput)
{
	size_t stringLength = strlen(userInput);
	unsigned int possibleNewline = stringLength - 1;
	if (userInput[possibleNewline] == '\n')
	{
		userInput[possibleNewline] = '\0';
	}
	return userInput;
}

char* collectUserInput(void)
{
	char userInput[MAX_ARRAY_SIZE] = "";
	fgets(userInput, MAX_ARRAY_SIZE, stdin);
	strcpy(userInput, removeNewLine(userInput));
	return userInput;
}

void createAccount(Stack* stack, Account* head) 
{
	int exit = 0;
	char userName[MAX_ARRAY_SIZE] = "";
	char pass[MAX_ARRAY_SIZE] = "";
	char profileURL[MAX_ARRAY_SIZE] = "";

	while (exit == 0) {
		printf("Enter a Username: ");
		strcpy(userName, collectUserInput());
		//Search linked list for existing account w username
		printf("Password must be at least 6 characters in length and contain: Number, Symbol (!@#$%&*_+=-,.?\n");
		printf("Enter a Password: ");
		strcpy(pass, collectUserInput());
		if (isPasswordValid(pass) == false) {
			printf("Password does not meet requirements.\n");
			continue;
		}
		printf("Enter a PFP URL: ");
		strcpy(profileURL, collectUserInput());
		exit = EXIT;
	}
	//Add node to linked list
	//Push action to stack
}

void deleteAccount(Stack* stack, Account* head) 
{

	char userName[MAX_ARRAY_SIZE] = "";
	char pass[MAX_ARRAY_SIZE] = "";
	int exit = 0;

	//Check if linked list is empty
	while (exit == 0) {
		printf("Enter the Username of the Account to be Deleted: ");
		strcpy(userName, collectUserInput());
		//Search linked list for account if not found, inform user and "continue;"
		printf("Enter Account's Password: ");
		strcpy(pass, collectUserInput());
		if (correctPass(*head, pass) == false) {
			printf("Incorrect Password.\n");
			continue;
		}
		exit = EXIT;
	}

	//Delete Node
	//Push action to stack
}

void changeUserName(Account* head, Stack* stack) 
{

	char userName[MAX_ARRAY_SIZE] = "";
	char pass[MAX_ARRAY_SIZE] = "";
	int exit = 0;

	while (exit == 0) {
		printf("Enter Username of Account to be Edited: ");
		strcpy(userName, collectUserInput());
		//Search linked list for account, if not found, inform user and "continue;"
		printf("Enter Account's Password: ");
		strcpy(pass, collectUserInput());
		if (correctPass(*head, pass) == false) {
			printf("Incorrect Password.\n");
			continue;
		}
		exit = EXIT;
	}

	printf("Enter new Username: ");
	strcpy(userName, collectUserInput());
	head->username = userName;
	//Add action to stack
}

void changePassword(Account* head, Stack* stack) 
{
	char userName[MAX_ARRAY_SIZE] = "";
	char pass[MAX_ARRAY_SIZE] = "";
	int exit = 0;

	while (exit == 0) {
		printf("Enter Username of Account to be Edited: ");
		strcpy(userName, collectUserInput());
		//Search linked list for account, if not found, inform user and "continue;"
		printf("Enter Account's Current Password: ");
		strcpy(pass, collectUserInput());
		if (correctPass(*head, pass) == false) {
			printf("Incorrect Password.\n");
			continue;
		}
		exit = EXIT;
	}

	printf("Enter new Password: ");
	strcpy(pass, collectUserInput());
	head->password = pass;
	//Add action to stack
}

void changeProfilePicture(Account* head, Stack* stack)
{
	char userName[MAX_ARRAY_SIZE] = "";
	char pass[MAX_ARRAY_SIZE] = "";
	char profilePicture[MAX_ARRAY_SIZE] = "";
	int exit = 0;

	while (exit == 0) {
		printf("Enter Username of Account to be Edited: ");
		strcpy(userName, collectUserInput());
		//Search linked list for account, if not found, inform user and "continue;"
		printf("Enter Account's Current Password: ");
		strcpy(pass, collectUserInput());
		if (correctPass(*head, pass) == false) {
			printf("Incorrect Password.\n");
			continue;
		}
		exit = EXIT;
	}

	printf("Enter new Profile Picture URL: ");
	strcpy(pass, collectUserInput());
	head->profilePicURL = profilePicture;
	//Add action to stack
}

void viewAccounts(Account* head) 
{
	struct Account* current = head;
	while (current != NULL) {
		printf("===ACCOUNT===\n");
		printf("Username: %s\n", current->username);
		printf("Password: %s\n", current->password);
		printf("PFP:      %s\n", current->profilePicURL);
		printf("=============\n");

		current = current->next;
	}
}