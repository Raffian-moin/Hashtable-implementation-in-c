#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define BASE_HASHTABLE_SIZE 53

typedef struct hashtable_item {
    char *key;
    char *value;
} ht_item;

typedef struct hashtable {
    size_t capacity;
    size_t size;
    ht_item **items;
} ht;

ht *init_ht() {
    ht *ht_ptr = malloc(sizeof(ht));
    ht_ptr->capacity = BASE_HASHTABLE_SIZE;
    ht_ptr->size = 0;
    ht_ptr->items = calloc((size_t) ht_ptr->capacity, sizeof(ht_item *));
    return ht_ptr;
}

void insert_item(ht *ht, char *key, char *value) {
    ht_item *item = malloc(sizeof(ht_item));
    item->key = strdup(key);
    item->value = strdup(value);
    ht->items[0] = item;
}

int main() {
    ht *ht = init_ht();
    
    printf("%zu\n", ht->capacity);
    printf("%zu\n", sizeof(struct hashtable));
    insert_item(ht, "name", "John Doe");
    printf("%s\n", ht->items[0]->key);
    printf("%s\n", ht->items[0]->value);
    
}
