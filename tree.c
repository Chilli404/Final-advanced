#include "stuffs.h"

int isLeaf(HeapNode* root) { 
	//checks if current node is a leaf (i.e corresponds to a char)
    	return !(root->left) && !(root->right); 
} 

HeapNode* buildHuffmanTree(int frequency[], MinHeap * minHeap) { 
    	HeapNode *left, *right, *top; 
	
    	//iterate until only root is left
    	while (minHeap->size > 1) { 
  
        	//get two smallest elements 
        	left = getMin(minHeap); 
        	right = getMin(minHeap); 
  
        	//create a new internal node with special character ASCII:129
        	top = createHeapNode(129, left->data + right->data); 
  
		//Store two elements as left and right subtree of new internal node
        	top->left = left; 
        	top->right = right; 

		//insert internal node back to heap  
        	insertToHeapNode(minHeap, top); 
    	} 
	//free(minHeap);  
    	return getMin(minHeap); 
} 
  
void freeTree(HeapNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
} 
