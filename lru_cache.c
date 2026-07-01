#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    char key[64];
    char context_data[256];
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    int capacity;
    int size;
    Node* head;
    Node* tail;
} LRUCache;

Node* create_lru_node(const char* k, const char* v) {
    Node* n = (Node*)malloc(sizeof(Node));
    strncpy(n->key, k, sizeof(n->key) - 1);
    strncpy(n->context_data, v, sizeof(n->context_data) - 1);
    n->prev = n->next = NULL;
    return n;
}

#ifdef _WIN32
    __declspec(dllexport) LRUCache* init_lru(int cap);
    __declspec(dllexport) const char* get_cached_context(LRUCache* cache, const char* key);
    __declspec(dllexport) void put_cached_context(LRUCache* cache, const char* key, const char* value);
    __declspec(dllexport) void free_lru(LRUCache* cache);
#endif

LRUCache* init_lru(int cap) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->capacity = cap; cache->size = 0;
    cache->head = cache->tail = NULL;
    return cache;
}

void detach_node(LRUCache* cache, Node* node) {
    if (node->prev) node->prev->next = node->next;
    else cache->head = node->next;
    if (node->next) node->next->prev = node->prev;
    else cache->tail = node->prev;
}

void move_to_head(LRUCache* cache, Node* node) {
    node->next = cache->head;
    node->prev = NULL;
    if (cache->head) cache->head->prev = node;
    cache->head = node;
    if (!cache->tail) cache->tail = node;
}

const char* get_cached_context(LRUCache* cache, const char* key) {
    Node* current = cache->head;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            detach_node(cache, current);
            move_to_head(cache, current);
            return current->context_data;
        }
        current = current->next;
    }
    return "CACHE_MISS";
}

void put_cached_context(LRUCache* cache, const char* key, const char* value) {
    Node* current = cache->head;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            strncpy(current->context_data, value, sizeof(current->context_data) - 1);
            detach_node(cache, current);
            move_to_head(cache, current);
            return;
        }
        current = current->next;
    }

    if (cache->size >= cache->capacity) {
        Node* old_tail = cache->tail;
        detach_node(cache, old_tail);
        free(old_tail);
        cache->size--;
    }

    Node* new_node = create_lru_node(key, value);
    move_to_head(cache, new_node);
    cache->size++;
}

void free_lru(LRUCache* cache) {
    Node* current = cache->head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(cache);
}
