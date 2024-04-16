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
	struct Stack* next;
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
void viewHistory(Account* head, Stack* stack, Queue* queue);
void deleteHistory(Stack* stack);

// Account/linked list stuff
struct Account* insertNode(struct Account* head, char* username, char* password, char* pfpURL);
struct Account* searchAccountByUser(struct Account* head, char* username);
void deleteAccountNode(struct Account* head, char* username);

int main(void) {

	int exitLoop = 0;
	int loop = 0;
	int userNum = 0;
	char userInput[MAX_ARRAY_SIZE] = "";
	char userName[MAX_ARRAY_SIZE] = "";
	char pass[MAX_ARRAY_SIZE] = "";
	char profileURL[MAX_ARRAY_SIZE] = "";
	struct Account* current = NULL;

	struct Stack* stack = (Stack*)malloc(sizeof(Stack));
	if (stack == NULL) {
		printf("No memory.");
		exit(EXIT);
	}
	stack->top = NULL;
	struct StackNode* action = stack->top;
	//struct Queue* queue = InitializeQueue();

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
		printf("8.\t Delete History (NOTE: Action cannot be undone. All previous actions will be unrecoverable.)\n");
		printf("9.\t Exit Program\n");

		fgets(userInput, MAX_ARRAY_SIZE, stdin);
		strcpy(userInput, removeNewLine(userInput));
		userNum = atoi(userInput);
		if (userNum < 1 || userNum > 9) {
			printf("Invalid input\n");
			continue;
		}

		switch (userNum) {
		case CREATE_ACCOUNT:
			loop = 0;
			while (loop == 0) {
				printf("Enter a Username: ");
				fgets(userName, MAX_ARRAY_SIZE, stdin);
				strcpy(userName, removeNewLine(userName));
				//current = searchAccountByUser(head, userName);
				if (current != NULL) {
					printf("Account with username %s already exists. \n", userName);
					continue;
				}
				printf("Password must be at least 6 characters in length and contain: Number, Uppercase, Lowercase, and Symbol (!@#$\\%&*_+=-,.?)\n");
				printf("Enter a Password: ");
				fgets(pass, MAX_ARRAY_SIZE, stdin);
				strcpy(pass, removeNewLine(pass));
				if (isPasswordValid(pass) == false) {
					printf("Password does not meet requirements.\n");
					continue;
				}
				printf("Enter a PFP URL: ");
				fgets(profileURL, MAX_ARRAY_SIZE, stdin);
				strcpy(profileURL, removeNewLine(profileURL));
				loop = EXIT;
			}
			//head = insertNode(head, userName, pass, profileURL);
			//push(stack, CREATE_ACCOUNT, userName, pass, profileURL, NULL);
			break;

		case DELETE_ACCOUNT:
			if (head == NULL) {
				printf("No account in list - Cannot delete account that does not exist.\n");
				break;
			}
			loop = 0;
			while (loop == 0) {
				printf("Enter the Username of the Account to be Deleted: ");
				fgets(userName, MAX_ARRAY_SIZE, stdin);
				strcpy(userName, removeNewLine(userName));
				//current = searchAccountByUser(head, userName);
				if (current == NULL) {
					printf("No account with username %s found. \n", userName);
					continue;
				}
				printf("Enter Account's Password: ");
				fgets(pass, MAX_ARRAY_SIZE, stdin);
				strcpy(pass, removeNewLine(pass));
				if (correctPass(*current, pass) == false) {
					printf("Incorrect Password.\n");
					continue;
				}
				loop = EXIT;
			}

			//push(stack, DELETE_ACCOUNT, current->username, current->password, current->profilePicURL, NULL);
			//deleteAccountNode(head, userName);
			break;

		case CHANGE_USER:
			loop = 0;
			while (loop == 0) {
				printf("Enter Username of Account to be Edited: ");
				fgets(userName, MAX_ARRAY_SIZE, stdin);
				strcpy(userName, removeNewLine(userName));
				//current = searchAccountByUser(head, userName);
				if (current == NULL) {
					printf("No account with username %s found. \n", userName);
					continue;
				}
				printf("Enter Account's Password: ");
				fgets(pass, MAX_ARRAY_SIZE, stdin);
				strcpy(pass, removeNewLine(pass));
				if (correctPass(*current, pass) == false) {
					printf("Incorrect Password.\n");
					continue;
				}
				loop = EXIT;
			}

			printf("Enter new Username: ");
			fgets(userName, MAX_ARRAY_SIZE, stdin);
			strcpy(userName, removeNewLine(userName));
			//push(stack, CHANGE_USER, userName, current->password, current->profilePicURL, current->username);
			strcpy(current->username, userName);
			break;

		case CHANGE_PASSWORD:
			loop = 0;
			while (loop == 0) {
				printf("Enter Username of Account to be Edited: ");
				fgets(userName, MAX_ARRAY_SIZE, stdin);
				strcpy(userName, removeNewLine(userName));
				//current = searchAccountByUser(head, userName);
				if (current == NULL) {
					printf("No account with username %s found. \n", userName);
					continue;
				}
				printf("Enter Account's Current Password: ");
				fgets(pass, MAX_ARRAY_SIZE, stdin);
				strcpy(pass, removeNewLine(pass));
				if (correctPass(*current, pass) == false) {
					printf("Incorrect Password.\n");
					continue;
				}
				loop = EXIT;
			}

			printf("Enter new Password: ");
			fgets(pass, MAX_ARRAY_SIZE, stdin);
			strcpy(pass, removeNewLine(pass));
			//push(stack, CHANGE_PASSWORD, current->username, pass, current->profilePicURL, current->password);
			strcpy(current->password, pass);
			break;

		case CHANGE_PROFILE:
			loop = 0;
			while (loop == 0) {
				printf("Enter Username of Account to be Edited: ");
				fgets(userName, MAX_ARRAY_SIZE, stdin);
				strcpy(userName, removeNewLine(userName));
				//current = searchAccountByUser(head, userName);
				if (current == NULL) {
					printf("No account with username %s found. \n", userName);
					continue;
				}
				printf("Enter Account's Password: ");
				fgets(pass, MAX_ARRAY_SIZE, stdin);
				strcpy(pass, removeNewLine(pass));
				if (correctPass(*current, pass) == false) {
					printf("Incorrect Password.\n");
					continue;
				}
				loop = EXIT;
			}

			printf("Enter new Profile Picture URL: ");
			fgets(profileURL, MAX_ARRAY_SIZE, stdin);
			strcpy(profileURL, removeNewLine(profileURL));
			//push(stack, CHANGE_PROFILE, current->username, current->password, profileURL, current->profilePicURL);
			strcpy(head->profilePicURL, profileURL);
			break;

		case SEE_ACCOUNTS:
			current = head;
			printf("===ACCOUNT===\n");
			while (current != NULL) {
				printf("Username: %s\n", current->username);
				printf("Password: %s\n", current->password);
				printf("PFP:      %s\n", current->profilePicURL);
				printf("=============\n");

				current = current->next;
			}
			break;

		case SEE_HISTORY:
			action = stack->top;
			loop = 0;
			while (loop == 0) {

				if (stack->top != NULL) {
					//action = peek(stack);
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
				}
				else {
					printf("End of history.\n");
				}

				printf("===============\n");
				printf("1. Move back\n");
				printf("2. Move forward\n");
				printf("3. Undo\n");
				printf("4. Delete from History. (NOTE: Will be unable to undo this action)\n");
				printf("5. Exit to menu\n");

				fgets(userInput, MAX_ARRAY_SIZE, stdin);
				strcpy(userInput, removeNewLine(userInput));
				userNum = atoi(userInput);
				if (userNum < 1 || userNum > 4) {
					printf("Invalid input\n");
					continue;
				}

				switch (userNum) {
				case MOVE_BACK:
					//EnQueue(queue, action->action, action->username, action->password, action->profilePicUrl, action->heldValue);
					//stack->top = pop(stack);
					break;

				case MOVE_FORWARD:
					/*if (queue->front == NULL) {
						printf("No action in forward history.");
					}
					else {
						push(stack, queue->front->action, queue->front->username, queue->front->password, queue->front->profilePicURl, queue->front->heldValue);
						DeQueue(queue);
					}*/
					break;
				case UNDO:
					if (action->action == CREATE_ACCOUNT) {
						//deleteAccountNode(head, action->username);
						//pop(stack);
					}
					else if (action->action == DELETE_ACCOUNT) {
						//insertNode(head, action->username, action->password, action->profilePicUrl);
						//pop(stack);
					}
					else if (action->action == CHANGE_USER) {
						//current = searchAccountByUser(head, action->username);
						strcpy(current->username, action->heldValue);
						//pop(stack);
					}
					else if (action->action == CHANGE_PASSWORD) {
						//current = searchAccountByUser(head, action->username);
						strcpy(current->password, action->heldValue);
						//pop(stack);
					}
					else if (action->action == CHANGE_PROFILE) {
						//current = searchAccountByUser(head, action->username);
						strcpy(current->profilePicURL, action->heldValue);
						//pop(stack);
					}
					break;

				case DELETE_FROM_HIS:
					//pop(stack);
					break;

				case TO_MENU:
					/*while (queue->front != NULL) {
						push(stack, queue->front->action, queue->front->username, queue->front->password, queue->front->profilePicURl, queue->front->heldValue);
						DeQueue(queue);
					}
					loop = EXIT;
					break;*/
				}
			}
			break;

		case DELETE_HISTORY:
			while (stack != NULL) {
				//pop(stack);
			}
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

struct Account* insertNode(struct Account* head, char* username, char* password, char* pfpURL)
{
	struct Account* newAccount = (struct Account*)malloc(sizeof(struct Account));
	if (newAccount == NULL) {
		printf("No Memory!");
		exit(EXIT);
	}

	struct Account* currentt = head;

	newAccount->username = (char*)malloc(sizeof(char*));
	if (newAccount->username == NULL) {
		printf("No Memory!");
		exit(EXIT);
	}
	newAccount->password = (char*)malloc(sizeof(char*));
	if (newAccount->password == NULL) {
		printf("No Memory!");
		exit(EXIT);
	}
	newAccount->profilePicURL = (char*)malloc(sizeof(char*));
	if (newAccount->profilePicURL == NULL) {
		printf("No Memory!");
		exit(EXIT);
	}

	strcpy(newAccount->username, username);
	strcpy(newAccount->password, password);
	strcpy(newAccount->profilePicURL, pfpURL);
	newAccount->next = NULL;

	if (currentt != NULL) {
		while (currentt->next != NULL) {
			currentt = currentt->next;
		}
		currentt->next = newAccount;
		return head;
	}
	return newAccount;
}

struct Account* searchAccountByUser(struct Account* head, char* username)
{
	int loop = 0;
	struct Account* current = head;

	while (current != NULL && loop == 0) {
		if (strcmp(current->username, username) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

void deleteAccountNode(struct Account* head, char* username)
{
	struct Account* current = head;
	struct Account* temp = NULL;
	int exit = 0;


	while (current != NULL) {
		if (strcmp(current->username, username) == 0) {
			printf("Deleting Account\n");
			exit = EXIT;

			if (temp == NULL) {
				head = current->next;
				current->next = NULL;
				strcpy(current->password, "NULL");
				strcpy(current->profilePicURL, "NULL");
				strcpy(current->username, "NULL");
				free(current);
				return;
			}
			else if (current->next == NULL) {
				temp->next = NULL;
				strcpy(current->password, "NULL");
				strcpy(current->profilePicURL, "NULL");
				strcpy(current->username, "NULL");
				free(current);
				return;
			}
			else {
				temp->next = current->next;
				current->next = NULL;
				strcpy(current->password, "NULL");
				strcpy(current->profilePicURL, "NULL");
				strcpy(current->username, "NULL");
				free(current);
				return;
			}
		}
		temp = current;
		current = current->next;
	}

	printf("No account with username %s found.\n", username);
	return;
}