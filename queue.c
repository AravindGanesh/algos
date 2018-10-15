#include <stdio.h>
#include <stdlib.h>

// singly linked list
struct node{
	int key;
	struct node *next;
};

void printQ(struct node *head){
	struct node *temp = head;
	while(temp!=NULL){
		printf("%d  ", temp->key);
		temp = temp->next;
	}printf("\n");
}

// insert at the end
struct node *enqueue(struct node *head, int x){
	struct node *temp = head;
	struct node *link = (struct node*)malloc(sizeof(struct node));
	link->key = x;
	link->next = NULL;

	if(temp == NULL)return link;

	while(temp->next != NULL) temp = temp->next;
	temp->next = link;
	return head;
}


// delete at the start
struct node *dequeue(struct node *head){
	struct node *temp = head;
	if(temp == NULL) return temp;
	head = temp->next;
	free(temp);
	return head;
}

int main(){
	struct node *head = NULL;
	int x;
	printf("give something to enqueue\n");
	scanf("%d", &x);
	head = dequeue(head);
	head = enqueue(head, x);
	head = enqueue(head, 2);
	head = enqueue(head, 3);
	head = enqueue(head, 4);
	head = enqueue(head, 5);
	head = enqueue(head, 6);
	printQ(head);
	head = dequeue(head);
	printQ(head);
	head = dequeue(head);
	printQ(head);
	head = dequeue(head);
	printQ(head);
	return 0;

}