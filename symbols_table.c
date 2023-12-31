#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "symbols_table.h"
#include "language_definition.h"
#include "mcro_table.h"


/* Implementation of Symbols Table */

s_table *create_s_table(void){
    /* Allocate memory for table*/
    s_table *hashtable = malloc(sizeof(s_table));

    /* Allocate memory for the entries */
    hashtable->entries = malloc(sizeof(s_table_entry) * TABLE_SIZE);
    /* Initializing all the entries to be null */
    {
        int i;
        for (i=0;i<TABLE_SIZE; i++){
            hashtable->entries[i] = NULL;
        }
    }
    return hashtable;
}

s_table_entry *s_table_pair(const char *symbol, int symbol_addr, symbol_t symbol_type){
    /* Allocate memory for the entry */
    s_table_entry *entry = malloc(sizeof(s_table_entry));
    entry->symbol = malloc(strlen(symbol) + 1);
    entry->symbol_addr = symbol_addr;
    entry->symbol_type = symbol_type;

    /* Get the value of the key & the data. */
    strcpy(entry->symbol, symbol);
    entry->next = NULL;

    return entry;
}

void add_s_entry(s_table *hashtable, const char *symbol, int symbol_addr, symbol_t symbol_type){
    unsigned int bucket = hash(symbol);
    s_table_entry *prev;
    s_table_entry *entry = hashtable -> entries[bucket];
    if (entry == NULL){
        hashtable->entries[bucket] = s_table_pair(symbol, symbol_addr, symbol_type);
        return;
    }

    /* Iterate through each entry to until the end is reach or key match found*/
    while (entry != NULL) {
        if(strcmp(entry->symbol, symbol) == 0) {
            /* Match found - Will replace the existing key with new one */
            free(entry->symbol);


            entry->symbol = malloc(strlen(symbol) + 1);
            entry->symbol_addr = symbol_addr;
            entry->symbol_type = symbol_type;


            strcpy(entry->symbol, symbol);
            return;
        }
        /* Iterate to the next node */
        prev = entry;
        entry = prev->next;
    }
    /* Reached the end of the linked list, add another node with the pair */
    prev->next = s_table_pair(symbol, symbol_addr, symbol_type);
}

s_table_entry *get_from_s_table(s_table *hashtable, const char *symbol) {
    unsigned int bucket = hash(symbol);

    /* try to find a valid bucket */
    s_table_entry *entry = hashtable->entries[bucket];

    /* no bucket means no entry */
    if (entry == NULL) {
        return NULL;
    }

    /* walk through each entry in the bucket, which could just be a single thing */
    while (entry != NULL) {
        /* return value if found */
        if (strcmp(entry->symbol, symbol) == 0) {
            return entry;
        }

        /* proceed to next key if available */
        entry = entry->next;
    }

    /* reaching here means there were >= 1 entries but no key match */
    return NULL;
}

void delete_s_entry(s_table *hashtable, const char *symbol) {
    unsigned int bucket = hash(symbol);
    s_table_entry *prev;
    int idx = 0;
    /* try to find a valid bucket */
    s_table_entry *entry = hashtable->entries[bucket];

    /* no bucket means no entry */
    if (entry == NULL) {
        return;
    }
    /* walk through each entry until either the end is reached or a matching key is found */
    while (entry != NULL) {
        /* check key */
        if (strcmp(entry->symbol, symbol) == 0) {
            /* first item and no next entry */
            if (entry->next == NULL && idx == 0) {
                hashtable->entries[bucket] = NULL;
            }

            /* first item with a next entry */
            if (entry->next != NULL && idx == 0) {
                hashtable->entries[bucket] = entry->next;
            }

            /* last item */
            if (entry->next == NULL && idx != 0) {
                prev->next = NULL;
            }

            /* middle item */
            if (entry->next != NULL && idx != 0) {
                prev->next = entry->next;
            }

            /* free the deleted entry */
            free(entry->symbol);
            free(entry);

            return;
        }

        /* walk to next */
        prev = entry;
        entry = prev->next;

        ++idx;
    }
}

void s_table_dump(s_table *hashtable) {
    int i;
    for (i=0; i < TABLE_SIZE; ++i) {
        s_table_entry *entry = hashtable->entries[i];

        if (entry == NULL) {
            continue;
        }

        for(;;) {
            printf("%s[%d] in %d\n", entry->symbol, entry->symbol_type, (entry->symbol_addr) + 100);
            if (entry->next == NULL) {
                break;
            }
            entry = entry->next;
        }
        /*printf("\n"); */
    }
}

void free_s_table(s_table *hashtable) {
    int i;
    /* free entries */
    for (i=0; i < TABLE_SIZE; i++) {
        if (hashtable->entries[i] != NULL) {
            s_table_entry *entry = hashtable->entries[i];
            while (entry != NULL) {
                s_table_entry *prev = entry;
                entry = entry->next;
                free(prev->symbol);
                free(prev);
            }
        }
    }

    /* free table */
    free(hashtable->entries);
    free(hashtable);
}