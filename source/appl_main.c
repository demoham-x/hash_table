/**
 * appl_main.c
 */

/******************************************Include Header Files*/
#include "common.h"
#include "hash_table.h"
#include "utils.h"

int main(int argc, char *argv[])
{
    HT_HASH_TABLE * ht;
    CHAR * k;
    CHAR * v;

    /* init */
    k = NULL;
    v = NULL;

    ht = ht_new();

    for (int i = 0; i < 5000; i++)
    {
        k = rand_word(2, 30);
        v = rand_word(10, 100);
        ht_insert(ht, k, v);
    }
    ht_del_hash_table(ht);
    return -1;
}