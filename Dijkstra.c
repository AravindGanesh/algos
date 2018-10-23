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
struct list{
	unsigned int v, w;
	struct list *next;
};

//
struct graph{ // an array of this struct will represent my graph
	struct list *adjList; 
};

// node of a priority Queue with vertex, parent and distance (in Dijkstra traversal)
struct priorityQ{
	unsigned int v, pi, d;
};

// function to swap two nodes of a priority Queue
void swap(struct priorityQ *a, struct priorityQ *b){
	struct priorityQ temp = *a;
	*a = *b;
	*b = temp;
}

// reference: CLRS
// function to make the array to a min-heap (w.r.t distances)
void HEAPIFY(int n, struct priorityQ *heap, int i){
	int left_i = (2*i)+1, right_i = (2*i)+2, min_i = i;
	
	if((left_i < n) && (heap[left_i].d < heap[min_i].d)) min_i = left_i;
	
	if((right_i < n) && (heap[right_i].d < heap[min_i].d)) min_i = right_i;
	
	if(min_i != i){
		swap(&(heap[i]), &(heap[min_i]));
		HEAPIFY(n, heap, min_i);
	}
}

// remove and returns node withmin d value from min-heap
struct priorityQ extract_min(int n, struct priorityQ *heap){
	struct priorityQ min;
	min.d = heap[0].d;
	min.v = heap[0].v;
	min.pi = heap[0].pi;
	heap[0].d = heap[n-1].d;
	heap[0].v = heap[n-1].v;
	heap[0].pi = heap[n-1].pi;
	n--;
	HEAPIFY(n, heap, 0);
	return min;
}

// decrease the distance of vertex v to value key  
void decrease_key(int n, struct priorityQ *heap, int i, unsigned int key){
	heap[i].d = key;
	// restore min-heap property to the array
	for(i; i && heap[i].d < heap[(i-1)/2].d; i=(i-1)/2){
		swap(&heap[i], &heap[(i-1)/2]);
	}
}

// insert an element at the end to an adjacency list
struct list *adjInsert(struct list *head, unsigned int v, unsigned int w){
	struct list *node = (struct list*)malloc(sizeof(struct list));
	struct list *temp = head;
	node->v = v;
	node->w = w;
	node->next = NULL;

	if(temp == NULL) return node;
	while(temp->next != NULL) temp = temp->next;
	temp->next = node;
	return head;
}

// 
unsigned int weight(struct graph *G, int n, unsigned int u, unsigned int v){
	struct list *adju = NULL;
	int i;
	adju = G[u-1].adjList;
	if(adju->next == NULL)return -1;

	for(adju=adju->next;(adju != NULL); adju = adju->next){
		if(adju->v == v) break;
	}

	if(adju == NULL)return -1;
	else return adju->w;
}

// function prints Dijkstra traversal from source s
void Dijkstra(struct graph *G, int n, unsigned int s){
	int i=0,j=0, m=n;
	unsigned int distances[n];
	unsigned int u, v, d;
	struct priorityQ *Q = (struct priorityQ*)malloc(n*sizeof(struct priorityQ));
	struct priorityQ qnode;
	struct list *adju = NULL;
	// intialize priority Q; set distances to ∞ and parents to 0
	for(i=0; i<n; i++){
		Q[i].d = -1;
		Q[i].pi = 0;
		Q[i].v = i+1; // vertcies are stored in ascending order in Q nodes
		distances[i] = -1;
	}
	distances[s-1] = 0;
	decrease_key(n, Q, s-1, 0);
	// for(i=0; i<n; i++) printf(" x %d %d x ",Q[i].v, Q[i].d);
	for(m=n; m>0; m--){
		qnode = extract_min(m, Q);
		u = qnode.v;
		printf("%d %d\n",qnode.v, qnode.d);
		adju = G[u-1].adjList;
		for(adju = adju->next; adju!=NULL; adju = adju->next){
			v = adju->v;
			for(j=0; j<m-1; j++){
				if(Q[j].v == v){
					d = Q[j].d;
					break;
				}
			}
			if(qnode.d + adju->w < d){
				d = qnode.d + adju->w;
				decrease_key(m-1, Q, j, d);
				Q[j].pi = u;
			}
		}
	}
}

// 
void shortest_path(struct graph *G, int n, unsigned int src, unsigned int dest){

}

// function to free list after each line
void FreeList(struct list *head){
	struct list* temp;
	while(head!=NULL){
		temp = head;
		head = head->next;
		free(temp);
	}head = NULL;
}

//
void free_graph(int n, struct graph *G){
	if(G==NULL)return;
	int i=0;
	for(i=0; i<n; i++) FreeList(G[i].adjList);
	G = NULL;
	return;
}

/*void printAdjList(struct list *head){
	struct list *temp = head;
	for(;temp!=NULL; temp=temp->next){
		printf(" v=%d, w=%d ", temp->v, temp->w);
	}printf("\n");
}*/

int main(){

	char d, option; 
	int i,V_size, flag=0, V_idx;
	unsigned int u=0, v=0, w=0, a=0;
	struct graph *G = NULL;
	struct priorityQ *Q;
	while((d=fgetc(stdin))!=EOF){
		if(d == 'N'){
			option = 'N';
			// free_graph(V_size,G);
		}
		else if(d == 'E') option = 'E';
		else if(d == '?') option = '?';
		else if(d == 'D') option = 'D';
		else if(d == 'P') option = 'P';

		else if(d == ' '){
			if(option == 'E'){
				if(a!=0){
					if(flag==0){
						V_idx = a-1;
						flag = 1; a=0;
						continue;
					}
					
					if(v==0) v = a;
					else if(v!=0 && w==0) w = a;

					if(v!=0 && w!=0){
						G[V_idx].adjList = adjInsert(G[V_idx].adjList, v, w);
						v=0; w=0;
					}
				}a = 0; // since only natural numbers are used
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
					free_graph(V_size,G);
					G = (struct graph*)malloc(V_size*sizeof(struct graph));
					for(i=0; i<V_size; i++) G[i].adjList = adjInsert(G[i].adjList, i+1, 0);
					Q = (struct priorityQ*)malloc(V_size*sizeof(struct priorityQ));
					break;

				case 'E':
					if(v==0) v = a;
					else if(v!=0 && w==0) w = a;
					if(v!=0 && w!=0) G[V_idx].adjList = adjInsert(G[V_idx].adjList, v, w);
					flag = 0;
					// printAdjList(G[V_idx].adjList);
					break;

				case '?':
					if(a!=0) v = a;
					printf("%d\n", weight(G, V_size, u, v));
					u=0; v=0;
					break;

				case 'P':
					if(a!=0) v = a;
					printf("P %d blah\n",v);
					break;

				case 'D':
					Dijkstra(G, V_size, a);
					break;

				default: break;
			}
			a=0; v=0; u=0; w=0;// flag=0;
		}

		else{
			 a = 10*a + (d - '0');
		}
	}
	return 0;
}