/**
 * hash_table.c
 */

/******************************************Include Header Files*/
#include "hash_table.h"

/******************************************Static Globals*/
#define HT_PRIME_1                         152
#define HT_PRIME_2                         163

DECL_STATIC HT_ITEM HT_DELETED_ITEM = {NULL, NULL};

/******************************************Intenal function declarations*/
DECL_STATIC HT_ITEM * ht_new_item
                      (
                         DECL_CONST CHAR * k,
                         DECL_CONST CHAR * v
                      );
DECL_STATIC void ht_del_item(HT_ITEM * i);
DECL_STATIC INT32 ht_hash
                  (
                     DECL_CONST CHAR * string,
                     DECL_CONST INT32 var,
                     DECL_CONST INT32 size
                  );
DECL_STATIC API_RESULT ht_get_hash
                       (
                          DECL_CONST CHAR  * s,
                          DECL_CONST INT32   num_buckets,
                          DECL_CONST INT32   attempt,
                          INT32            * index
                       );
DECL_STATIC HT_HASH_TABLE * ht_new_sized(DECL_CONST INT32 base_size);
DECL_STATIC void ht_resize
                 (
                     HT_HASH_TABLE * ht,
                     DECL_CONST INT32 base_size
                 );
DECL_STATIC void ht_resize_up(HT_HASH_TABLE * ht);
DECL_STATIC void ht_resize_down(HT_HASH_TABLE* ht);
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
 * ht_hash gets a string , int a, Num Of Buckets(size)
 * then does a algorithmic calcukation and returns a
 * hash key
 */
DECL_STATIC INT32 ht_hash
                  (
                     DECL_CONST CHAR * string,
                     DECL_CONST INT32 var,
                     DECL_CONST INT32 size
                  )
{
    INT64 hash, i;

    /* Init */
    hash = 0;

    if (NULL != string)
    {
        DECL_CONST INT32 len_s = strlen(string);

        for (i = 0; i < len_s; i++)
        {
            hash += (INT64)pow(var, len_s - (i+1)) * string[i];
            hash = hash % size;
        }
    }

    return (INT32)hash;
}

/**
 * ht_get_hash will handle collisions
 */
DECL_STATIC API_RESULT ht_get_hash
                       (
                          DECL_CONST CHAR  * s,
                          DECL_CONST INT32   num_buckets,
                          DECL_CONST INT32   attempt,
                          INT32            * index
                       )
{
    if (NULL == s)
    {
        return API_FAILURE;
    }

    DECL_CONST INT32 hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    DECL_CONST INT32 hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
    *index = (hash_a + (attempt * (hash_b + 1))) % num_buckets;

    return API_SUCCESS;
}

/**
 * @fn ht_new_sized
 */
DECL_STATIC HT_HASH_TABLE * ht_new_sized(DECL_CONST INT32 base_size)
{
    HT_HASH_TABLE * ht;

    /* Init */
    ht = NULL;

    ht = MALLOC(sizeof(HT_HASH_TABLE));

    if (NULL == ht)
    {
        return ht;
    }

    ht->base_size = base_size;
    ht->size = next_prime(ht->base_size);
    ht->count = 0;
    ht->items = CALLOC((size_t)ht->size, sizeof(HT_ITEM*));
    return ht;
}

/**
 * @fn ht_resize
 */
DECL_STATIC void ht_resize
                 (
                     HT_HASH_TABLE * ht,
                     DECL_CONST INT32 base_size
                 )
{
    HT_HASH_TABLE * new_ht;
    HT_ITEM * item;
    HT_ITEM ** tmp_items;

    /* Init */
    new_ht = NULL;
    item = NULL;
    if (base_size < HT_INIT_SIZE) {
        return;
    }
    new_ht = ht_new_sized(base_size);

    if ((NULL == new_ht) && (NULL == ht))
    {
        CONSOLE_OUT("[HT]: Resizing Failed");
        return;
    }

    for (int i = 0; i < ht->size; i++)
    {
        item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM)
        {
            ht_insert(new_ht, item->key, item->value);
        }
    }

    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    /* To delete new_ht, we give it ht's size and items */
    DECL_CONST INT32 tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    ht_del_hash_table(new_ht);
}

/**
 * @fn ht_resize_up
 */
DECL_STATIC void ht_resize_up(HT_HASH_TABLE * ht)
{
    DECL_CONST INT32 new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}

/**
 * @fn ht_resize_down
 */
