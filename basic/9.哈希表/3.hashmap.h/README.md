# hashmap.h

https://github.com/sheredom/hashmap.h

A simple one header hashmap implementation for C/C++.

## Usage

Just `#include "hashmap.h"` in your code!

The current supported compilers are gcc, clang and msvc.

The current supported platforms are Linux, macOS and Windows.

### Fundamental Design

The hashmap is made to work with UTF-8 string slices - sections of strings that are passed with a pointer and an explicit length. The reason for this design choice was that the hashmap is being used, by the author, to map symbols that are already resident in memory from a source file of a programming language. To save from causing millions of additional allocations to move these UTF-8 string slices into null-terminated strings, an explicit length is always passed.

Note also that while the API passes char* pointers as the key - these keys are never used with the C API string functions. Instead `memcmp` is used to compare keys. This allows us to use UTF-8 strings in place of regular ASCII strings with no additional code.

### Create a Hashmap

To create a hashmap call the `hashmap_create` function:

要创建 hashmap，请调用 hashmap_create 函数：

```
const unsigned initial_size = 2;
struct hashmap_s hashmap;
if (0 != hashmap_create(initial_size, &hashmap)) {
  // error!
}
```

The `initial_size` parameter only sets the initial size of the hashmap - which can grow if multiple keys hit the same hash entry. The initial size must be a power of two, and creation will fail if it is not.

initial_size 参数仅设置hashmap的初始大小 - 如果多个键命中相同的hash条目，该大小会增长。初始大小必须是 2 的幂，否则创建将失败。

### Put Something in a Hashmap

To put an item in the hashmap use the `hashmap_put` function:

要将项目放入hashmap中，请使用 hashmap_put 函数：

```
int meaning_of_life = 42;
char question = 6 * 8;

if (0 != hashmap_put(&hashmap, "life", strlen("life"), &meaning_of_life)) {
  // error!
}

if (0 != hashmap_put(&hashmap, "?", strlen("?"), &question)) {
  // error!
}
```

Notice that multiple entries of *differing* types can exist in the same hashmap. The hashmap is not typed - it can store any `void*` data as the value for a key.

请注意，不同类型的多个条目可以存在于同一个hashmap中。 hashmap 没有类型 - 它可以存储任何 void* 数据作为键的值。

### Get Something from a Hashmap

To get an entry from a hashmap use the `hashmap_get` function:

要从 hashmap 中获取条目，请使用 hashmap_get 函数：

```
void* const element = hashmap_get(&hashmap, "x", strlen("x"));
if (NULL == element) {
  // error!
}
```

The function will return `NULL` if the element is not found. Note that the key used to get an element does not have to be the same pointer used to put an element in the hashmap - but the string slice must match for a hit to occur.

如果未找到该元素，该函数将返回 NULL。请注意，用于获取元素的键不必与用于将元素放入hashmap中的指针相同 - 但是字符串片段必须匹配才能发生命中。

### Remove Something from a Hashmap

To remove an entry from a hashmap use the `hashmap_remove` function:

要从hashmap中删除一个条目，请使用hashmap_remove函数:

```
if (0 != hashmap_remove(&hashmap, "x", strlen("x"))) {
  // error!
}
```

The function will return non-zero if the element is not found. Note that the key used to get an element does not have to be the same pointer used to put an element in the hashmap - but the string slice must match for a hit to occur.

如果未找到该元素，该函数将返回非零值。请注意，用于获取元素的键不必与用于将元素放入hashmap中的指针相同 - 但是字符串片段必须匹配才能发生命中。

### Iterate Over a Hashmap

You can iterate over all the elements stored in the hashmap with the `hashmap_iterate` function:

你可以使用 hashmap_iterate 函数遍历存储在 hashmap 中的所有元素：

```
static int iterate(void* const context, void* const value) {
  // If the value is 42...
  if (42 == *(int*)value) {
    // Store into our user-provided context the value.
    *(void**) context = value;

    // Return 0 to tell the iteration to stop here.
    return 0;
  }

  // Otherwise tell the iteration to keep going.
  return 1;
}

int* value;
if (0 != hashmap_iterate(&hashmap, iterate, &value)) {
  if (*value != 42) {
    // error!
  }
} else {
  // if we got here it means we never found 42 in the hashmap
}
```

You can early exit from the iteration of the hashmap by returning non-zero from your callback function - perhaps you want to process and remove all elements from the hashmap or search for a specific value only. Otherwise if zero is returned from your callback then the iteration will encompass the entire hashmap.

你可以通过从回调函数返回非零值来提前退出hashmap的迭代 - 也许你想处理和删除hashmap中的所有元素或仅搜索特定值。否则，如果你的回调返回零，则迭代将包含整个hashmap。

### Alternate Iterator for Key Value Pairs

In some applications, such as needing to print out the contents of a hashmap, you need to have access to the key and key length in addition to the value. For that purpose a second iterator has been added called `hashmap_iterate_pairs`.

在某些应用程序中，例如需要打印出 hashmap 的内容，除了 value 之外，你还需要访问 key 和 key length。为此，添加了第二个迭代器，称为 hashmap_iterate_pairs。

Also, returning a -1 from the callback function allows automatic removal of the current item. This is especially handy when storing dynamically allocated objects to the map and needing to free the memory when destroying the map.

此外，从回调函数返回 -1 允许自动删除当前项目。这在将动态分配的对象存储到map 并在销毁map 时需要释放内存时特别方便。

```
int log_and_free_all(void* const context, struct hashmap_element_s* const e) {
  int counter;
  for (counter=0; counter < e->key_len; counter++) {
    fputc(e->key[counter], (FILE)context);
  }
  fprintf((FILE)context,"=%s pair has been freed\n", (char *)e->data);
  free(e->data);
  return -1;
}

void shut_down() {
  if (0!=hashmap_iterate_pairs(&hash, log_and_free_all, (void *)log)) {
    fprintf(stderr, "failed to deallocate hashmap entries\n");
  }
  fclose(log);
  hashmap_destroy(&hash);
}
```

### Get the Number of Entries in a Hashmap

To get the number of entries that have been put into a hashmap use the `hashmap_num_entries` function:

要获取已放入hashmap 中的条目数，请使用 hashmap_num_entries 函数：

```
unsigned num_entries = hashmap_num_entries(&hashmap);
```

### Destroy a Hashmap

To destroy a hashmap when you are finished with it use the `hashmap_destroy` function:

要在完成后销毁hashmap，请使用 hashmap_destroy 函数：

```
hashmap_destroy(&hashmap);
```
