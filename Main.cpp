#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CREATE_ACCOUNT	1
#define MOVE_BACK		1
#define DELETE_ACCOUNT	2
#define MOVE_FORWARD	2
#define CHANGE_USER		3
#define UNDO			3
#define CHANGE_PASSWORD	4
#define DELETE_FROM_HIS	4
#define CHANGE_PROFILE	5
#define TO_MENU			5
#define MIN_PASS_LENGTH	6
#define SEE_ACCOUNTS	6
#define SEE_HISTORY		7
#define DELETE_HISTORY	8
#define EXIT			9
#define MAX_ARRAY_SIZE	101
#define MAX_QUEUE_SIZE	15

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
	char* heldValue;
	struct StackNode* next;
}StackNode;

typedef struct Stack {
	struct StackNode* top;
}Stack;

typedef struct QueueNode {
	int action;
	char* username;
	char* password;
	char* profilePicURl;
	char* heldValue;
	struct QueueNode* next;
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
void viewHistory(Account* head, Stack* stack, Queue* queue);
void deleteHistory(Stack* stack);

//Queue
Queue* InitializeQueue(void);
bool IsQueueEmpty(Queue* queue);
bool IsQueueFull(Queue* queue);
int Front(Queue* queue);
int Back(Queue* queue);
int DeQueue(Queue* queue);
void EnQueue(Queue* queue, int action, char* username, char* password, char* profilePicURL, char* heldValue);
QueueNode* CreateNewAccount(int action, char* username, char* password, char* profilePicURL, char* heldValue);

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
	struct Account* head = NULL;

	//Queue
	Queue* queue = InitializeQueue();

	while (exitLoop != EXIT) {
		printf(" ===YOUR ACCOUNT MANAGER=== \n");
		printf("1.\t Create Account\n");
		printf("2.\t Delete Account\n");
		printf("3.\t Change an Account's Username\n");
		printf("4.\t Change an Account's Password\n");
		printf("5.\t Change an Account's Profile Picture\n");
		printf("6.\t See Accounts\n");
		printf("7.\t See History\n");
		printf("8.\t Delete History (NOTE: Action cannot be undone. All previous actions will be unrecoverable.)\n");
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
			break;

		case SEE_HISTORY:
			viewHistory(head, stack, queue);
			break;

		case DELETE_HISTORY:
			deleteHistory(stack);
			break;

		case EXIT:
			exitLoop = EXIT;
			break;
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
	//Add action to stack
	head->username = userName;
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
	//Add action to stack
	head->password = pass;
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
	//Add action to stack
	head->profilePicURL = profilePicture;
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

void viewHistory(Account* head, Stack* stack, Queue* queue)
{
	int exit = 0;
	int userNum = 0;
	char userInput[MAX_ARRAY_SIZE] = "";
	struct StackNode* action = stack->top;

	//Peek into stack & set action to top

	while (exit == 0) {
		printf("====HISTORY====\n");

		switch (action->action) {
		case DELETE_ACCOUNT:
			printf("Account Deleted... Details:\n");
			printf("Username: %s\n", action->username);
			printf("Password: %s\n", action->password);
			printf("PFP:      %s\n", action->profilePicUrl);
			break;
		case CREATE_ACCOUNT:
			printf("Account Created... Details:\n");
			printf("Username: %s\n", action->username);
			printf("Password: %s\n", action->password);
			printf("PFP:      %s\n", action->profilePicUrl);
			break;
		case CHANGE_USER:
			printf("Username Changed... Details:\n");
			printf("Current Username: %s\n", action->username);
			printf("Old Username:     %s\n", action->heldValue);
			break;
		case CHANGE_PASSWORD:
			printf("Password Changed... Details:\n");
			printf("Edited Account:   %s\n", action->username);
			printf("Current Password: %s\n", action->password);
			printf("Old Password:     %s\n", action->heldValue);
			break;
		case CHANGE_PROFILE:
			printf("Profile Picture Changed... Details:\n");
			printf("Edited Account: %s\n", action->username);
			printf("Current PFP:    %s\n", action->profilePicUrl);
			printf("Old PFP:        %s\n", action->heldValue);
			break;
		}

		printf("===============\n");
		printf("1. Move back\n");
		printf("2. Move forward\n");
		printf("3. Undo\n");
		printf("4. Delete from History. (NOTE: Will be unable to undo this action)\n");
		printf("5. Exit to menu\n");

		strcpy(userInput, collectUserInput());
		userNum = atoi(userInput);
		if (userNum < 1 || userNum > 4) {
			printf("Invalid input\n");
			continue;
		}

		switch (userNum) {
		case MOVE_FORWARD:
			//Enqueue action
			//Pop stack
			break;

		case MOVE_BACK:
			//Push action
			//Dequeue queue
			break;
		case UNDO:
			if (action->action == CREATE_ACCOUNT) {
				//Delete node in linked list
				//Pop stack
			}
			else if (action->action == DELETE_ACCOUNT) {
				//Create node in linked list
				//Pop Stack
			}
			else if (action->action == CHANGE_USER) {
				//search linked list for action->username
				head->username = action->heldValue;
				//Pop Stack
			}
			else if (action->action == CHANGE_PASSWORD) {
				//search linked list for action->username
				head->password = action->heldValue;
				//Pop stack
			}
			else if (action->action == CHANGE_PROFILE) {
				//Search linked list for action->username
				head->password = action->heldValue;
				//Pop stack
			}
			break;

		case DELETE_FROM_HIS:
			//Pop stack w/o enqueue
			break;
			
		case TO_MENU:
			//Dequeue & Push to stack until queue is empty
			exit = EXIT;
		}
	}
}

void deleteHistory(Stack* stack)
{
	while (stack != NULL) {
		//Pop stack
	}
}

//Working in Queue

Queue* InitializeQueue(void)
{
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (queue == NULL)
	{
		printf("No Memory");
		exit(EXIT);
	}

	queue->front = NULL;
	queue->back = NULL;
	return queue;
}

bool IsQueueEmpty(Queue* queue)
{
	return queue->front == NULL;
}

bool IsQueueFull(Queue* queue)
{
	QueueNode* temp = queue->front;
	if (temp == NULL)
	{
		return false;
	}
	for (int counter = 0; temp != queue->back; counter++)
	{
		if (counter == MAX_QUEUE_SIZE)
		{
			return true;
		}
	}

	free(temp);
	return false;
}

int Front(Queue* queue)
{
	if (IsQueueEmpty(queue))
	{
		printf("Queue is Empty");
		return EXIT;
	}
	return queue->front->action;
}

int Back(Queue* queue)
{
	if (IsQueueEmpty(queue))
	{
		printf("Queue is Empty");
		return EXIT;
	}

	return queue->back->action;
}

int DeQueue(Queue* queue)
{
	if (IsQueueEmpty(queue))
	{
		printf("Queue is Empty");
		return EXIT;
	}

	QueueNode* nodeToDQueue = queue->front;
	int dataToDequeue = nodeToDQueue->action;
	queue->front = nodeToDQueue->next;
	free(nodeToDQueue);
	return dataToDequeue;
}

void EnQueue(Queue* queue, int action, char* username, char* password, char* profilePicURL, char* heldValue)
{
	if (queue == NULL)
	{
		queue = InitializeQueue();
	}

	QueueNode* toEnqueue = CreateNewAccount(action, username, password, profilePicURL, heldValue);
	if (IsQueueEmpty(queue))
	{
		queue->front = toEnqueue;
		queue->back = toEnqueue;
	}
	else
	{
		queue->back->next = toEnqueue;
		queue->back = toEnqueue;
	}

}

QueueNode* CreateNewAccount(int action, char* username, char* password, char* profilePicURL, char* heldValue)
{
	QueueNode* newAccount = (QueueNode*)malloc(sizeof(QueueNode));
	if (newAccount == NULL)
	{
		printf("No Memory");
		exit(EXIT);
	}

	newAccount->action = action;
	newAccount->username = username;
	newAccount->password = password;
	newAccount->profilePicURl = profilePicURL;
	newAccount->heldValue = heldValue;
	newAccount->next = NULL;
	return newAccount;
}