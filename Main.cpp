#include <stdio.h>

#define CREATE_ACCOUNT	1
#define DELETE_ACCOUNT	2
#define CHANGE_USER		3
#define CHANGE_PASSWORD	4
#define CHANGE_PROFILE	5

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

int main(void) {

}