#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define HEAP_CAPACITY 640000
#define POBJECT_LIST_CAPACITY 1024

#define UNIMPLEMENTED \
    do { \
        fprintf(stderr, "%s:%d: TODO: %s is not implemented yet\n", \
                __FILE__, __LINE__, __func__); \
        abort(); \
    } while(0)

typedef struct {
    void *start;
    size_t size;
} PObject;

typedef struct {
    size_t count;
    PObject pobjects [POBJECT_LIST_CAPACITY];
} PObject_List;

int pobject_list_find(const PObject_List *list, void *ptr)
{
    (void) list;
    (void) ptr;
    UNIMPLEMENTED;
    return -1;
}

void pobject_list_dump(const PObject_List *list)
{
    printf("PObjects (%zu):\n", list->count);
    for (size_t i = 0; i < list->count; ++i) {
        printf("  start: %p, size: %zu\n",
               list->pobjects[i].start,
               list->pobjects[i].size);
    }
}

void pobject_list_insert(PObject_List *list, void *start, size_t size)
{
    assert(list->count < POBJECT_LIST_CAPACITY);
    list->pobjects[list->count].start = start;
    list->pobjects[list->count].size = size;

    for (size_t i = list->count; i > 0
            && list->pobjects[i].start < list->pobjects[i - 1].start;
            --i) {
        const PObject t = list->pobjects[i];
        list->pobjects[i] = list->pobjects[i - 1];
        list->pobjects[i - 1] = t;
    }

    list->count += 1;
}

void pobject_list_remove(PObject_List *list, size_t index)
{
    (void) list;
    (void) index;
    UNIMPLEMENTED;
}

char heap[HEAP_CAPACITY] = {0};
size_t heap_size = 0;

PObject_List allocated_pobjects = {0};
PObject_List freed_pobjects = {0};

void *heap_alloc(size_t size)
{
    if (size == 0) {
        return NULL;
    }

    assert(heap_size + size <= HEAP_CAPACITY);
    void *ptr = heap + heap_size;
    heap_size += size;
    pobject_list_insert(&allocated_pobjects, ptr, size);

    return ptr;
}

// O(allocated_pobjects)
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

    pobject_list_dump(&allocated_pobjects);
    return 0;
}
