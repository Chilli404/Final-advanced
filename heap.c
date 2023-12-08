#include "stuffs.h"
int viewMin(MinHeap * minHeap);

unsigned concatenate(unsigned x, unsigned y) {
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
}

void swapNodes(HeapNode** a, HeapNode** b) {
    HeapNode* temp = *a;
    *a = *b;
    *b = temp;
}


void heapify(MinHeap * minHeap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < minHeap->size && minHeap->array[left]->data < minHeap->array[smallest]->data)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->data < minHeap->array[smallest]->data)
        smallest = right;

    if (smallest != index) {
        swapNodes(&minHeap->array[index], &minHeap->array[smallest]);
        heapify(minHeap, smallest);
    }
}


MinHeap * createHeap(int capacity) {
    MinHeap * heap = (MinHeap *) malloc(sizeof(MinHeap));
    heap->array = (HeapNode **) malloc(capacity * sizeof(HeapNode *));
    heap->capacity = capacity;
    heap->size = 0;
    
    return heap;
}

HeapNode * createHeapNode(int node, int data) {
    struct HeapNode* newNode = (HeapNode *) malloc(sizeof(HeapNode));
    newNode->data = data;
    newNode->c = node;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insertToHeap(MinHeap* minHeap, int node, int data) {
    if (minHeap->size == minHeap->capacity) {
        printf("Heap is full. Cannot insert more elements.\n");
        return;
    }
    
    HeapNode * newNode = createHeapNode(node,data);

    int i = minHeap->size;
    minHeap->array[i] = newNode;
    minHeap->size++;
    
    while (i != 0 && minHeap->array[(i - 1) / 2]->data > minHeap->array[i]->data) {
        swapNodes(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void insertToHeapNode(MinHeap* minHeap, HeapNode * newNode) {
    if (minHeap->size == minHeap->capacity) {
        printf("Heap is full. Cannot insert more elements.\n");
        return;
    }

    int i = minHeap->size;
    minHeap->array[i] = newNode;
    minHeap->size++;
    
    while (i != 0 && minHeap->array[(i - 1) / 2]->data > minHeap->array[i]->data) {
        swapNodes(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}


HeapNode* getMin(MinHeap* minHeap) {
    if (minHeap->size == 0)
        return NULL;
    HeapNode* root = minHeap->array[0];
    
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;

    heapify(minHeap, 0);

    return root;
}

int viewMin(MinHeap * minHeap) {
    HeapNode* root = minHeap->array[0];
    return root->data;
}

void printMinHeap(MinHeap* minHeap) {
    printf("Min-Heap: ");
    for (int i = 0; i < minHeap->size; i++)
        printf("%d ", minHeap->array[i]->data);
    printf("\n");
}
