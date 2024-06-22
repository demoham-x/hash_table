/**
 * hash_table.h
 */
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

/******************************************Include Header Files*/
#include "common.h"
/******************************************Static Globals*/
#define HT_MAX_SIZE                        53

/******************************************Structres*/
/* Structure for key-value pair */
typedef struct {
    CHAR * key;
    CHAR * value;
} HT_ITEM;

/* Structure for key-value pair array and its details */
typedef struct {
    int size;
    int count;
    HT_ITEM** items;
} HT_HASH_TABLE;

/******************************************API declarations*/
HT_HASH_TABLE * ht_new();
void ht_del_hash_table(HT_HASH_TABLE* ht);

#endif /* HASH_TABLE_H */