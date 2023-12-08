#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HeapNode HeapNode;
struct HeapNode {
    int c;
    int data;  
    struct HeapNode* left;
    struct HeapNode * right;
};

typedef struct {
    HeapNode** array;
    int capacity;         
    int size;            
} MinHeap;

typedef struct {
   	char data[100];
	char len;   
  	int key;
}hashItem;

typedef struct {
	int capacity;
	int size;
	hashItem ** array;
} HashTable;

//heap.c functions
MinHeap * createHeap(int capacity);
void printMinHeap(MinHeap* minHeap);
void insertToHeap(MinHeap* minHeap, int node, int data);
HeapNode* getMin(MinHeap* minHeap);
HeapNode * createHeapNode(int node, int data);
void insertToHeapNode(MinHeap* minHeap, HeapNode * newNode);

//tree.c functions
HeapNode* buildHuffmanTree(int frequency[], MinHeap * minHeap);
void printCodes(HeapNode* root, int arr[], int top); 
void freeTree(HeapNode* root);
int isLeaf(HeapNode* root);
 
//hash.c functions
HashTable * createDict(int frequency[]);
void freeTable(HashTable* table);

