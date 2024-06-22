/**
 * appl_main.c
 */

/******************************************Include Header Files*/
#include "common.h"
#include "hash_table.h"

int main(int argc, char *argv[])
{
    HT_HASH_TABLE * ht;

    ht = ht_new();
    ht_del_hash_table(ht);
    return 0;
}