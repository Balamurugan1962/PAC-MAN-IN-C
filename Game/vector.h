#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void **data;
    size_t size;
    size_t capacity;
} Vector;

Vector* vector_create();
void vector_destroy(Vector *vec);
void vector_push_back(Vector *vec, void *value);
void* vector_at(Vector *vec, size_t index);
size_t vector_size(Vector *vec);

Vector* vector_create() {
    Vector *vec = (Vector*)malloc(sizeof(Vector));
    if (vec == NULL) {
        perror("Failed to allocate memory for vector");
        exit(EXIT_FAILURE);
    }
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
    return vec;
}

void vector_destroy(Vector *vec) {
    free(vec->data);
    free(vec);
}

void vector_push_back(Vector *vec, void *value) {
    if (vec->size >= vec->capacity) {
        vec->capacity = (vec->capacity == 0) ? 1 : vec->capacity * 2;
        vec->data = (void**)realloc(vec->data, vec->capacity * sizeof(void*));
        if (vec->data == NULL) {
            perror("Failed to reallocate memory for vector");
            exit(EXIT_FAILURE);
        }
    }
    vec->data[vec->size++] = value;
}

void* vector_at(Vector *vec, size_t index) {
    if (index < vec->size) {
        return vec->data[index];
    } else {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

size_t vector_size(Vector *vec) {
    return vec->size;
}


#endif /* VECTOR_H */
