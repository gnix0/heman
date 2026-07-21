#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define HEAP_CAPACITY 640000
#define CHUNK_LIST_CAPACITY 1024

#define UNIMPLEMENTED \
    do { \
        fprintf(stderr, "%s:%d: TODO: %s is not implemented yet\n", \
                __FILE__, __LINE__, __func__); \
        abort(); \
    } while(0)

typedef struct {
    void *start;
    size_t size;
} Chunk;

typedef struct {
    size_t count;
    Chunk chunks [CHUNK_LIST_CAPACITY];
} Chunk_List;

int chunk_list_find(const Chunk_List *list, void *ptr)
{
    (void) list;
    (void) ptr;
    UNIMPLEMENTED;
    return -1;
}

void chunk_list_dump(const Chunk_List *list)
{
    printf("Chunks (%zu):\n", list->count);
    for (size_t i = 0; i < list->count; ++i) {
        printf("  start: %p, size: %zu\n",
               list->chunks[i].start,
               list->chunks[i].size);
    }
}

void chunk_list_insert(Chunk_List *list, void *start, size_t size)
{
    assert(list->count < CHUNK_LIST_CAPACITY);
    list->chunks[list->count].start = start;
    list->chunks[list->count].size = size;

    for (size_t i = list->count; i > 0
            && list->chunks[i].start < list->chunks[i - 1].start;
            --i) {
        const Chunk t = list->chunks[i];
        list->chunks[i] = list->chunks[i - 1];
        list->chunks[i - 1] = t;
    }

    list->count += 1;
}

void chunk_list_remove(Chunk_List *list, size_t index)
{
    (void) list;
    (void) index;
    UNIMPLEMENTED;
}

char heap[HEAP_CAPACITY] = {0};
size_t heap_size = 0;

Chunk_List allocated_chunks = {0};
Chunk_List freed_chunks = {0};

void *heap_alloc(size_t size)
{
    if (size == 0) {
        return NULL;
    }

    assert(heap_size + size <= HEAP_CAPACITY);
    void *ptr = heap + heap_size;
    heap_size += size;
    chunk_list_insert(&allocated_chunks, ptr, size);

    return ptr;
}

// O(allocated_chunks)
void heap_free(void *ptr)
{
    (void) ptr;
    UNIMPLEMENTED;
}

void heap_collect()
{
    UNIMPLEMENTED;
}

int main(void)
{
    for (size_t i = 0; i < 100; ++i) {
        void *p = heap_alloc(i);
        // if (i % 2 == 0) {
        //     heap_free(p);
        // }
    }

    chunk_list_dump(&allocated_chunks);
    return 0;
}
