#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define BASE_HASHTABLE_SIZE 53
#define FIRST_PRIME_NUMBER 151 
#define SECOND_PRIME_NUMBER 173

typedef struct hashtable_item {
    char *key;
    char *value;
} ht_item;

typedef struct hashtable {
    int capacity;
    int size;
    ht_item **items;
} ht;

static ht_item DELETED_HASHTABLE_ITEM = {NULL, NULL};

int hash(char *key, int prime_number, int capacity) {
    long hash_value = 0;
    int s_len = strlen(key);

    for (int i = 0; i < s_len; i++) {
        hash_value += (long) pow(prime_number, s_len - (i + 1)) * key[i];
        hash_value = hash_value % capacity;
    }
    
    return (int) hash_value;

}

int get_hash(char *key, int capacity, int attempt) {
    int hash_a = hash(key, FIRST_PRIME_NUMBER, capacity);
    int hash_b = hash(key, SECOND_PRIME_NUMBER, capacity);
    
    return (hash_a + ((hash_b + 1) * attempt)) % capacity;
}

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

    int attempt = 0;
    int index = get_hash(key, ht->capacity, attempt);
    ht_item *current = ht->items[index];
    while(current != NULL) {
        attempt++;
        index = get_hash(key, ht->capacity, attempt);
        current = ht->items[index];
    }
    ht->items[index] = item;
    ht->size++;
}

void free_item(ht *ht, int index) {
    free(ht->items[index]->key);
    free(ht->items[index]->value);
    free(ht->items[index]);
}

void delete_item(ht *ht, char *key) {
    int attempt = 0;
    int index = get_hash(key, ht->capacity, attempt);
    ht_item *current = ht->items[index];
    while(current != NULL) {
        if (current != &DELETED_HASHTABLE_ITEM && (strcmp(current->key, key) == 0)) {
            free_item(ht, index);
            ht->items[index] = &DELETED_HASHTABLE_ITEM;
            ht->size--;
            break;
        }

        attempt++;
        index = get_hash(key, ht->capacity, attempt);
        current = ht->items[index];
    }
}

char *search_item(ht *ht, char *key) {
    int attempt = 0;
    int index = get_hash(key, ht->capacity, attempt);
    ht_item *current = ht->items[index];
    while(current != NULL) {
        if (current != &DELETED_HASHTABLE_ITEM && strcmp(current->key, key) == 0) {
            return current->value;
        }

        attempt++;
        index = get_hash(key, ht->capacity, attempt);
        current = ht->items[index];
    }

    return NULL;
}

void destroy_hashtable(ht *ht) {
    for(int i = 0; i < ht->capacity; i++) {
        if (ht->items[i] != NULL && ht->items[i] != &DELETED_HASHTABLE_ITEM) {
            free_item(ht, i);
        }
    }

    free(ht->items);
    free(ht);
}

int main() {
    ht *ht = init_ht();
    
    printf("%d\n", ht->capacity);
    printf("%zu\n", sizeof(struct hashtable));
    insert_item(ht, "name", "John Doe");
    insert_item(ht, "name", "John Cena");
    insert_item(ht, "name", "John Doe");
    insert_item(ht, "name", "John Doe");
    insert_item(ht, "name", "John Doe");
    /*
    printf("%s\n", ht->items[0]->key);
    printf("%s\n", ht->items[0]->value);
    */
    
    
    printf("size %d\n", ht->size);
    delete_item(ht, "name");
    delete_item(ht, "name");
    delete_item(ht, "name");
    delete_item(ht, "name");
    delete_item(ht, "name");
    printf("size %d\n", ht->size);
    printf("search item %s\n", search_item(ht, "name"));
    destroy_hashtable(ht);
    
}
