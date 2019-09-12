#include <stdio.h>
#include <string.h>

#include "hashtable.h"

void printTable(ht_hashtable_t *table) {

	printf("======== hash table ========\n");

	ht_record_t *currentRecord = table->firstRecord;

	while (currentRecord != NULL) {
		if (currentRecord->size == 0)
			printf("%s -> %s\n", currentRecord->key, (char *)currentRecord->value);
		else if (currentRecord->size == sizeof(int))
			printf("%s -> %d\n", currentRecord->key, *(int *)currentRecord->value);
		else {
			printf("%s -> 0x", currentRecord->key);
			for (size_t i = 0; i < currentRecord->size; i++)
				printf("%X", ((char *)currentRecord->value)[i]);
			printf("\n");
			
		}
		currentRecord = currentRecord->next;
	}

	printf("TOTAL : %ld\n\n", table->size);
}

void freeStdin() {
	char ch = '\0';
	while ((ch = getchar()) != '\n' && ch != EOF);
}

int main(int argc, char const *argv[]) {
	ht_hashtable_t table = {};
	unsigned int action = 0;
	char key[25] = "\0";
	char value[128] = "\0";
	int tmp = 0;

	/* fill hashtable */
	ht_setValueByKey(&table, "en_US", "English (United-States)", 0);
	ht_setValueByKey(&table, "en_UK", "English (United-Kingdom)", 0);
	ht_setValueByKey(&table, "en_CA", "English (Canada)", 0);
	ht_setValueByKey(&table, "fr_FR", "Français (France)", 0);
	ht_setValueByKey(&table, "fr_CA", "Français (Canada)", 0);
	ht_setValueByKey(&table, "ru_RU", "русский", 0);
	
	while (1) {
		action = 0;
		printf(
			"======== actions ========\n"
			"1. display table\n"
			"2. add record in table\n"
			"3. remove record in table\n"
		);
		printf(">> ");
		scanf("%u", &action);
		freeStdin();
		switch (action) {
			case 1:
				printf("\e[1;1H\e[2J\n");
				printTable(&table);
				break;

			case 2:
				printf("Key : ");
				fgets(key, sizeof(key), stdin);
				key[strlen(key)-1] = '\0';
				printf("Value : ");
				fgets(value, sizeof(value), stdin);
				value[strlen(value)-1] = '\0';
				tmp = ht_setValueByKey(&table, key, value, 0);
				printf("\e[1;1H\e[2J\n");
				if (tmp != 0)
					fprintf(stderr, "ERROR : %X\n", tmp);
				break;

			case 3:
				printf("Key : ");
				fgets(key, sizeof(key), stdin);
				key[strlen(key)-1] = '\0';
				tmp = ht_removeRecordByKey(&table, key);
				printf("\e[1;1H\e[2J\n");
				if (tmp == KEY_NOT_FOUND)
					fprintf(stderr, "ERROR : key not found !\n");
				else if(tmp != 0)
					fprintf(stderr, "ERROR : %X\n", tmp);
				break;
				
			default:
				printf("\e[1;1H\e[2J\n");
				fprintf(stderr, "ERROR : unkown action\n");
				break;
		}
	}

	return 0;
}