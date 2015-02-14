// Copyright (c) 2014 Edd Mann
// http://eddmann.com/posts/implementing-a-dynamic-vector-array-in-c/

#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

void vector_init(vector *v)
{
    v->capacity = VECTOR_INIT_CAPACITY;
    v->total = 0;
    v->items = malloc(sizeof(void *) * v->capacity);
}

int vector_total(vector *v)
{
    return v->total;
}

static void vector_resize(vector *v, int capacity)
{
#ifdef DEBUG_ON
    printf("vector_resize: %d to %d\n", v->capacity, capacity);
#endif
    
    void **items = realloc(v->items, sizeof(void *) * capacity);
    if (items) {
        v->items = items;
        v->capacity = capacity;
    }
}

void vector_add(vector *v, void *item)
{
    if (v->capacity == v->total)
        vector_resize(v, v->capacity * 2);
    v->items[v->total++] = item;
}

void vector_set(vector *v, int index, void *item)
{
    if (index >= 0 && index < v->total)
        v->items[index] = item;
}

void *vector_get(vector *v, int index)
{
    if (index >= 0 && index < v->total)
        return v->items[index];
    return NULL;
}

void vector_delete(vector *v, int index)
{
    if (index < 0 || index >= v->total)
        return;
    
    v->items[index] = NULL;

    /* Bug fix - Yanick Castonguay - 02/11/2015 */
    for (int i = index; i < v->total - 1; i++) {
        v->items[i] = v->items[i + 1];
        v->items[i + 1] = NULL;
    }

    v->total--;
    
    if (v->total > 0 && v->total == v->capacity / 4)
        vector_resize(v, v->capacity / 2);
}

void vector_free(vector *v)
{
    free(v->items);
}

/* BEGIN - My addition - Yanick Castonguay - 02/09/2015 */
void vector_insert(vector *v, int index, void *item) {
    int count = vector_total(v);

    void* lastItem = vector_get(v, count-1);
    vector_add(v, lastItem);

    for(int a = count - 1; a >= index; a--) {
        void* itemToMove = vector_get(v, a);
        vector_set(v, a+1, itemToMove);
    }

    vector_set(v, index, item);
}
/* END - My addition - Yanick Castonguay - 02/09/2015 */