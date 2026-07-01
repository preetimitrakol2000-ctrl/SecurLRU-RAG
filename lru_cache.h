#ifndef LRU_CACHE_H
#define LRU_CACHE_H

typedef struct Node Node;
typedef struct LRUCache LRUCache;
LRUCache* init_lru(int cap);
const char* get_cached_context(LRUCache* cache, const char* key);
void put_cached_context(LRUCache* cache, const char* key, const char* value);
void free_lru(LRUCache* cache);

#endif
