# oscar

https://github.com/silentbicycle/oscar

mark/sweep garbage collector for C



oscar, for when memory leaks are making you grouchy.
oscar, 当内存泄漏让你不高兴的时候。

oscar provides a mark and sweep garbage collector for a pool of equally-sized chunks of memory. It uses lazy sweeping, roughly as described here. The pool can be grown an demand, or kept inside a fixed-size pool of statically allocated memory. Marking and freeing behavior are specified via callbacks.
oscar为大小相同的内存块池提供了标记和清除垃圾收集器。它使用懒惰清扫，大致如下所述。池可以根据需求增长，也可以保存在静态分配的固定大小的内存池中。标记和释放行为是通过回调来指定的。

The GC should be reasonably efficient (though it is not generational). Its tests pass on OS X and OpenBSD, and it runs without Valgrind warnings.
GC应该是相当有效的(尽管它不是分代的)。它的测试通过了OS X和OpenBSD，并且运行时没有Valgrind的警告。

The documentation is inside oscar.h. For usage examples, see the test suite (test.c).
文档在oscar.h中。有关使用示例，请参阅测试套件(test.c)。

For more information about garbage collectors, I recommend Paul R. Wilson's "Uniprocessor Garbage Collection Techniques", Jones, Hosking, and Moss's The Garbage Collection Handbook, and Jones & Lins' Garbage Collection: Algorithms for Automatic Dynamic Memory Management.




