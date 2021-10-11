# skiplist

https://github.com/silentbicycle/skiplist



# skiplist

A skiplist-based ordered collection library.

## Key Features:

- Getting or popping the first or last value in the skiplist is very cheap.
- Keys can have multiple values associated with them, if `skiplist_add` is used instead of `skiplist_set`.
- The skiplist can be iterated over from the start, or beginning at an arbitrary key.
- This library is distributed under the ISC License. You can use it freely, even for commercial purposes.

This library currently requires C99 (for `__VA_ARGS__`, stack-allocated arrays, and numeric types), but could be converted to C89 without a whole lot of work.
