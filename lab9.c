#include <stdio.h>
#include <stdlib.h>
#define HASHSIZE 31
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:6031)

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order;
};

struct node {
	struct RecordType data;
	struct node* next;
};

// Fill out this structure
struct HashType
{
	struct node* head;
};

// Compute the hash function
int hash(int x)
{
	return x % (rand() % 30 + 1);
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType* pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType* pHashArray, int hashSz)
{
	int i;
	for (i = 0; i < hashSz; ++i)
	{
		struct node* current = pHashArray[i].head;
		if (current != NULL)
		{
			printf("Index %d -> ", i);
			while (current != NULL)
			{
				printf("%d %c %d -> ", current->data.id, current->data.name, current->data.order);
				current = current->next;
			}
			printf("\n");
		}
	}
}

void initializeHashTable(struct HashType* hashArr, int size) { //helper 
	int i;
	for (i = 0; i < size; ++i) {
		hashArr[i].head = NULL; //initialize each chain
	}
}

void insertRecord(struct HashType* hashArray, struct RecordType record) {
	int index = hash(record.id);
	struct node* newN = (struct node*)malloc(sizeof(struct node));
	if (newN == NULL) {
		printf("Memory allocation failed.\n");
		exit(-1);
	}
	newN->data = record;
	newN->next = hashArray[index].head;
	hashArray[index].head = newN; 
}


int main() {
	struct RecordType* pRecords;
	int recordSz = 0;

	recordSz = parseData("input_lab_9.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation

	struct HashType hashArray[HASHSIZE];
	initializeHashTable(hashArray, HASHSIZE);

	//insert each record
	for (int i = 0; i < recordSz; ++i) {
		insertRecord(hashArray, pRecords[i]);
	}

	displayRecordsInHash(hashArray, HASHSIZE);
	
	return 0;
}