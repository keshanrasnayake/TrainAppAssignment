#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#  define INT_MAX   2147483647
int infin = INT_MAX;

typedef struct node Node; //Synonyms Definition
typedef Node *NodePtr;
typedef struct priorityqueue Priorityqueue;



//Define Node structure in adjacency list
struct node{
	char name[30];
	int dist;
	char parent[30];
	int upper_bound;
	struct edge *edges[4];
	char color;//w for white, g for gray, b for black
	struct node *next;
	struct node *parent;
};

struct edge{
	int weight;
	char track;
	struct node *adj;
};


void createnode(char name[30], NodePtr *Ptr);
void joinnode(char node1[30], char node2[30], int weight, char track);
void Dijiktra(char tart[3], char end[30]);
void initialize();
void relax();

void main(){
	printf("%d", infin);
	getchar();
}

void createnode(char name[30], NodePtr *Ptr){
	NodePtr currentPtr;
	NodePtr previousPtr;
	NodePtr nextPtr;

	currentPtr = malloc(sizeof(Node));

	if (currentPtr != NULL){}
	else{
		printf("Not enough memory available. ");
	}

}