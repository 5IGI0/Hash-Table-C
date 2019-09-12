#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#include "hashtable.h"

ht_record_t *ht_findRecord(ht_hashtable_t *table, const char *key) {
	if (!table)
		return NULL;
	if (!key)
		return NULL;

	ht_record_t *currentRecord = table->firstRecord;

	while (currentRecord != NULL) {
		if (!strcmp(currentRecord->key, key))
			return currentRecord;
		currentRecord = currentRecord->next;
	}

	return NULL;
}

int ht_setValue(ht_record_t *record, const char *value, size_t size) {
	if (!record)
		return INVALID_ARG_NO_RECORD;

	if (size == 0) { //string
		record->size = 0;
		size = strlen(value)+1;
	} else {
		record->size = size;
	}
	
	char *copy = calloc(size, 1);

	if (!copy)
		return ALLOC_ERROR;

	// free
	if (!record->value) {
		free(record->value);
		record->value = NULL;
	}
	
	for (size_t i = 0; i < size; i++) {
		copy[i] = value[i];
	}
	
	record->value = (void *)copy;

	return 0;
}

ht_record_t *ht_getLastRecord(ht_hashtable_t *table) {
	if (!table)
		return NULL;
	if (!table->firstRecord)
		return NULL;

	ht_record_t *currentRecord = table->firstRecord;
	ht_record_t *lastRecord = NULL;

	while (currentRecord != NULL) {
		lastRecord = currentRecord;
		currentRecord = currentRecord->next;
	}

	return lastRecord;
}

int ht_addRecord(ht_hashtable_t *table, ht_record_t *record) {
	if (!table)
		return INVALID_ARG_NO_HASHTABLE;
	if (!record)
		return INVALID_ARG_NO_RECORD;
	if (!record->key)
		return INVALID_ARG_RECORD_WITHOUT_KEY;
	if (!record->value)
		return INVALID_ARG_RECORD_WITHOUT_VALUE;
	if (record->key[0] == '\0')
		return INVALID_ARG_RECORD_WITHOUT_KEY;

	if (!table->firstRecord) {
		table->firstRecord = record;
		record->next = NULL;
		record->prev = NULL;
	} else {
		ht_record_t *lastRecord = ht_getLastRecord(table);
		lastRecord->next = record;
		record->prev = lastRecord;
	}

	table->size += 1;

	return 0;
}

void ht_freeRecord(ht_record_t *record) {
	free(record->key);
	free(record->value);
	free(record);
}

int ht_removeRecord(ht_hashtable_t *table, ht_record_t *record){
	if (!table)
		return INVALID_ARG_NO_HASHTABLE;
	if (!record)
		return INVALID_ARG_NO_RECORD;

	if (!record->prev) { //first record
		table->firstRecord = record->next;
	} else {
		record->prev->next = record->next;
		record->next->prev = record->prev;
	}

	ht_freeRecord(record);
	
	table->size -= 1;

	return 0;
}

int ht_removeRecordByKey(ht_hashtable_t *table, const char *key){
	if (!table)
		return INVALID_ARG_NO_HASHTABLE;
	if(!key)
		return INVALID_ARG_NO_KEY;

	ht_record_t *record = ht_findRecord(table, key);

	if (!record)
		return KEY_NOT_FOUND;

	return ht_removeRecord(table, record);
}

int ht_setKey(ht_record_t *record, const char *key) {
	if (!record)
		return INVALID_ARG_NO_RECORD;
	if(!key)
		return INVALID_ARG_NO_KEY;

	char *copy = calloc(strlen(key)+1, 1);
	strcpy(copy, key);

	record->key = copy;
	return 0;
}

int ht_setValueByKey(ht_hashtable_t *table, const char *key, const char *value, size_t size){
	if (!table)
		return INVALID_ARG_NO_HASHTABLE;
	if (!key)
		return INVALID_ARG_NO_KEY;
	
	int tmp = 0;
	ht_record_t *record = ht_findRecord(table, key);

	if (record) { // record exist
		return ht_setValue(record, value, size);
	} else {
		record = calloc(1, sizeof(ht_record_t));
		tmp = ht_setValue(record, value, size);
		if(tmp != 0)
			return tmp;

		tmp = ht_setKey(record, key);

		if(tmp != 0)
			return tmp;
		
		ht_addRecord(table, record);
		return 0;
	}
}

