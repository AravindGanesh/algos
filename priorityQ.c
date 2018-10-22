#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
// reference: CLRS
void HEAPIFY(int n, int *heap, int i){
	int left_i = 2*i + 1, right_i = 2*i + 2, min_i = i;
	
	if((left_i < n) && (heap[left_i] < heap[min_i])) min_i = left_i;
	
	if((right_i < n) && (heap[right_i] < heap[min_i])) min_i = right_i;
	
	if(min_i != i){
		swap(&heap[i], &heap[min_i]);
		HEAPIFY(n, heap, min_i);
	}
}

int minimum(int *heap){
	return heap[0];
}

// reference: CLRS
int extract_min(int n, int *heap){
	if(n==0) return -1;
	int minVal = heap[0];
	heap[0] = heap[n-1];
	n--;
	HEAPIFY(n, heap, 0);
	return minVal;
}

void decrease_key(int n, int *heap, int i, int key){
	heap[i] = key;
	for(; i!=0 && heap[i] < heap[(i-1)/2]; i=(i-1)/2){
		swap(&heap[i], &heap[(i-1)/2]);
	}
}

int main(){
	printf("enter main\n");
	int Q[] = {1,2,4,5,6,7,8,9};
	int A[] = {9,8,7,6,5,4,2,1};
	HEAPIFY(8,A,0);
	printf("Q is made\n");
	for(int i=0; i<8; i++) printf(" A %d blah  ",A[i]);
	int a = extract_min(8, Q);
	printf("\n%d a \n", a);
	for(int i=0; i<7; i++) printf(" %d blah ",Q[i]);
	printf("\n");
	decrease_key(7, Q, 2, 3);
	printf("\n");
	for(int i=0; i<7; i++) printf(" %d blah ",Q[i]);
	printf("\n");
	
	return 0;
}