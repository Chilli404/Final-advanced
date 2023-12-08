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

MinHeap * createHeap(int capacity);
void printMinHeap(MinHeap* minHeap);
void insertToHeap(MinHeap* minHeap, int node, int data);
HeapNode* getMin(MinHeap* minHeap);
HeapNode * createHeapNode(int node, int data);
void insertToHeapNode(MinHeap* minHeap, HeapNode * newNode);

HeapNode* buildHuffmanTree(int frequency[], MinHeap * minHeap);
void printCodes(HeapNode* root, int arr[], int top); 
void freeTree(HeapNode* root);


