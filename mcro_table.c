#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mcro_table.h"

unsigned int hash(const char *key) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);
    /* Do several rounds of multiplication */
    for (i = 0; i < key_len; i++){
        value = value * 37 + key[i];
    }
    value = value % TABLE_SIZE; /* Make sure value is between 0 and TABLE_SIZE */

    return value;
}

/* Implementation of Macros Table */

m_table *create_m_table(void){
    /* Allocate memory for table*/
    m_table *hashtable = malloc(sizeof(m_table));

    /* Allocate memory for the entries */
    hashtable->entries = malloc(sizeof(m_table_entry) * TABLE_SIZE);
    /* Initializing all the entries to be null */
    {
        int i=0;
        for (i=0;i<TABLE_SIZE; i++){
            hashtable->entries[i] = NULL;
        }
    }
    return hashtable;
}

m_table_entry *m_table_pair(const char *macro_name, const char *macro_content){
    /* Allocate memory for the entry */
    m_table_entry *entry = malloc(sizeof(m_table_entry));
    entry->macro_name = malloc(strlen(macro_name) + 1);
    entry->macro_content = malloc(strlen(macro_content)+ 1);


    /* Get the value of the key & the data. */
    strcpy(entry->macro_name, macro_name);
    strcpy(entry->macro_content , macro_content);
    entry->next = NULL;

    return entry;
}

void add_m_entry(m_table *hashtable, const char *macro_name, const char *macro_content){
    unsigned int bucket = hash(macro_name);
    m_table_entry *prev;
    m_table_entry *entry = hashtable -> entries[bucket];
    if (entry == NULL){
        hashtable->entries[bucket] = m_table_pair(macro_name, macro_content);
        return;
    }

    /* Iterate through each entry to until the end is reach or key match found*/
    while (entry != NULL) {
        if(strcmp(entry->macro_name, macro_name) == 0) {
            /* Match found - Will replace the existing key with new one */
            free(entry->macro_name);
            free(entry->macro_content);


            entry->macro_name = malloc(strlen(macro_name) + 1);
            entry->macro_content = malloc(strlen(macro_content) + 1);


            strcpy(entry->macro_name, macro_name);
            strcpy(entry->macro_content, macro_content);
            return;
        }
        /* Iterate to the next node */
        prev = entry;
        entry = prev->next;
    }
    /* Reached the end of the linked list, add another node with the pair */
    prev->next = m_table_pair(macro_name,macro_content);
}

char *get_from_m_table(m_table *hashtable, const char *macro_name) {
    unsigned int bucket = hash(macro_name);

    /* try to find a valid bucket */
    m_table_entry *entry = hashtable->entries[bucket];

    /* no bucket means no entry */
    if (entry == NULL) {
        return NULL;
    }

    /* walk through each entry in the bucket, which could just be a single thing */
    while (entry != NULL) {
        /* return value if found */
        if (strcmp(entry->macro_name, macro_name) == 0) {
            return entry->macro_content;
        }

        /* proceed to next key if available */
        entry = entry->next;
    }

    /* reaching here means there were >= 1 entries but no key match */
    return NULL;
}

void delete_m_entry(m_table *hashtable, const char *macro_name) {
    unsigned int bucket = hash(macro_name);
    m_table_entry *prev;
    int idx = 0;
    /* try to find a valid bucket */
    m_table_entry *entry = hashtable->entries[bucket];

    /* no bucket means no entry */
    if (entry == NULL) {
        return;
    }
    /* walk through each entry until either the end is reached or a matching key is found */
    while (entry != NULL) {
        /* check key */
        if (strcmp(entry->macro_name, macro_name) == 0) {
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
            free(entry->macro_name);
            free(entry->macro_content);
            free(entry);

            return;
        }

        /* walk to next */
        prev = entry;
        entry = prev->next;

        ++idx;
    }
}

void m_table_dump(m_table *hashtable) {
    int i;
    for (i=0; i < TABLE_SIZE; ++i) {
        m_table_entry *entry = hashtable->entries[i];

        if (entry == NULL) {
            continue;
        }
        printf("bucket[%d]: ", i);
        for(;;) {
            printf("%s=%s ", entry->macro_name, entry->macro_content);
            if (entry->next == NULL) {
                break;
            }
            entry = entry->next;
        }
        printf("\n");
    }
}

void free_m_table(m_table *hashtable) {
    int i;
    /* free entries */
    for (i=0; i < TABLE_SIZE; i++) {
        if (hashtable->entries[i] != NULL) {
            m_table_entry *entry = hashtable->entries[i];
            while (entry != NULL) {
                m_table_entry *prev = entry;
                entry = entry->next;
                free(prev->macro_name);
                free(prev->macro_content);
                free(prev);
            }
        }
    }

    /* free table */
    free(hashtable->entries);
    free(hashtable);
}
