#include <stdio.h>
#include <stdlib.h>

// linked list to store adjacency lists with weights 
struct list{
	unsigned int v, w;
	struct list *next;
};

// an array of this struct will represent my graph
struct graph{
	struct list *adjList; 
};

// node of a priority Queue with vertex, parent and distance (in Dijkstra traversal)
struct priorityQ{
	unsigned int v, d;
};

// array of this will store at index = v-1,  distance from source and parent of v 
struct path{
	unsigned int d, pi;
};

// function to swap two nodes of a priority Queue
void swap(struct priorityQ *a, struct priorityQ *b){
	struct priorityQ temp = *a;
	*a = *b;
	*b = temp;
}

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
	heap[0].d = heap[n-1].d;
	heap[0].v = heap[n-1].v;
	n--;
	HEAPIFY(n, heap, 0);
	return min;
}

// decrease the distance at index i to value key  
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

// function to get weight of the edge between u and v
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
// Trick: -1 will be treated as ∞ since unsigned int is used
// -1 will be printed wherever necessary as %d format specifier will be used
// returns the struct with distances and parents of vertices w.r.t source
struct path *Dijkstra(struct graph *G, int n, unsigned int s, int flag){
	int i=0,j=0, m=n;
	unsigned int u, v, d;
	struct path *P = (struct path*)malloc(n*sizeof(struct path));
	struct priorityQ *Q = (struct priorityQ*)malloc(n*sizeof(struct priorityQ));
	struct priorityQ qnode;
	struct list *adju = NULL;
	// intialize priority Q; set distances to ∞ and parents to 0
	for(i=0; i<n; i++){
		Q[i].v = i+1; // vertcies are stored in ascending order in Q nodes
		Q[i].d = -1;
		P[i].d = -1;
		P[i].pi = 0;
	}
	decrease_key(n, Q, s-1, 0);
	for(m=n; m>0; m--){

		qnode = extract_min(m, Q);
		u = qnode.v;
		if(flag == 0) printf("%d %d\n",qnode.v, qnode.d); 
		P[u-1].d = qnode.d;
		adju = G[u-1].adjList;
		for(adju = adju->next; adju!=NULL; adju = adju->next){
			v = adju->v;
			for(j=0; j<m-1; j++){
				if(Q[j].v == v){
					d = Q[j].d;
					P[v - 1].pi = u;
					break;
				}
			}
			if((qnode.d + adju->w) < d){
				d = qnode.d + adju->w;
				decrease_key(m-1, Q, j, d);
			}
		}
	}
	return P;
}

// function to print the shortest path using parents w.r.t Dijkstra of source
void shortest_path(struct path *P, unsigned int dest){
	if(P[dest-1].pi == 0) return;
	shortest_path(P, P[dest-1].pi);
	printf("%d ", dest);
}

// function to free list 
void FreeList(struct list *head){
	struct list* temp;
	while(head!=NULL){
		temp = head;
		head = head->next;
		free(temp);
	}head = NULL;
}

// function to free graph 
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
	struct path *Path;
	struct graph *G = NULL;
	struct priorityQ *Q;
	while((d=fgetc(stdin))!=EOF){
		if(d == 'N'){
			option = 'N';
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
					Path = (struct path*)malloc(V_size*sizeof(struct path));
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
					Path = Dijkstra(G, V_size, u, 1);
					printf("%d %d ", Path[v-1].d, u);
					shortest_path(Path, v);
					printf("\n");
					break;

				case 'D':
					Path = Dijkstra(G, V_size, a,  0);
					break;

				default: break;
			}
			a=0; v=0; u=0; w=0;
		}

		else{
			 a = 10*a + (d - '0');
		}
	}
	return 0;
}