#include <stdio.h>
#include <stdlib.h>

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

// remove and returns min value of min-heap
unsigned int extract_min(int n, struct priorityQ *heap){
	if(n==0) return -1;
	int minVal = heap[0].d;
	heap[0].d = heap[n-1].d;
	heap[0].v = heap[n-1].v;
	heap[0].pi = heap[n-1].pi;
	n--;
	HEAPIFY(n, heap, 0);
	return minVal;
}

// decrease the distance of vertex v to value key  
void decrease_key(int n, struct priorityQ *heap, unsigned int v, unsigned int key){
	int i = v-1;
	heap[i].d = key;
	// restore min-heap property to the array
	for(i; i && heap[i].d < heap[(i-1)/2].d; i=(i-1)/2){
		swap(&heap[i], &heap[(i-1)/2]);
	}
}

int main(){
	// unsigned int Q[8] = {1,2,4,5,6,7,8,9};
	struct priorityQ A[8];
	printf("enter main\n");
	int i;
	for(i=0; i<8; i++){
		A[i].d = i+2;
		A[i].v = i+1;
		A[i].pi = 0;
	}
	// int A[] = {9,8,7,6,5,4,2,1};
	HEAPIFY(8,A,0);
	printf("Q is made\n");
	for(int i=0; i<8; i++) printf(" A d=%d, v=%d ",A[i].d, A[i].v);
	int a = extract_min(8, A);
	printf("\n%d a \n", a);
	for(int i=0; i<7; i++) printf(" %d blah ",A[i].d);
	printf("\n");
	decrease_key(7, A, 2, 1);
	printf("\n");
	for(int i=0; i<7; i++) printf(" %d blah ",A[i].d);
	printf("\n");
	
	return 0;
}