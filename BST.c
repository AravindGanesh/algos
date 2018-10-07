/******************************************************************************
Binary Search Tree 
Input Format
Each line of the input starts with one of the symbols:
• ‘N’ (stands for new set)
• ‘+’ (Add element to set)
• ‘>’ (Find successor)
• ‘–’ (Delete element)
• ‘S’ (search within most recent set)
• ‘P’ (pre-order traversal)
• 'C' print children
• 'U' print uncle
• 'B' build BST from preorder traversal
• 'L' left rotate
• 'R' Right rotate
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdint.h>

// Node of a BST
struct node{
	uint64_t n; // long natural number
	struct node* left;
	struct node* right;
	struct node* parent;
};

// insert a natural number into a Binary Search Tree
struct node *insert(struct node* root, uint64_t x){
	// Inputs: pointer to the root node of BST and value to be inserted
	// Output: returns pointer to the root node of BST with x inserted
	struct node* temp = root;
	struct node* branch = (struct node*)malloc(sizeof(struct node));
	// if the tree is empty
	if(temp == NULL){
		branch->n = x; 
		branch->right = branch->left = NULL;
		branch->parent = NULL;
		temp = branch;
		return temp;
	}
	// recursively insert into a BST
	// here, temp is the root of the sub-tree since it's recursion
	else {
		if(x < temp->n){
			branch = insert(temp->left, x);
			// make the new node as left branch of the root
			temp->left = branch; 
			// parent pointer of the branch points to the root 
			branch->parent = temp;
		}
		else if(x > temp->n){ 
			branch = insert(temp->right, x);
			// make the new node as right branch of the root
			temp->right = branch;
			// parent pointer of the branch points to the root 
			branch->parent = temp; 		
		}
	}
	return temp;
}

// search for an element in a BST
void search(struct node *root, uint64_t x){
	// INPUTS: Pointer to the root node of the BST and the element to be searched
	// OUTPUTS: Prints a binary string - path from root to node containing x,
	// -1 in case x is not present in the tree 
	struct node *temp = root;
	int *path = (int*)malloc(sizeof(int)); // array with 0s and 1s
	int i = 0, j=0;
	// if x is not present, the temp pointer goes to NULL in the above loop
	if(temp == NULL){
		printf("-1\n");
		return;
	}
	// search for the element 
	while(temp != NULL && temp->n != x){	
		if(x > temp->n){
			temp = temp->right;
			path[i] = 1; 
		}
		else if(x < temp->n){
			temp = temp->left;
			path[i] = 0;
		}
		i++;	
	}
	// if x is present, print the path
	for(j=0; j<i; j++) printf("%d", path[j]);
	return;	
}

// minimum value in a branch (sub-tree)
struct node *tree_min(struct node* branch){
	// returns the pointer to the node containing min value in a branch
	// the left-most leaf is the minimum value
	while(branch->left !=NULL) branch = branch->left;
	return branch;
}

// recursive preorder traversal
void PreOrder(struct node* root){
	struct node* temp= root;

	if(temp == NULL) return;
	
	printf("%lu ", temp->n);
	PreOrder(temp->left);
	PreOrder(temp->right);
	return;
}

// for reference, not asked in the assignment
void InOrder(struct node* root){
	struct node* temp= root;
	
	if(temp == NULL) return;
	
	InOrder(temp->left);
	printf("%lu ", temp->n);
	InOrder(temp->right);
	return;
}

// reference CLRS - modified for case, x not in tree
struct node *successor(struct node* root, uint64_t x){
	// Inputs: pointer to the root node of the tree and 
	// number for which successor needs to be returned
	// Returns the pointer to the node with successor of x
	// NULL if x is the largest or larger than all the elements in the tree
	struct node *branch = root;
	// search for x in the tree to see if it is the tree or not
	struct node *x_node = root;
	while(x_node != NULL && x_node->n != x){
		if(x > x_node->n) x_node = x_node->right;
		else if(x < x_node->n) x_node = x_node->left;
	} // after the loop, x_node becomes the pointer to the node with x
	// otherwise, x_node points to NULL
	// x is inserted at the leaf node if not present in the tree  
	if(x_node == NULL) branch = insert(root, x);
	
	struct node *temp_x = (struct node*)malloc(sizeof(struct node));
	
	while(1){ // traverse the tree to get node with x
		if(x < branch->n) branch = branch->left;
		else if(x > branch->n) branch = branch->right;
		else if(x == branch->n) break;
	} // branch is the pointer to the node with x

	if(x_node == NULL) temp_x = branch; // to delete the inserted x later

	// if the right sub-tree is not NULL,
	// successor is the left-most value (min value) in the right sub-tree 
	if(branch->right != NULL) return tree_min(branch->right);

	// if right sub-tree is NULL
	// find the nearest ancestor such that node is left sub-tree
	struct node *P = branch->parent;
	while(P != NULL && branch == P->right){
		branch = P;
		P = P->parent;
	}
	// since, inserted x is a leaf, no need to use delete function
	if(x_node == NULL){ // if x is inserted,
		struct node *temp = temp_x->parent; // parent pointer
		if(temp->left == temp_x){ // if x is a left child 
			temp->left = NULL; // make left child of the parent to NULL
			free(temp_x); // free the inserted node
		}
		if(temp->right == temp_x){ // if x is a right child
			temp->right = NULL; // make right child of the parent to NULL
			free(temp_x); // free the inserted node
		}
	}
	return P;
}

// Function to delete x from a BST
struct node *delete(struct node *root, uint64_t x){
	// INPUTS: pointer to the root node of the tree and the element to be deleted x
	// OUTPUT: returns the root pointer of the tree with x deleted
	struct node *temp = root;
	// trivial case
	if(temp == NULL) return root; // if the root is NULL, nothing to delete

	struct node *x_node = root; 
	while(x_node != NULL && x_node->n != x){
		if(x_node != NULL){
			if(x > x_node->n) x_node = x_node->right;
			else if(x < x_node->n) x_node = x_node->left;
		} 
	} // get node with x 

	if(x_node == NULL) return root;
	
	// case 0: no children, trivial 
	if(x_node->right == NULL && x_node->left == NULL){
		struct node *P = x_node->parent; // parent pointer to x
		if(P->left == x_node){ // if x is left child
			P->left = NULL; // make left child of parent NULL
			free(x_node); // free the node
		}
		if(P->right == x_node){ // if x is right child
			P->right = NULL; // make right child of parent NULL
			free(x_node); // free the node
		}
		return temp;
	}
	// case 1 (L): only left child
	else if(x_node->right == NULL){ 
		struct node *P = x_node->parent; // parent pointer to x
		if(P->left == x_node){ // if x is left child
			P->left = x_node->left; // make left child of x as left child of parent
			free(x_node); // free the node
		}
		if(P->right == x_node){ // if x is right child
			P->right = x_node->left; // make left child of x as right child of parent
			free(x_node); // free the node
		}
		// return here to use for splicing the successor later
		return temp; 
	}
	// case 1 (R): only right child
	else if(x_node->left == NULL){ 
		struct node *P = x_node->parent; // parent pointer to x
		if(P->left == x_node){ // if x is left child
			P->left = x_node->right; // make right child of x as left child of parent
			free(x_node);// free the node
		}
		if(P->right == x_node){// if x is right child
			P->right = x_node->right;// make right child of x as right child of parent
			free(x_node);// free the node
		}
		return temp;
	}
	// case 2: the node has two children
	else{
		// replace the node with it's successor and splice the successor
		struct node *succ = successor(root, x);
		uint64_t temp_succ = succ->n;
		temp = delete(temp, temp_succ); 
		x_node->n = temp_succ; // replace the value with its successor
		return temp;
	}
}

void children(struct node *root, uint64_t x){
	struct node *temp = root;
	while(temp != NULL && temp->n != x){
		if(x > temp->n) temp = temp->right;
		else if(x < temp->n) temp = temp->left;
	}

	if(temp == NULL){
		printf("-1\n");
		return;
	}

	if(temp->left == NULL) printf("Nil ");
	else printf("%lu ", temp->left->n);

	if(temp->right == NULL) printf("Nil\n");
	else printf("%lu\n", temp->right->n);

	return;
}

struct node *uncle(struct node *root, uint64_t x){
	struct node *x_node = root;

	if(x_node == NULL) return NULL;

	while(x_node != NULL && x_node->n != x){
		if(x_node != NULL){
			if(x > x_node->n) x_node = x_node->right;
			else if(x < x_node->n) x_node = x_node->left;
		} 
	} // get node with x 

	if(x_node == NULL) return x_node;

	struct node *temp_p = x_node->parent;
	if(temp_p == NULL) return temp_p;
	if(temp_p->parent == NULL) return temp_p->parent;
	x_node = temp_p; // parent
	temp_p = temp_p->parent; // grand parent
	if(temp_p->left == x_node) return temp_p->right;
	if(temp_p->right == x_node) return temp_p->left;
}


void free_tree(struct node *root){
	if(root == NULL) return;
	free_tree(root->left);
	free_tree(root->right);
	free(root);
}



// handle inputs and outputs
void do_stuff(struct node *root){
	struct node *tree = root;
	char c, num;
	char *line = (char*)malloc(sizeof(char));
	int i=0, j=0;
	for(i=0; (c=fgetc(stdin))!='\n'; i++) line[i] = c;
	uint64_t a=0;
	uint64_t X=0;

	// printf("%s\n", line);
	// do_stuff();
	switch(line[0]){
		case 'N':
			free_tree(tree);
			tree = NULL;
			for(j=1; j<i; j++){
				if(line[j] == ' '){
					if(a!=0) tree = insert(tree, a);
					a = 0; // since only natural numbers are used
				}
				else a = 10*a + (line[j] - '0');
			}
			if(a!=0)tree = insert(tree, a);
			do_stuff(tree); // recursively call for each line
			break;

		case 'S':
			for(j=1; j<i; j++){
				if(line[j] == ' ') continue;
				X = X*10 + (line[j] - '0');
			}
			search(tree, X)
		;	printf("\n");
			do_stuff(tree);
			break;

		case 'P':
			PreOrder(tree);
			printf("\n");
			do_stuff(tree);
			break;

		case '+':
			for(j=1; j<i; j++){
				if(line[j] == ' ') continue;
				X = X*10 + (line[j] - '0');
			}
			tree = insert(tree, X);
			do_stuff(tree);
			break;

		case '>':
			for(j=1; j<i; j++){
				if(line[j] == ' ') continue;
				X = X*10 + (line[j] - '0');
			}
			struct node *succ = successor(tree, X);
			if(succ != NULL) printf("%lu\n", succ->n);
			else printf("-1\n");
			do_stuff(tree);
			break;

		case '-':
			for(j=1; j<i; j++){
				if(line[j] == ' ') continue;
				X = X*10 + (line[j] - '0');
			}
			tree = delete(tree, X);
			do_stuff(tree);
			break;

		case 'C':
			for(j=1; j<i; j++){
				if(line[j] == ' ') continue;
				X = X*10 + (line[j] - '0');
			}children(tree, X);
			do_stuff(tree);

		case 'U':
			for(j=1; j<i; j++){
				if(line[j] == ' ') continue;
				X = X*10 + (line[j] - '0');
			}
			struct node *uncl = uncle(tree, X);
			if(uncl != NULL) printf("%lu\n", uncl->n);
			else printf("-1\n");
			do_stuff(tree);
	
		default: break;
	}


}

int main(){
	struct node *TREE;
	do_stuff(TREE);
	return 0;
}