DECL_STATIC void ht_resize_down(HT_HASH_TABLE* ht)
{
    DECL_CONST INT32 new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
}
/******************************************Functions*/
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
    return ht_new_sized(HT_INIT_SIZE);
    CONSOLE_OUT("[HT]: Hash Table Created\n");
}

/**
 *  ht_del_hash_table deletes ht_hash_tables,
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
    CONSOLE_OUT("[HT]: Hash Table Deleted\n");
}

/**
 * @fn ht_insert
 *     API to Insert a item to the hash table
 */
API_RESULT ht_insert
           (
                HT_HASH_TABLE   * ht,
                DECL_CONST CHAR * key,
                DECL_CONST CHAR * value
           )
{
    HT_ITEM * item;
    HT_ITEM * cur_item;
    INT32     index, i, load;

    /* Init */
    i = 1;
    item = NULL;
    cur_item = NULL;

    load = ht->count * 100 / ht->size;
    if (load > 70) {
        ht_resize_up(ht);
    }

    item = ht_new_item(key, value);

    if (NULL == item)
    {
        CONSOLE_OUT("[HT]: Create New Item Failed\n");
        return API_FAILURE;
    }

    if (API_SUCCESS != ht_get_hash(item->key, ht->size, 0, &index))
    {
        CONSOLE_OUT("[HT]: Hash Calculation Failed\n");
        return API_FAILURE;
    }

    cur_item = ht->items[index];

    while ((cur_item != NULL) && (cur_item != &HT_DELETED_ITEM))
    {
       if (cur_item != &HT_DELETED_ITEM)
       {
            if (strcmp(cur_item->key, key) == 0)
            {
                ht_del_item(cur_item);
                ht->items[index] = item;
                return API_SUCCESS;
            }
       }

       if (API_SUCCESS != ht_get_hash(item->key, ht->size, i, &index))
       {
            return API_FAILURE;
       }

        cur_item = ht->items[index];
        i++;
    }

    ht->items[index] = item;
    ht->count++;
    CONSOLE_OUT("[HT]: New Item Inserted\n");

    return API_SUCCESS;
}

/**
 * @fn ht_search
 * To search a value in the table
 */
API_RESULT ht_search
           (
                /* IN */  HT_HASH_TABLE   *  ht,
                /* IN */  DECL_CONST CHAR *  key,
                /* OUT */ CHAR            ** value
           )
{
    INT32 index;
    HT_ITEM * item;
    INT32 i;
    API_RESULT retval;

    /* Init */
    retval = API_FAILURE;
    index = 0;
    item = NULL;
    i = 1;
    *value = NULL;

    if ((NULL == ht) || (NULL == key))
    {
        return API_FAILURE;
    }

    if (API_SUCCESS != ht_get_hash(key, ht->size, 0, &index))
    {
        CONSOLE_OUT("[HT]: Hash Calculation Failed\n");
        return API_FAILURE;
    }

    item = ht->items[index];

    while (item != NULL)
    {
        if (item != &HT_DELETED_ITEM)
        {
            if (strcmp(item->key, key) == 0)
            {
                *value = item->value;
                retval = API_SUCCESS;
                break;
            }
        }
        if (API_SUCCESS != ht_get_hash(key, ht->size, i, &index))
            {
                CONSOLE_OUT("[HT]: Hash Calculation Failed\n");
                retval = API_FAILURE;
                break;
            }
            item = ht->items[index];
            i++;
    }

    return retval;
}

/**
 * @fn ht_delete
 * To Delete the item From Hash Table
 */
API_RESULT ht_delete
           (
                HT_HASH_TABLE   * ht,
                DECL_CONST CHAR * key
           )
{
    INT32        index, i;
    API_RESULT   retval;
    HT_ITEM    * item;

    /* Init */
    retval = API_SUCCESS;
    item   = NULL;
    i = 1;

    retval = ht_get_hash(key, ht->size, 0, &index);

    if (API_SUCCESS != retval)
    {
        CONSOLE_OUT("[HT]: Hash Calculation Failed\n");
        return API_FAILURE;
    }

    item = ht->items[index];

    while (item != NULL)
    {
        if (item != &HT_DELETED_ITEM)
        {
            if (strcmp(item->key, key) == 0)
            {
                ht_del_item(item);
                ht->items[index] = &HT_DELETED_ITEM;
                ht->count--;
                retval = API_SUCCESS;
                break;
            }
        }
        retval = ht_get_hash(key, ht->size, i, &index);

        if (API_SUCCESS != retval)
        {
            CONSOLE_OUT("[HT]: Hash Calculation Failed\n");
            retval = API_FAILURE;
            break;
        }
        item = ht->items[index];
        i++;
    }

    return retval;
}