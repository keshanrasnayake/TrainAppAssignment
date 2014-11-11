#define _CRT_SECURE_NO_WARNINGS //Needed in vs to disable deprecation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int infin = INT_MAX;
typedef struct node Node; //Synonyms Definition
typedef Node *NodePtr;
typedef struct edge Edge;
typedef Edge *EdgePtr;
//Define Node structure in adjacency list

struct node{
	char name[30];
	int dist;
	char parent[30];
	int upper_bound;
	struct edge *edges[4];
	char color;//w for white, b for black
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
void Dijkstra(NodePtr Ptr, char *start, char *end);
void initialize(NodePtr Ptr, NodePtr start);
void relax(NodePtr currentNode, EdgePtr Edge);
NodePtr extract_lowbound(NodePtr Ptr);
void tracepath(NodePtr Start, NodePtr End, NodePtr Ptr);

void main(){
	printf("%d", infin);

	NodePtr Start = NULL;

	createnode("Dejvicka", &Start);
	createnode("Namesti Republiky", &Start);
	createnode("Hradcanska", &Start);
	createnode("Malostranska", &Start);

	joinnode("Dejvicka", "Hradcanska", 1, 'A', &Start);
	joinnode("Hradcanska", "Malostranska", 2, 'A', &Start);
	Dijkstra(&Start, "Dejvicka", "Hradcanska");

	/*NodePtr nodes = locate(&Start, "Dejvicka");
	char name[30];
	strcpy(name,nodes->name) ;
	printf("%s", locate(&Start, "Dejvicka"));*/
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
		newPtr->parentn = NULL;
		newPtr->color = 'w';
		for (int i = 0; i < 4; i++){
			newPtr->edges[i] = NULL;
		}
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
			previousPtr->next = newPtr;
		}
		printf("Node successfully added. \n");
	}
	else
	{
		printf("Not enough memory available. ");
	}
}

void joinnode(char *node1name, char *node2name, int *weight, char *track, NodePtr *Ptr) {

	EdgePtr  leftPath;
	leftPath = malloc(sizeof(Edge));
	EdgePtr rightPath;
	rightPath = malloc(sizeof(Edge));
	leftPath->track = track;
	leftPath->weight = weight;
	rightPath->weight = weight;
	rightPath->track = track;
	NodePtr currentPtr = *Ptr;
	NodePtr previousPtr = NULL;
	NodePtr node1;
	NodePtr node2;


	while (currentPtr != NULL && strcmp(currentPtr->name, node1name)){
		previousPtr = currentPtr;
		currentPtr = currentPtr->next;
	}
	if (strcmp(currentPtr->name, node1name) != 0 && previousPtr == NULL){
		printf("No available nodes. Please add first.");
	}
	else{
		if (currentPtr == NULL){
			printf("Node not found. Check again.");
		}

		else{
			node1 = currentPtr;
			currentPtr = *Ptr;
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
				for (int i = 0; i < 4; i++){
					if (node1->edges[i] == NULL){
						node1->edges[i] = leftPath;
						leftPath->adj = node2;
						break;

					}
				}
				for (int i = 0; i < 4; i++){
					if (node2->edges[i] == NULL){
						node2->edges[i] = rightPath;
						rightPath->adj = node1;
						break;
					}
				}
				printf("Nodes successfully joined.\n");
			}
		}
	}
}

NodePtr locate(NodePtr *Ptr, char Node){
	NodePtr currentPtr = *Ptr;
	NodePtr previousPtr = NULL;

	while (currentPtr != NULL && strcmp(Node, currentPtr->name) != 0){
		previousPtr = currentPtr;
		currentPtr = currentPtr->next;
	}
	return currentPtr;
}


void initialize(NodePtr *Ptr, NodePtr start){
	NodePtr currentPtr = *Ptr;
	NodePtr previousPtr = NULL;

	while (currentPtr != NULL){
		currentPtr->color = 'w';
		currentPtr->upper_bound = INT_MAX;
		strcpy(currentPtr->parent, "NONE");
		currentPtr->parentn = NULL;
		previousPtr = currentPtr;
		currentPtr = currentPtr->next;
	}

	start->upper_bound = 0;
	start->parentn = NULL;
	strcpy(start->parent, "NONE");
}

void relax(NodePtr currentNode, EdgePtr Edge){
	NodePtr adjacentNode = Edge->adj;
	int proposed_weight = currentNode->upper_bound + Edge->weight;
	int current_weight = adjacentNode->upper_bound;
	if (current_weight > proposed_weight){
		current_weight = proposed_weight;
		adjacentNode->upper_bound = current_weight;
		adjacentNode->parentn = currentNode;
		strcpy(adjacentNode->parent, currentNode->name);
		printf("Relaxed %s node with weight %d\n", adjacentNode->name, current_weight);
	}

}

NodePtr extract_lowbound(NodePtr *Ptr){
	NodePtr currentPtr = *Ptr;
	NodePtr previousPtr = NULL;
	NodePtr minNode = NULL;

	int min = INT_MAX;

	while (currentPtr != NULL){
		if (currentPtr->upper_bound < min && currentPtr->color == 'w'){
			min = currentPtr->upper_bound;
			minNode = currentPtr;
		}
		currentPtr = currentPtr->next;
	}

	return minNode;
}

void Dijkstra(NodePtr *Ptr, char *start, char *end){
	NodePtr currentPtr;
	currentPtr = *Ptr;
	NodePtr previousPtr;
	previousPtr = NULL;

	while (currentPtr != NULL && strcmp(currentPtr->name, start) != 0) {
		previousPtr = currentPtr;
		currentPtr = currentPtr->next;
	}
	NodePtr startPtr = currentPtr;
	initialize(Ptr, startPtr);
	NodePtr checkNode = extract_lowbound(Ptr);
	while (checkNode != NULL && (strcmp(end, checkNode->name) != 0)){
		checkNode = extract_lowbound(Ptr);
		checkNode->color = 'b';
		for (int i = 0; i < 4; i++){
			if (checkNode->edges[i] != NULL){
				EdgePtr checkEdge = checkNode->edges[i];
				relax(checkNode, checkEdge);
			}
		}
	}
	printf("successful\n");
}


void tracePath(NodePtr *Ptr, char * start, char *end){
	NodePtr endNode = locate(Ptr, end);
	Dijkstra(Ptr, start, end);
	NodePtr currentPtr = endNode;
	while (currentPtr != NULL && strcmp(currentPtr->name, start) != 0){
		printf("%s", currentPtr->name);
		currentPtr = currentPtr->next;
	}
	printf("%s", currentPtr->name);
}
