/******************************************************************************
Sum of two large integers using doubly linked lists. 
Each node stores a digit.

Input Format:
• Input through standard input stream.
• Each line will contain two positive integers seperated by a space.
• Each line will end with a ‘\n’ character.
• End of input is indicated by EOF.

Output Format:
• For each line of the input read, your program should output the sum of the two integers read on that line followed by a ‘\n’ character. Implementation rules
• Use a doubly-linked list or a circular doubly-linked list to store the numbers. Each node stores one digit.
• Handle the input line by line. i.e., your program should not wait for all of the input lines. It has to output the sum immediately after reading each line.
• Your code should be modular: write a separate procedure to add two numbers that are represented as doubly-linked list.
******************************************************************************/
 
/*****************************************************************************
my implementation:
inputs are taken into two doubly linked lists with head node storing LSB ignoring leading zeros. 
new linked list is formed with the sum of the inputs and the lists are freed after every input
*****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>

// node of a linked list
struct node{
	uint8_t digit;
	struct node *next;
	struct node *prev;
};

// function to print a list in order from head to tail
void printLargeNum(struct node *head){
	struct node *temp = head;
	while(temp!=NULL){
		printf("%hhu", temp->digit);
		temp = temp->next;
	}printf("\n");
}

// inserts digit at the beginning of the list
struct node *insert(struct node *head, uint8_t d){
	
	struct node *link = (struct node*) malloc(sizeof(struct node));
	// put a new node (link) at the beginning 
	// assign the value to a new node 
	link->digit = d; 
	// prev of node to NULL
	link->prev = NULL;
	// point the prev of head to new node
	if(head != NULL) head->prev = link; 
	// point next of new node to head
	link->next = head;
	// make the new node as head
	head = link;
	return head;
}

// implemented this, but found out that I don't need this. 
// read input number string into linked lists
/*void readNum(char *num_string, struct node *num1, struct node *num2){
	int i=0, c, flag = 0;
	struct node* Number = NULL;
	for(i=0; num_string[i]!='\n', i++){
		if(num_string[i]=='0') continue;
		if(num_string[i] != ' '){
			flag = 1;
			continue;
		}
		c = num_string[i] - '0'
		if(flag==0)num1 = insert(num1, c);
		else if(flag == 1) num2 = insert(num2, c);
	}
}*/

//  function to add the two large numbers
struct node *add(struct node *A, struct node *B){

	struct node *C = NULL; // head pointer of sum
	uint8_t sum = 0, carry = 0; // digits for sum and carry
	// digit by digit sum
	while(A != NULL || B != NULL){
		if(A != NULL && B != NULL){
			sum = A->digit + B->digit + carry;
			// insert the ones digit of sum to new list
			C = insert(C, (sum%10)); 
			carry = sum/10; // carry in each digit
			// traverse the digits 
			A = A->next;  
			B = B->next;
		}
		// if one if the node is NULL
		else if(A == NULL && B != NULL){
			sum = B->digit + carry;
			C = insert(C, (sum%10));
			carry = sum/10;
			B = B->next;
		}
		else if(A != NULL && B == NULL){
			sum = A->digit + carry;
			C = insert(C, (sum%10));
			carry = sum/10;
			A = A->next;
		}
	} 
	// though both the nodes are null, there is a possibility of carry
	if(carry !=0) C = insert(C, carry);
	return C;
}

// function to free list after each line
void FreeList(struct node* head){
	struct node* temp;
	while(head!=NULL){
		temp = head;
		head = head->next;
		free(temp);
	}
}

int main(){

	struct node *num1 = NULL;
	struct node *num2 = NULL;
	struct node *num = NULL;
	int d;
	int flag=0, lead1=0, lead2=0; // flags for inputs, leading zeros
	while((d=fgetc(stdin))!=EOF){
		// if(d!=0)lead=1;
		if(d=='\n'){
			num = add(num1, num2);
			printLargeNum(num);
			// free lists after each line
			FreeList(num1);
			FreeList(num2);
			FreeList(num);
			num1 = NULL;
			num2 = NULL;
			num = NULL;
			// setings flag values
			flag=0; lead1=0; lead2=0;
		}
		else if(d==' ') flag = 1; // flag for second input
		else{
			if(flag==0){ // first input
				lead1 += (d - '0'); // leading zeros sum = 0
				if(lead1 > 0) num1 = insert(num1, (d-'0'));
			}
			else if(flag==1){ // second input
				lead2 += (d - '0');
				if(lead2>0) num2 = insert(num2, (d-'0'));
			}
		}
	}
	return 0;
}