```c
/* Unsigned int for pool IDs, can be defined at compile-time
 * to use <4 bytes. */
//Unsigned int for pool IDs, can be defined at compile-time to use <4 bytes.
//用于池id的无符号int，可以在编译时定义为使用<4字节。
#ifdef OSCAR_POOL_ID_TYPE
typedef OSCAR_POOL_ID_TYPE pool_id;
#else
typedef uint32_t pool_id;
#endif

/* Opaque struct for the GC internals. */
//GC内部的不透明结构。
typedef struct oscar oscar;

/* Special sentinel value for "no ID". */
//"no ID"的特殊标记值。
#define OSCAR_ID_NONE ((pool_id) -1)

/* Function to mark the current root set, using oscar_mark on each
 * reachable pool ID. The UDATA is passed along from when the pool
 * was defined. Should return <0 on error. >=0 results are ignored. */
//Function to mark the current root set, using oscar_mark on each reachable pool ID.
//函数标记当前根集，在每个可达的池ID上使用oscar_mark。
//The UDATA is passed along from when the pool was defined.
//UDATA是从定义池开始传递的。
//Should return <0 on error. >=0 results are ignored.
//在错误时应该返回<0。>=0结果被忽略。
typedef int (oscar_mark_cb)(oscar *pool, void *udata);

/* If non-NULL, this will be called whenever an unreachable cell is about to
 * be swept. If the cell has not previously been allocated into, then the
 * cell will contain (CELL_SZ) 0 bytes. */
//If non-NULL, this will be called whenever an unreachable cell is about to be swept.
//如果非null，当一个不可达的单元格即将被扫描时，这个函数将被调用。
//If the cell has not previously been allocated into, then the cell will contain (CELL_SZ) 0 bytes.
//如果单元格以前没有被分配到其中，那么单元格将包含(CELL_SZ) 0字节。
typedef void (oscar_free_cb)(oscar *pool, pool_id id, void *udata);

/* Callback to malloc / realloc / free memory.
 * p == NULL, new_sz == N           -> behave as malloc(N)
 * p == x, new_sz == 0              -> behave as free(x)
 * p == x, old_sz != 0, new_sz != 0 -> behave as realloc(x, new_sz)
 * Note: the realloc-like behavior is expected to copy old_sz bytes over. */
// Callback to malloc / realloc / free memory.
// 回调到malloc / realloc /释放内存。
// p == NULL, new_sz == N           -> behave as malloc(N)
// p == NULL, new_sz == N           -> 相当于malloc(N)
// p == x, new_sz == 0              -> behave as free(x)
// p == x, new_sz == 0              -> 相当于free(x)
// p == x, old_sz != 0, new_sz != 0 -> behave as realloc(x, new_sz)
// p == x, old_sz != 0, new_sz != 0 -> 相当于realloc(x, new_sz)
// Note: the realloc-like behavior is expected to copy old_sz bytes over.
// 注意:类似realloc的行为被期望复制old_sz字节。
typedef void *(oscar_memory_cb)(void *p, size_t old_sz,
                                size_t new_sz, void *udata);

/* An oscar_memory_cb that just calls malloc/free/realloc. */
// oscar_memory_cb只调用malloc/free/realloc。
void *oscar_generic_mem_cb(void *p, size_t old_sz, size_t new_sz, void *udata);

/* Init a fixed-sized garbage-collected pool of as many CELL_SZ-byte
 * cells as will fit inside the BYTES bytes pointed to by MEMORY.
 * For the various callbacks, see their typedefs.
 * Return NULL on error, such as if the provided memory in insufficient. */
//Init a fixed-sized garbage-collected pool of as many CELL_SZ-byte cells as will fit inside the BYTES bytes pointed to by MEMORY.
//初始化一个固定大小的垃圾回收池，池中包含尽可能多的CELL_SZ-byte单元格，以容纳MEMORY所指向的BYTES字节。
//For the various callbacks, see their typedefs.
//有关各种回调函数，请参阅它们的类型定义。
//Return NULL on error, such as if the provided memory in insufficient.
//如果出现错误，例如提供的内存不足，则返回NULL。
oscar *oscar_new_fixed(unsigned int cell_sz, unsigned int bytes, char *memory,
                       oscar_mark_cb *mark_cb, void *mark_udata,
                       oscar_free_cb *free_cb, void *free_udata);

/* Init a resizable garbage-collected pool of START_COUNT cells,
 * each CELL_SZ bytes. For the various callbacks, see their typedefs. */
//Init a resizable garbage-collected pool of START_COUNT cells, each CELL_SZ bytes.
//初始化一个可调整大小的垃圾收集池，其中包含START_COUNT单元格，每个CELL_SZ字节。
//For the various callbacks, see their typedefs.
//有关各种回调函数，请参阅它们的类型定义。
oscar *oscar_new(unsigned int cell_sz, unsigned int start_count,
    oscar_memory_cb *mem_cb, void *mem_udata,
    oscar_mark_cb *mark_cb, void *mark_udata,
    oscar_free_cb *free_cb, void *free_udata);

/* Get the current cell count. */
//获取当前单元格计数。
unsigned int oscar_count(oscar *pool);

/* Mark the ID'th cell as reachable. */
//将ID单元格标记为可达。
void oscar_mark(oscar *pool, pool_id id);

/* Get a pointer to a cell, by ID.
 * Note that the pointer may become stale if oscar_alloc causes the pool
 * to resize, or if the cell is swept. Returns NULL on error. */
//Get a pointer to a cell, by ID.
//通过ID获得指向单元格的指针
//Note that the pointer may become stale if oscar_alloc causes the pool to resize, or if the cell is swept. Returns NULL on error.
//注意，如果oscar_alloc导致池调整大小，或者单元格被清除，指针可能会变得陈旧。错误返回NULL。
void *oscar_get(oscar *pool, pool_id id);

/* Get a fresh pool ID. Can cause a mark/sweep pass, and may cause
 * the pool's backing cells to move in memory (making any pointers stale).
 * Returns -1 on error. */
//Get a fresh pool ID. Can cause a mark/sweep pass, and may cause the pool's backing cells to move in memory (making any pointers stale).
//获取一个新的池ID。可能导致标记/清除通过，并可能导致池的支持单元在内存中移动(使任何指针陈旧)。
//Returns -1 on error. 
//错误返回-1
pool_id oscar_alloc(oscar *pool);

/* Force a full GC mark/sweep. If free_cb is defined, it will be called
 * on every swept cell. Returns <0 on error. */
//Force a full GC mark/sweep. If free_cb is defined, it will be called on every swept cell.
//强制一个完整的GC标记/清除。如果定义了free_cb，它将在每个扫描单元格上被调用。
//Returns <0 on error.
//在错误时返回<0。
int oscar_force_gc(oscar *pool);

/* Free the pool and its contents. If the memory was dynamically allocated,
 * it will be freed; if a free_cb is defined, it will be called on every cell. */
//Free the pool and its contents. If the memory was dynamically allocated,
//释放池和里面的东西。如果内存是动态分配的，
//it will be freed; if a free_cb is defined, it will be called on every cell.
//它将被释放;如果定义了free_cb，它将在每个单元格上被调用。
void oscar_free(oscar *pool);
```