/******************************************************************************
Sum of two large integers using linked lists. 
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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct node{
	uint8_t digit;
	struct node *next;
	struct node *prev;
};
