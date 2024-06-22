/**
 * hash_table.h
 */
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

/******************************************Include Header Files*/
#include "common.h"
#include "utils.h"
/******************************************Static Globals*/
#define HT_INIT_SIZE                       0

/******************************************Structres*/
/* Structure for key-value pair */
typedef struct {
    CHAR * key;
    CHAR * value;
} HT_ITEM;

/* Structure for key-value pair array and its details */
typedef struct {
    INT32 base_size;
    INT32 size;
    INT32 count;
    HT_ITEM** items;
} HT_HASH_TABLE;

/******************************************API declarations*/
HT_HASH_TABLE * ht_new();
void ht_del_hash_table(HT_HASH_TABLE* ht);
API_RESULT ht_insert
           (
                HT_HASH_TABLE   * ht,
                DECL_CONST CHAR * key,
                DECL_CONST CHAR * value
           );
API_RESULT ht_search
           (
                /* IN */  HT_HASH_TABLE   *  ht,
                /* IN */  DECL_CONST CHAR *  key,
                /* OUT */ CHAR            ** value
           );

#endif /* HASH_TABLE_H */