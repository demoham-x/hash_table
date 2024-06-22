# hash_table
 A C project implementing hash tables with operations for insertion, searching, and deletion of key-value pairs

 # Hash_table Algorithm

 This has two steps:

1. Convert the string to a large integer
2. Reduce the size of the integer to a fixed range by taking its remainder `mod`
   `m`

The variable `a` should be a prime number larger than the size of the alphabet.
We're hashing ASCII strings, which has an alphabet size of 128, so we should
choose a prime larger than that.

`char_code` is a function which returns an integer which represents the
character. We'll use ASCII character codes for this.

Let's try the hash function out:

```
hash("cat", 151, 53)

hash = (151**2 * 99 + 151**1 * 97 + 151**0 * 116) % 53
hash = (2257299 + 14647 + 116) % 53
hash = (2272062) % 53
hash = 5
```
