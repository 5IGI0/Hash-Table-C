#ifndef HASHTABLE_H
#define HASHTABLE_H

/* structures */

typedef struct ht_record {
	char *key;
	void *value;
	size_t size;
	struct ht_record *prev;
	struct ht_record *next;
} ht_record_t;


typedef struct ht_hashtable {
	size_t size;
	ht_record_t *firstRecord;
} ht_hashtable_t;

/* errors */

#define INVALID_ARG_NO_HASHTABLE 			1
#define INVALID_ARG_NO_KEY					2
#define INVALID_ARG_NO_RECORD				3
#define INVALID_ARG_RECORD_WITHOUT_KEY		4
#define INVALID_ARG_RECORD_WITHOUT_VALUE	5
#define ALLOC_ERROR							6
#define KEY_NOT_FOUND						7

/* fonctions */

ht_record_t *ht_findRecord(ht_hashtable_t *table, const char *key);
int ht_setValue(ht_record_t *record, const char *value, size_t size);
ht_record_t *ht_getLastRecord(ht_hashtable_t *table);
int ht_addRecord(ht_hashtable_t *table, ht_record_t *record);
int ht_setKey(ht_record_t *record, const char *key);
int ht_setValueByKey(ht_hashtable_t *table, const char *key, const char *value, size_t size);
int ht_removeRecord(ht_hashtable_t *table, ht_record_t *record);
void ht_freeRecord(ht_record_t *record);
int ht_removeRecordByKey(ht_hashtable_t *table, const char *key);

#endif