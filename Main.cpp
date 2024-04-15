#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable: 4996)

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

struct StackNode* pop(Stack* stack);
struct Stack* push(Stack* stack, int action, char* user, char* pass, char* pfp, char* held);
struct StackNode* peek(Stack* stack);

struct StackNode* pop(Stack* stack)
{
	if (stack->top == NULL) {
		printf("Stack Empty.\n");
		return NULL;
	}
	struct StackNode* temp = stack->top;
	stack->top = stack->top->next;
	strcpy(temp->heldValue, "NULL");
	strcpy(temp->password, "NULL");
	strcpy(temp->username, "NULL");
	strcpy(temp->profilePicUrl, "NULL");
	free(temp);
	return stack->top;
}

struct Stack* push(Stack* stack, int action, char* user, char* pass, char* pfp, char* held)
{
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	if (newNode == NULL) {
		printf("Out of memory.\n");
		exit(EXIT);
	}

	newNode->username = (char*)malloc(sizeof(char));
	if (newNode->username == NULL) {
		printf("Out of memory.\n");
		exit(EXIT);
	}
	newNode->password = (char*)malloc(sizeof(char));
	if (newNode->password == NULL) {
		printf("Out of memory.\n");
		exit(EXIT);
	}
	newNode->profilePicUrl = (char*)malloc(sizeof(char));
	if (newNode->profilePicUrl == NULL) {
		printf("Out of memory.\n");
		exit(EXIT);
	}
	newNode->heldValue = (char*)malloc(sizeof(char));
	if (newNode->heldValue == NULL) {
		printf("Out of memory.\n");
		exit(EXIT);
	}
	newNode->action = action;
	strcpy(newNode->username, user);
	strcpy(newNode->password, pass);
	strcpy(newNode->profilePicUrl, pfp);
	if (held != NULL) {
		strcpy(newNode->heldValue, held);
	}
	newNode->next = stack->top;
	stack->top = newNode;
	return stack;
}

struct StackNode* peek(Stack* stack)
{
	if (stack->top == NULL) {
		printf("Stack Empty.\n");
		return NULL;
	}
	return stack->top;
}