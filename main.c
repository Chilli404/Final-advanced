#include "stuffs.h"

int computeFrequency(const char * filename, int frequency[]);
void resetFrequency(int frequency[]);
MinHeap *  buildHeap(int frequency[]);
void encodeFile(const char * filename, HashTable * dict);
void decodeFile(const char * filename, HeapNode * root);

int main() {
	//Initialization Vars
	char command[20];
	int haveScheme = 0;
	int frequency[128] = {0};
	char currFile[10];

	//Compression Tree
	HeapNode * root = NULL;
	//Dictionary of Bits
	HashTable * table = NULL;


	//Welcome Text
	printf("\n$$$$$$$$\\ $$\\ $$\\                  $$$$$$\\                                                                                               \n");
    	printf("$$  _____|\\__|$$ |                $$  __$$\\                                                                                              \n");
   	 printf("$$ |      $$\\ $$ | $$$$$$\\        $$ /  \\__| $$$$$$\\  $$$$$$\\$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$$\\  $$$$$$$\\  $$$$$$\\   $$$$$$\\  \n");
   	 printf("$$$$$\\    $$ |$$ |$$  __$$\\       $$ |      $$  __$$\\ $$  _$$  _$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  _____|$$  _____|$$  __$$\\ $$  __$$\\ \n");
    	printf("$$  __|   $$ |$$ |$$$$$$$$ |      $$ |      $$ /  $$ |$$ / $$ / $$ |$$ /  $$ |$$ |  \\__|$$$$$$$$ |\\$$$$$$\\  \\$$$$$$\\  $$ /  $$ |$$ |  \\__|\n");
    	printf("$$ |      $$ |$$ |$$   ____|      $$ |  $$\\ $$ |  $$ |$$ | $$ | $$ |$$ |  $$ |$$ |      $$   ____| \\____$$\\  \\____$$\\ $$ |  $$ |$$ |      \n");
    	printf("$$        $$ |$$ |\\$$$$$$$\\       \\$$$$$$  |\\$$$$$$  |$$ | $$ | $$ |$$$$$$$  |$$ |      \\$$$$$$$\\ $$$$$$$  |$$$$$$$  |\\$$$$$$  |$$ |      \n");
    	printf("\\__|      \\__|\\__| \\_______|       \\______/  \\______/ \\__| \\__| \\__|$$  ____/ \\__|       \\_______|\\_______/ \\_______/  \\______/ \\__|      \n");
    printf("                                                                    $$ |                                                                 \n");
    printf("                                                                    $$ |                                                                 \n");
    printf("                                                                    \\__|                                                                 \n");	
	printf("Type \"help\" for help");
	
	//Command Input Parser
	while (1) {
  		printf("$ ");
    		scanf("%s", command);
		if (strcmp(command, "import") == 0) {
			//Get Filename
			char filename[100];
		    	scanf("%s", filename);
			int ret_value = computeFrequency(filename, frequency);
			
			//if no errors in computing frequency
			if (ret_value == 0) {	
		    		//Free existing memory if populated
				if (table != NULL) freeTable(table);	
		    		if (root != NULL) freeTree(root);
				
				//Build Heap From frequency array and the Build Tree
				MinHeap * minHeap = buildHeap(frequency);
				root = buildHuffmanTree(frequency, minHeap);

				//Create Dictionary and free unused data
				table = createDict(root);
				haveScheme = 1;
				printf("Sucessfully Imported %s\n", filename);
				free(minHeap->array);
				free(minHeap);
			}else {
				printf("Deleting retained frquencies\n");
				resetFrequency(frequency);
			}
		} else if (strcmp(command, "encode") == 0) {
			//Get Filename
			char filename[100];
		    	scanf("%s", filename);

			if (haveScheme == 1) {
				encodeFile(filename, table);
			}else {
				printf("Error: No scheme in program. Have you imported a file yet?\n");
			}
		} else if (strcmp(command, "decode") == 0) {    
			//Get Filename
			char filename[100];
		    	scanf("%s", filename);

			if (haveScheme == 1) {
				decodeFile(filename, root);
			}else {
				printf("Error: No scheme in program. Have you imported a file yet?\n");
			}

		} else if (strcmp(command, "dump") == 0) {
		    	if(table != NULL) {
				printf("Dumping dictionary:\n");
				printDict(table);
			}else {
				printf("Error: No Dictionary Loaded\n");
			}

		} else if (strcmp(command, "help") == 0) {
			printf("Available Commands:\n");
			printf("	import <filename> : imports a file as a base for the compresion scheme\n");	
			printf("	encode <filename> : encodes a file using the exisitng compression scheme (if it exists)\n");
			printf("	decode <filename> : decodes an already encoded file using the existing compression scheme\n");	
			printf("	dump              : outputs the compression scheme\n");
			printf("	help              : prints the help menu\n");
			printf("	quit              : quits the program\n");
		} else if (strcmp(command, "quit") == 0) {
			if(table != NULL) {
				freeTable(table);
			}
			if(root != NULL) {
				freeTree(root);
			}
			break; 
		}else {
		    	printf("Invalid command. Please try again.\n");
		}
    	}
	printf("\n$$$$$$$$\\ $$\\                           $$\\             $$\\     $$\\\n");                   
	printf("\\__$$  __|$$ |                          $$ |            \\$$\\   $$  |\n");                   
	printf("   $$ |   $$$$$$$\\   $$$$$$\\  $$$$$$$\\  $$ |  $$\\        \\$$\\ $$  /$$$$$$\\  $$\\   $$\\\n");  
	printf("   $$ |   $$  __$$\\  \\____$$\\ $$  __$$\\ $$ | $$  |        \\$$$$  /$$  __$$\\ $$ |  $$ |\n"); 
	printf("   $$ |   $$ |  $$ | $$$$$$$ |$$ |  $$ |$$$$$$  /          \\$$  / $$ /  $$ |$$ |  $$ |\n"); 
	printf("   $$ |   $$ |  $$ |$$  __$$ |$$ |  $$ |$$  _$$<            $$ |  $$ |  $$ |$$ |  $$ |\n"); 
	printf("   $$ |   $$ |  $$ |\\$$$$$$$ |$$ |  $$ |$$ | \\$$\\           $$ |  \\$$$$$$  |\\$$$$$$  |\n"); 
	printf("   \\__|   \\__|  \\__| \\_______|\\__|  \\__|\\__|  \\__|          \\__|   \\______/  \\______/\n"); 	

    	return 0;
}

