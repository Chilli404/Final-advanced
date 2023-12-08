#include "stuffs.h"
void printArr(int arr[], int n) 
{ 
    int i; 
    for (i = 0; i < n; ++i) 
        printf("%d", arr[i]); 
  
    printf("\n"); 
} 
  
int isLeaf(HeapNode* root) 
  
{ 
  
    return !(root->left) && !(root->right); 
} 

HeapNode* buildHuffmanTree(int frequency[], MinHeap * minHeap) { 
    	HeapNode *left, *right, *top; 
	
    	// Iterate while size of heap doesn't become 1 
    	while (minHeap->size > 1) { 
  
        	// Step 2: Extract the two minimum 
        	// freq items from min heap 
        	left = getMin(minHeap); 
        	right = getMin(minHeap); 
  
        	// Step 3:  Create a new internal 
       	 	// node with frequency equal to the 
        	// sum of the two nodes frequencies. 
        	// Make the two extracted node as 
        	// left and right children of this new node. 
        	// Add this node to the min heap 
        	// '$' is a special value for internal nodes, not 
        	// used 
        	top = createHeapNode(129, left->data + right->data); 
  
        	top->left = left; 
        	top->right = right; 
  
        	insertToHeapNode(minHeap, top); 
    	} 
	//free(minHeap);  
    	return getMin(minHeap); 
} 
  
// Prints huffman codes from the root of Huffman Tree. 
// It uses arr[] to store codes 
void printCodes(HeapNode* root, int arr[], int top) { 
  
    // Assign 0 to left edge and recur 
    if (root->left) { 
  
        arr[top] = 0; 
        printCodes(root->left, arr, top + 1); 
    } 
  
    // Assign 1 to right edge and recur 
    if (root->right) { 
  
        arr[top] = 1; 
        printCodes(root->right, arr, top + 1); 
    } 
  
    // If this is a leaf node, then 
    // it contains one of the input 
    // characters, print the character 
    // and its code from arr[] 
    if (isLeaf(root)) { 
  
        printf("%c: ", root->c); 
        printArr(arr, top); 
    } 
}

void freeTree(HeapNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
} 
