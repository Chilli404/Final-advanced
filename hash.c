#include "stuffs.h"
#define SIZE 128

void insertHash(HashTable* table,  int key, char data[], int len);
void printDict(HashTable * table);
MinHeap *  buildHeap(int frequency[]);

int hashCode(int key) {
   return key % SIZE;
}

// Function to create a dictionary mapping characters to their encoded values
void populate(HeapNode* root, char arr[], int top, HashTable* table) {
    if (root->left) {
        arr[top] = '0';
        populate(root->left, arr, top + 1, table);
    }

    if (root->right) {
        arr[top] = '1';
        populate(root->right, arr, top + 1, table);
    }

    if (isLeaf(root)) {
        // Store the character and its code in the dictionary
        insertHash(table, root->c, arr, top);
    }
}

HashTable * createDict(int frequency[]) {
	HashTable * table = (HashTable *) malloc(sizeof(HashTable)); 
	table->capacity = 128;
	table->size = 0;
	table->array = (hashItem **) malloc(128 * sizeof(hashItem*));

	//printFrequencies(frequency);
	MinHeap * minHeap = buildHeap(frequency);
	HeapNode * root = buildHuffmanTree(frequency, minHeap);
	int arr[128], top = 0; 
	

	char arr2[100];
    	top = 0;	
	populate(root, arr2, top, table);	

	freeTree(root);
	free(minHeap->array);
	free(minHeap);
	return table;
}

void insertHash(HashTable* table, int key, char data[], int len) {
	
   	hashItem *item = (hashItem*) malloc(sizeof(hashItem));
   	item->len = len;  
   	item->key = key;
	for(int i = 0; i < len; i++) {
		item->data[i] = data[i];
	}

	item->data[len] = '\0';	

   	int hashIndex = hashCode(key);
	
	table->array[hashIndex] = item;
	table->size++;
}


void printDict(HashTable * table) {
	hashItem ** arr = table->array;	

   	//Handling printing the special characters
	int special[2] = {10, 13};
	for(int i =0; i < 2; i++) {
		int ind = hashCode(special[i]); 		
      		if(arr[ind] != NULL && i == 0) {
         		printf("'\\n';%s\n", arr[ind]->data);
   		} else if(arr[ind] != NULL && i == 1) {
         		printf("'\\r';%s\n", arr[ind]->data);
      		} else {
         		printf(" ~~ ");
   		}

	}

	//Handling regular characters
	for(int i = 32; i<128; i++) {
		int ind = hashCode(i); 		
      		if(arr[ind] != NULL) {
         		printf("%c;%s\n",arr[ind]->key, arr[ind]->data);
      		} else{
         		printf(" ~~ ");
   		}
	}	
   	printf("\n");
}

MinHeap *  buildHeap(int frequency[]) {
	MinHeap * minHeap = createHeap(128);
	for (int i = 0; i < 128; i++) {
		insertToHeap(minHeap, i, frequency[i]);
	}
	return minHeap;	
}

void freeTable(HashTable* table) {
    // Traverse the array and free each hash item
    for (int i = 0; i < SIZE; i++) {
        if (table->array[i] != NULL) {
            free(table->array[i]);
        }
    }

    // Free the array itself
    free(table->array);

    // Free the hash table structure
    free(table);
}
