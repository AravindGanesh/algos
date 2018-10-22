/******************************************************************************
• ‘N’ followed by number of vertices n ∈ N.
• ‘E’ followed by a vertex and vertex-weight pairs that look like:
u, v 1 , w(u, v 1 ), v 2 , w(u, v 2 ) · · · , v k , w(u, v k )
This list gives the adjacency list of vertex u along with the respective edge weights.
The list is given as a space-separated list.
• ‘?’ followed by u, v ∈ [n] with a space separating them.
• ‘D’ followed by a u ∈ [n].
• ‘P’ followed by u, v ∈ [n] with a space separating them.
////////////////////////////////////////////////////////////////////////////////
• If input line started with ‘N’ or ‘E’, then no corresponding output.
• If input line was “? u v”: Output w(u, v) if (u, v) ∈ E, −1 otherwise.
• If input line was “D u”:
Let v 1 , v 2 , . . . , v n be the order of vertices visited on a run of of Dijkstra’s algorithm
from u (note that u = v 1 ). Let δ(u, v) denote the shortest path from u to v. Output
a list of pairs: (v 1 , δ(u, v 1 )), . . . , (v n , δ(u, v n )). If δ(u, v) = ∞ then output −1 in its
place. Use a space to separate v and δ(u, v) within a pair. Use a ‘\n’ between pairs.
• If input line was “P u v”:
If v is not reachable from u, output −1. Else output the shortest distance from u to
v followed by a shortest path from u to v as a space-separated list of vertices starting
with u.
All output lines have to end with a ‘\n’ character.
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

//
struct priorityQ{
	unsigned int v, pi, d;
};

//
struct list{
	unsigned int v, w;
	struct list *next;
};

//
struct graph{ // an array of this struct will represent my graph
	struct list *adjList; 
};

// function to swap two numbers
void swap(struct priorityQ *a, struct priorityQ *b){
	struct priorityQ temp = *a;
	*a = *b;
	*b = temp;
}

// reference: CLRS
void HEAPIFY(int n, struct priorityQ *heap, int i){
	int left_i = 2*i + 1, right_i = 2*i + 2, min_i = i;
	
	if((left_i < n) && (heap[left_i].d < heap[min_i].d)) min_i = left_i;
	
	if((right_i < n) && (heap[right_i].d < heap[min_i].d)) min_i = right_i;
	
	if(min_i != i){
		swap(&(heap[i]), &(heap[min_i]));
		HEAPIFY(n, heap, min_i);
	}
}

// 
unsigned int extract_min(int n, struct priorityQ *heap){
	if(n==0) return -1;
	int minVal = heap[0];
	heap[0] = heap[n-1];
	n--;
	HEAPIFY(n, heap, 0);
	return minVal;
}

// 
void decrease_key(int n, struct priorityQ *heap, int i, unsigned int key){
	heap[i] = key;
	for(; i!=0 && heap[i].d < heap[(i-1)/2].d; i=(i-1)/2){
		swap(&heap[i], &heap[(i-1)/2]);
	}
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

// 
unsigned int weight(int n, struct list **Graph, unsigned int u, unsigned int v){
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

	if(adju == NULL)return -1;
	else return adju->w;
}

/******************************************************************************
// From Lecture Slides
For all u ∈ V , d[u] ← ∞, π[u] ← NIL
d[s] ← 0
Initialize min-priority queue Q ← V
S ←∅
while Q 6 = ∅ do
u ← Extract-Min(Q)
S ← S ∪ {u}
	for each v ∈ N (u) do
		if d[u] + w(u, v) < d[v] then
			d[v] ← d[u] + w(u, v)
			DECREASE-KEY(v, d[v]).
			π[v] ← u
		end if
	end for
end while
******************************************************************************/

//
void Dijkstra(struct graph *G, int n, unsigned int s, struct priorityQ *Q){
	int i=0;
	for(i=0; i<n; i++){
		Q[i].d = -1;
		Q[i].pi = 0;
		Q[i].v = i+1;
	}
	

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

//
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
		else if(d == 'D') option = 'D';
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