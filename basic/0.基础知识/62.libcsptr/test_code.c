#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#include "smart_ptr.h"
#include "array.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
//Simple unique_ptr

int simple1(void)
{
    // some_int is an unique_ptr to an int with a value of 1.
    smart int *some_int = unique_ptr(int, 1);

    printf("%p = %d\n", some_int, *some_int);

    // some_int is destroyed here
    return 0;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//Simple unique_ptr with destructor

struct log_file {
    int fd;
    // ...
};

void cleanup_log_file(void *ptr, void *meta) {
    (void) meta;
    close(((struct log_file *) ptr)->fd);
}

//Simple unique_ptr with destructor
int simple2(void)
{
    smart struct log_file *log = unique_ptr(struct log_file, {
            .fd = open("/dev/null", O_WRONLY | O_APPEND),
            // ...
        }, cleanup_log_file);

    write(log->fd, "Hello", 5);

    // cleanup_log_file is called, then log is freed
    return 0;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//Allocating a smart array and printing its contents before destruction

void print_int(void *ptr, void *meta) {
    (void) meta;
    // ptr points to the current element
    // meta points to the array metadata (global to the array), if any.
    printf("%d\n", *(int*) ptr);
}

int simple3(void) {
    // Destructors for array types are run on every element of the
    // array before destruction.
    smart int *ints = unique_ptr(int[5], {5, 4, 3, 2, 1}, print_int);
    // ints == {5, 4, 3, 2, 1}

    // Smart arrays are length-aware
    for (size_t i = 0; i < array_length(ints); ++i) {
        ints[i] = i + 1;
    }
    // ints == {1, 2, 3, 4, 5}

    return 0;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//Using a different memory allocator (although most will replace malloc/free)
/* void *some_allocator(size_t);
void some_deallocator(void *);

int simple4(void) {
    smalloc_allocator = (s_allocator) {some_allocator, some_deallocator};
    // ...
    return 0;
} */
/************************************************************************/
/*                                                                      */
/************************************************************************/
//Automatic cleanup on error cases

/* struct log_file {
    int fd;
    // ...
}; */

static void close_log(void *ptr, void *meta) {
    (void) meta;
    struct log_file *log = ptr;
    if (log->fd != -1)
        close(log->fd);
}

struct log_file *open_log(const char *path) {
    smart struct log_file *log = shared_ptr(struct log_file, {0}, close_log);
    if (!log) // failure to allocate
        return NULL; // nothing happens, destructor is not called

    log->fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (log->fd == -1) // failure to open
        return NULL; // log gets destroyed, file descriptor is not closed since fd == -1.

    return sref(log); // a new reference on log is returned, it does not get destoyed
}

int simple5(void) {
    smart struct log_file *log = open_log("/dev/null");
    // ...
    return 0; // file descriptor is closed, log is freed
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//Using named parameters

void nothing(void *ptr, void *meta) {}

int simple6(void) {
    struct { int a; } m = { 1 };

    smart int *i = unique_ptr(int,
            .dtor = nothing,
            .value = 42,
            .meta = { &m, sizeof (m) }
        );

    return 0;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    simple1();
    simple2();
    simple3();
    //simple4();
    simple5();
    simple6();
    
    return 0;
}