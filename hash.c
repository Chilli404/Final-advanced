#include "stuffs.h"
#define SIZE 128

void insertHash(HashTable* table,  int key, char data[], int len);
void printDict(HashTable * table);
MinHeap *  buildHeap(int frequency[]);

//Hashing algo
int hashCode(int key) {
   	return key % SIZE;
}

// Function to create a dictionary mapping characters to their encoded values
void populate(HeapNode* root, char arr[], int top, HashTable* table) {
	//Popualate left subtree
	if (root->left) {
		arr[top] = '0';
		populate(root->left, arr, top + 1, table);
	}

	//Populate right subtree
	if (root->right) {
		arr[top] = '1';
		populate(root->right, arr, top + 1, table);
	}

	if (isLeaf(root)) {
		// Store the character and code in the hash table
		insertHash(table, root->c, arr, top);
	}
}

HashTable * createDict(HeapNode * root) {
	HashTable * table = (HashTable *) malloc(sizeof(HashTable)); 
	table->capacity = 128;
	table->size = 0;
	table->array = (hashItem **) malloc(128 * sizeof(hashItem*));

	char arr[100];
    	int top = 0;	
	populate(root, arr, top, table);	

	return table;
}

void insertHash(HashTable* table, int key, char data[], int len) {
	//Create corresponding item
   	hashItem *item = (hashItem*) malloc(sizeof(hashItem));
   	item->len = len;  
   	item->key = key;

	//Populate item with bit data
	for(int i = 0; i < len; i++) {
		item->data[i] = data[i];
	}

	//Termination char
	item->data[len] = '\0';	

	//Get current item index
   	int hashIndex = hashCode(key);
	
	//Popualte hashtable with item
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
}


void freeTable(HashTable* table) {
	for (int i = 0; i < SIZE; i++) {
        	if (table->array[i] != NULL) {
            		free(table->array[i]);
        	}
    	}

    	free(table->array);

    	free(table);
}
