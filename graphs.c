/******************************************************************************
• ‘N’ followed by number of vertices n ∈ N.
• ‘E’ followed by vertices u, v 1 , v 2 , · · · , v k ∈ [n] that indicates the
  adjacency list of vertex u. The list is given as a space-separated list.
• ‘?’ followed by u, v ∈ [n] with a space separating them.
• ‘B’ followed by a u ∈ [n]
• ‘P’ followed by u, v ∈ [n] with a space separating them.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

struct list{
	int v;
	// int color = WHITE;
	struct list *next;
};

struct Queue{
	int key;
	struct Queue *next;
};

// insert an element at the end to an adjacency list
struct list *adjInsert(struct list *adjListHead, int v){
	struct list *node = (struct list*)malloc(sizeof(struct list));
	struct list *temp = adjListHead;
	node->v = v;
	node->next = NULL;

	if(temp == NULL) return node;
	while(temp->next != NULL) temp = temp->next;
	temp->next = node;
	return adjListHead;
}

// Breadth First Traversal, reference: lecture slides and CLRS, 
void BFS(int n, struct list **Graph, int u){
	int i=0,v=0, colors[n];
	for(v=0; v<n; v++){
		colors[n] = WHITE;
	}
	colors[u-1] = GRAY;
	struct Queue *Q = NULL;
	Q = enqueue(Q, u);
	while(Q != NULL){
		printf("%d ", Q->key);
		Q = dequeue(Q);
		struct list *adj_u = Graph[u-1];
		for(; adj_u != NULL; adj_u = adj_u->next){
			int v = adj_u->v;
		}
	}
}

// shortest path using BFS
void shortestPath(int n, struct list **Graph, int u, int v){
	int i=0,z,x,j, colors[n], pi[n], path[n];
	struct Queue *Q = NULL;
	for(i=0; i<n; i++){
		colors[i] = WHITE;
	}
	colors[u-1] = GRAY;
	Q = enqueue(Q, u);
	while(Q->key  != v){
		x = Q->key; // front 
	
		Q = dequeue(Q);
		struct list *adj_u = Graph[x-1];
		for(; adj_u != NULL; adj_u = adj_u->next){
			int z = adj_u->v;
			if(colors[z-1] == WHITE){
				colors[z-1] = GRAY;
				Q = enqueue(Q, z);
				pi[z-1] = x;
			}
		}colors[x-1] = BLACK;
	}
	printf("%d ", u);
	for(i=v,j=0; i!=u; i=pi[i-1], j++) path[j]=i;
		
	for(j;j>0;j--)printf("%d ", path[j-1]);
}

// insert at the end
struct Queue *enqueue(struct Queue *head, int x){
	struct Queue *temp = head;
	struct Queue *link = (struct Queue*)malloc(sizeof(struct Queue));
	link->key = x;
	link->next = NULL;

	if(temp == NULL)return link;

	while(temp->next != NULL) temp = temp->next;
	temp->next = link;
	return head;
}

// delete at the start
struct Queue *dequeue(struct Queue *head){
	struct Queue *temp = head;
	if(temp == NULL) return temp;
	head = temp->next;
	free(temp);
	return head;
}



int main(){

	char d, option; 
	int i=0, j=0, V_size, V_idx;
	int X;
	struct list **Graph = (struct list**)malloc(V_size*sizeof(struct list*));
	for(i=0; i<V_size; i++) *Graph[i] = NULL; 

	// struct node *tree = NULL, *temp = NULL;
	while((d=fgetc(stdin))!=EOF){
		// assuming that the given list is valid preorder traversal
		if(d == 'N'){
			option = 'N';
			free_tree(tree);
			tree = NULL;
		}
		// else if(d == 'B') option = 'B';
		else if(d == 'E') option = 'E';
		else if(d == '?') option = '?';
		else if(d == 'B') option = 'B';
		else if(d == 'P') option = 'P';

		else if(d == ' '){
			if(option == 'E'){
				if(X!=0) *Graph[V_idx] = adjInsert(*Graph[i], X);
				X = 0; // since only natural numbers are used
			}
		}
		else if(d == '\n'){
			switch(option){
				case 'N':
					V_size = X;
					break;

				case 'E':
					search(tree, X);
					break;

				case '?':
					if(X!=0)tree = insert(tree, X); // only natural numbers
					break;

				case 'P':
					PreOrder(tree);
					printf("\n");
					break;

				case 'B':
					
					break;

				default: break;
			}
			X = 0;
		}

		else{
			 X = 10*X + (d - '0');
		}
	}
	return 0;
}

