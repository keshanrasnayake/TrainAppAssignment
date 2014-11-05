#define _CRT_SECURE_NO_WARNINGS //Needed in vs to disable deprecation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>



int infin = INT_MAX;
typedef struct node Node; //Synonyms Definition
typedef Node *NodePtr;
typedef struct priorityqueue Priorityqueue;
typedef struct edge Edge;
typedef Edge *EdgePtr;
//Define Node structure in adjacency list

struct node{
	char name[30];
	int dist;
	char parent[30];
	int upper_bound;
	struct edge *edges[4];
	char color;//w for white, g for gray, b for black
	struct node *next;
	struct node *parentn;
};
struct edge{
	int weight;
	char track;
	struct node *adj;
};
void createnode(char *namePtr, NodePtr *Ptr);
void joinnode(char *node1name, char *node2name, int weight, char track, Node *Ptr);
void Dijikstra(char tart[3], char end[30]);
void initialize();
void relax();

void main(){
	printf("%d", infin);

	NodePtr startPtr = NULL;
	char city_name[30];
	char city1[30];
	char city2[30];
	char line[5];
	int dist;

	char *city1Prt;
	char *city2Ptr;
	char *namePtr;
	char *linePtr;
	getchar();
}

void createnode(char *namePtr, NodePtr *Ptr){
	NodePtr currentPtr;
	NodePtr previousPtr;
	NodePtr newPtr;
	newPtr = malloc(sizeof(Node));
	if (newPtr != NULL){
		strcpy(newPtr->name, namePtr);
		newPtr->next = NULL;
		newPtr->upper_bound = infin;

		previousPtr = NULL;
		currentPtr = *Ptr;

		while (currentPtr != NULL){
			previousPtr = currentPtr;
			currentPtr = currentPtr->next;
		}

		if (previousPtr == NULL){
			*Ptr = newPtr;
		}

		else{
			currentPtr = newPtr;
		}
	}
	else
	{
		printf("Not enough memory available. ");
	}
}

void joinnode(char *node1name, char *node2name, int weight, char track, Node *Ptr){
	
	EdgePtr  newPath;
	newPath = malloc(sizeof(Edge));
	NodePtr currentPtr = Ptr;
	NodePtr previousPtr = NULL;
	NodePtr node1;
	NodePtr node2;
	while (currentPtr != NULL && strcmp(currentPtr->name, node1name)){
		previousPtr = currentPtr;
		currentPtr = currentPtr->next;
	}
	if (previousPtr == NULL){
		printf("No available nodes. Please add first.");
	}
	else{
		if (currentPtr == NULL){
			printf("Node not found. Check again.");
		}
		
		else{
			node1 = currentPtr;
			currentPtr = Ptr;
			previousPtr = NULL;
			while (currentPtr != NULL && strcmp(currentPtr->name, node2name)){
				previousPtr = currentPtr;
				currentPtr = currentPtr->next;
			}
			if (currentPtr == NULL){
				printf("Node not found. Check again.");
			}
			else{
				node2 = currentPtr;


			}
		}
	}
}
