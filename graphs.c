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
	struct list *next;
};

struct Queue{
	int key;
	struct Queue *next;
};

// insert at the end
struct Queue *enqueue(struct Queue *head, int a){
	struct Queue *temp = head;
	struct Queue *link = (struct Queue*)malloc(sizeof(struct Queue));
	link->key = a;
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

int isEdge(int n, struct list **Graph, int u, int v){
	struct list *adju;
	int i;
	for(i=0; i<n; i++){
		if(Graph[i]->v == u){
			adju = Graph[i];
			break;
		}
	}
	for(adju = adju->next;(adju != NULL); adju = adju->next){
		if(adju->v == v) break;
	}

	if(adju == NULL)return 0;
	else return 1;	
}

// Breadth First Traversal, reference: lecture slides and CLRS, 
// reference: CLRS 
void BFS(int n, struct list **Graph, int s, int *pi, int flag){
	int i=0,v,u, colors[n];
	// P.V = n;
	pi[0] = s;
	struct Queue *Q = NULL;
	for(i=0; i<n; i++){
		colors[i] = WHITE;
		pi[i+1] = 0;
	}
	colors[s-1] = GRAY;
	Q = enqueue(Q, s);
	while(Q != NULL){
		u = Q->key; // front 
		if(flag == 0) printf("%d ", u);
		Q = dequeue(Q);
		struct list *adju = Graph[u-1];
		for(; adju != NULL; adju = adju->next){
			v = adju->v;
			if(colors[v-1] == WHITE){
				colors[v-1] = GRAY;
				pi[v] = u;
				Q = enqueue(Q, v);
			}
		}
		colors[u-1] = BLACK;
		// if(flag == 0) printf("%d ", u);
	}
}

void shortestPath(int *pi, int dest){
	// TODO: give -1 if no path exists
	int src = pi[0];
	if(src == dest){
		printf("%d ",src);
		return;
	}
	else if(pi[dest] == 0){
		printf("-1 ");
		return;
	}
	else{
		int dest_pi = pi[dest];
		shortestPath(pi, dest_pi);
	}printf("%d ", dest);
}

// function to free list after each line
void FreeList(struct list* head){
	struct list* temp;
	while(head!=NULL){
		temp = head;
		head = head->next;
		free(temp);
	}head = NULL;
}

void free_graph(int n, struct list **graph){
	int i=0;
	for(i=0; i<n; i++) FreeList(graph[i]);
	return;
}


int main(){

	char d, option; 
	int i,V_size, V_idx=0, a, u=0, v=0;
	struct list **Graph;
	int *pis;
	// struct node *tree = NULL, *temp = NULL;
	while((d=fgetc(stdin))!=EOF){
		// assuming that the given list is valid preorder traversal
		if(d == 'N'){
			option = 'N';
			V_idx = 0;
			free_graph(V_size,Graph);
		}
		// else if(d == 'B') option = 'B';
		else if(d == 'E') option = 'E';
		else if(d == '?') option = '?';
		else if(d == 'B') option = 'B';
		else if(d == 'P') option = 'P';

		else if(d == ' '){
			if(option == 'E'){
				if(a!=0){
					Graph[V_idx] = adjInsert(Graph[V_idx], a);
				}
				a = 0; // since only natural numbers are used
			}
			else if((option == '?') || (option == 'P')){
				if(u==0 && a!=0) u = a;
				else if(a!=0) v = a;	
			}
				a = 0;
		}
	else if(d == '\n'){
			switch(option){
				case 'N':
					V_size = a;
					Graph = (struct list**)malloc((V_size)*sizeof(struct list*));
					for(i=0; i<V_size; i++) Graph[i] = NULL; 
					pis = (int*)malloc((V_size+1)*sizeof(int));
					break;

				case 'E':
					if(a!=0) Graph[V_idx] = adjInsert(Graph[V_idx], a);
					// printAdjList(Graph[V_idx]);
					V_idx++;
					break;

				case '?':
					if(a!=0) v = a;
					printf("%d\n", isEdge(V_size, Graph, u, v));
					u=0; v=0;
					break;

				case 'P':
					if(a!=0) v = a;
					if(pis[0]!=u){
						for(i=0; i<=V_size; i++) pis[i]=0;
						BFS(V_size, Graph, u, pis, 1);
					}
					shortestPath(pis, v);
					printf("\n");
					break;

				case 'B':
					BFS(V_size, Graph, a, pis, 0);
					printf("\n");
					break;

				default: break;
			}
			a = 0;
		}

		else{
			 a = 10*a + (d - '0');
		}
	}
	return 0;
}