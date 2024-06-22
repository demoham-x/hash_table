#include "utils.h"

/**
 * @fn is_prime
 * Return whether x is prime or not
 *
 * Returns:
 *   1  - prime
 *   0  - not prime
 *   -1 - undefined (i.e. x < 2)
 */
UCHAR is_prime(DECL_CONST INT32 x)
{
    INT32 i;

    if (x < 2) { return FALSE; }
    if (x < 4) { return TRUE; }
    if ((x % 2) == 0) { return FALSE; }
    for (i = 3; i <= floor(sqrt((double) x)); i += 2)
    {
        if ((x % i) == 0)
        {
            return FALSE;
        }
    }
    return TRUE;
}


/*
 * Return the next prime after x, or x if x is prime
 */
INT32 next_prime(INT32 x)
{
    while (is_prime(x) != 1)
    {
        x++;
    }
    return x;
}

/**
 * @fn rand_word
 * To generate a random word
 */
CHAR * rand_word
       (
            INT32 min_len,
            INT32 max_len
       )
{
    INT32 i, length;
    CHAR c;
    CHAR * word;

    /* Init */
    word = NULL;

    /* seed random */
#ifdef _WIN32
    LARGE_INTEGER frequency;
    LARGE_INTEGER counter;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&counter);
    srand((unsigned int)(counter.QuadPart % frequency.QuadPart));
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((unsigned int)ts.tv_nsec);
#endif

    length = rand() % (max_len - min_len + 1) + min_len;

    word = calloc((size_t)(length+1), sizeof(CHAR));

    if (NULL != word)
    {
        for (i = 0; i < length; i++)
        {
            c = 'a' + rand() % 26;
            word[i] = c;
        }

        word[i] = 0;
    }

    return word;
}
