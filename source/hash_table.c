/**
 * hash_table.c
 */

/******************************************Include Header Files*/
#include "hash_table.h"

/******************************************Intenal function declarations*/
DECL_STATIC HT_ITEM * ht_new_item
                      (
                         DECL_CONST CHAR * k,
                         DECL_CONST CHAR * v
                      );
DECL_STATIC void ht_del_item(HT_ITEM * i);

/******************************************Intenal functions*/
/**
 * ht_new_item allocates a chunk of memory
 * the size of an HT_ITEM, and saves a copy of
 * the strings k and v in the new chunk of memory.
 * The function is marked as static because it will
 * only ever be called by code internal to the
 * hash table
 */
DECL_STATIC HT_ITEM * ht_new_item
                      (
                         DECL_CONST CHAR * k,
                         DECL_CONST CHAR * v
                      )
{
    HT_ITEM * i;

    /* Init */
    i = NULL;

    if ((NULL != k) || (NULL != v))
    {
        /* allocating a mem for the key-value item */
        i = (HT_ITEM *) MALLOC(sizeof(HT_ITEM));

        if (NULL != i)
        {
            /* storing the duplicated string */
            i->key = strdup(k);
            i->value = strdup(v);
        }
    }

    return i;
}

/******************************************Functions*/
/**
 * ht_del_item deletes ht_items,
 * which free the memory we've allocated, so we
 * don't cause memory leaks.
 */
DECL_STATIC void ht_del_item(HT_ITEM * i)
{
    FREE(i->key);
    FREE(i->value);
    FREE(i);
}

/**
 * ht_new initialises a new hash table.
 * size defines how many items we can store.
 * This is fixed at 53 for now. We'll expand
 * this in the section on resizing. We
 * initialise the array of items with calloc,
 * which fills the allocated memory with NULL
 * bytes. A NULL entry in the array indicates
 * that the bucket is empty.
 */
HT_HASH_TABLE * ht_new()
{
    HT_HASH_TABLE * ht;

    /* Init */
    ht = NULL;

    /* allocating memory for new has table */
    ht = (HT_HASH_TABLE *)MALLOC(sizeof(HT_HASH_TABLE));

    if (NULL != ht)
    {
        ht->size = HT_MAX_SIZE;
        ht->count = 0;
        ht->items = CALLOC(ht->size, sizeof(HT_ITEM*));
    }

    return ht;
}

/**
 * ht_del_hash_table deletes ht_hash_tables,
 * which free the memory we've allocated, so we
 * don't cause memory leaks.
 */
void ht_del_hash_table(HT_HASH_TABLE * ht) {
    INT32 i;

    if (NULL != ht)
    {
        for (i = 0; i < ht->size; i++)
        {
            if (NULL != ht->items[i])
            {
                ht_del_item(ht->items[i]);
            }
        }
    }
    free(ht->items);
    free(ht);
}