#include "stuffs.h"
int compute_frequency(const char * filename, int frequency[]);
void printFrequencies(int frequency[]);
MinHeap* buildTree(int frequency[]); 
void resetFrequency(int frequency[]);


int main() {
	char command[20];
  	//Command Line Functionality 
	int calcFreq = 0;
	int frequency[128] = {0};
	char currFile[10];

	HashTable * table = NULL;
	while (1) {
  		printf("\nEnter command (import/encode/decode/dump/quit): ");
    		scanf("%s", command);
		if (strcmp(command, "import") == 0) {
		    	if (table != NULL) freeTable(table);
			char filename[100];
		    	printf("Enter file name: ");
		    	scanf("%s", filename);
			int ret_value = compute_frequency(filename, frequency);
			
			//if no errors in computing frequency
			if (ret_value == 0) {	
				table = createDict(frequency);
			}else {
				printf("Deleting retained frquencies\n");
				resetFrequency(frequency);
			}
		} else if (strcmp(command, "encode") == 0) {
			if (calcFreq == 1) {
				char filename[100];
		    		printf("Enter file name: ");
		    		scanf("%s", filename);
		    		//encodeFile(filename, codes, bits);
			}else {
				printf("Error: Have not imported file yet\n");
			}
		} else if (strcmp(command, "decode") == 0) {
		    	if (calcFreq == 1) {
				char filename[100];
		    		printf("Enter file name: ");
		    		scanf("%s", filename);
		    		//decodeFile(filename, codes, bits);
			}else {
				printf("Error: Have not imported file yet\n");
			}

		} else if (strcmp(command, "dump") == 0) {
		    	if(table != NULL) {
				printf("Dumping dictionary:\n");
				printDict(table);
			}else {
				printf("Error: No Dictionary Loaded\n");
			}

		} else if (strcmp(command, "quit") == 0) {
			if(table != NULL) {
				freeTable(table);
			}
			break;
		} else {
		    	printf("Invalid command. Please try again.\n");
		}
    }

    return 0;
}

int compute_frequency(const char * filename, int frequency[]) {
	FILE *file = fopen(filename, "r");

    	if (file == NULL) {
        	printf("Error opening file %s\n", filename);
        	return 1;
    	}

    	int ch;
    	while ((ch = fgetc(file)) != EOF) {
        	// Increment the frequency of the current character
        	if (ch >= 0 && ch <= 127) {
            		frequency[ch]++;
       	 	}else {
			printf("Error: Encountered Unknown Character\n");
			return 1;
		}
    	}

    	fclose(file);
	return 0;	
}

void printFrequencies(int frequency[]) {
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