int computeFrequency(const char * filename, int frequency[]) {
	FILE *file = fopen(filename, "r");

    	if (file == NULL) {
        	printf("Error opening file %s\n", filename);
        	return 1;
    	}

	//Loop through file and populate frequency array
    	int c;
    	while ((c = fgetc(file)) != EOF) {
        	if (c >= 0 && c <= 127) {
            		frequency[c]++;
       	 	}else {
			printf("Error: Encountered Unknown Character, ASCII: %d\n", (int) c);
		}
    	}

    	fclose(file);
	return 0;	
}

void printFrequencies(int frequency[]) {
	//Debug Frequency Array
	printf("Character frequencies in file:\n");
    	for (int i = 0; i < 128; ++i) {
        	if (frequency[i] > 0) {
            		printf("\"%c\", %d\n", (char)i, frequency[i]);
        	}
    	}	
}

void resetFrequency(int frequency[]) {
	for (int i = 0; i < 128; ++i) {
        	frequency[i] = 0;
    	}
}

MinHeap *  buildHeap(int frequency[]) {
	//Initialzie heap with 128 nodes
	MinHeap * minHeap = createHeap(128);
	for (int i = 0; i < 128; i++) {
		//insert character and frequency to heap
		insertToHeap(minHeap, i, frequency[i]);
	}
	return minHeap;	
}

	
void encodeFile(const char * filename, HashTable * dict) {
	FILE * file = fopen(filename, "r");
	
	//Check if file exists
	if (file == NULL) {
        	printf("Error opening file %s\n", filename);
        	return;
    	}
	
	char c;
	int bits = 0;

	//iterate through characters in file
    	while ((c = fgetc(file)) != EOF) {
        	// Check if character is valid
		if ((int) c > 127) {
			printf("Encountered Unknown Character \'%c\'\nStopping encoding ...", c);
			return;
		}        

		//find character in dictionary
		int index = hashCode(c);
		hashItem * item = dict->array[index];
		
		//Update bits and print encoding
		bits += item->len;
            	printf("%s", item->data);
        
    	}

    	fclose(file);
    	printf("\nNumber of bits: %d\n", bits);
	
}

void decodeFile(const char * filename, HeapNode* root) {
    	FILE* file = fopen(filename, "r");
	//Check if file exists
    	if (file == NULL) {
        	printf("Error opening file %s\n", filename);
        	return;
    	}


    	HeapNode* current = root;
    	int bit;
	
	//iterate through file by charcaters
    	while ((bit = fgetc(file)) != EOF) {
        	if (bit == '0') {
            		current = current->left;
        	} else if (bit == '1') {
            		current = current->right;
        	}

        	// Check if we reached a leaf node
        	if (isLeaf(current)) {
            		printf("%c", current->c);
            		current = root; // Reset to the root for the next character
        	}
    	}

    fclose(file);
}

