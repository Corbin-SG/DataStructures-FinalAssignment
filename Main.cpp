#include <stdio.h>
#include <string.h>

#define CREATE_ACCOUNT	1
#define DELETE_ACCOUNT	2
#define CHANGE_USER		3
#define CHANGE_PASSWORD	4
#define CHANGE_PROFILE	5
#define MIN_PASS_LENGTH	6

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

int main(void) {

	return 0;
}

bool isPasswordValid(char* pass) {
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