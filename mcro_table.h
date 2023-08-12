#ifndef MMN14_MCRO_TABLE_H
#define MMN14_MCRO_TABLE_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "language_definition.h"

#define TABLE_SIZE 64

/* Macros Table Implementation */
/* Define an entry in a macros table */
typedef struct m_table_entry{
    char *macro_name;
    char *macro_content;
    struct m_table_entry *next;
} m_table_entry;

/* Define a table */
typedef struct {
    m_table_entry **entries;
} m_table;

/*
    The hash function for the function
    @param key The key of the value to be inserted to the table
    @return A value from 0 to TABLE_SIZE
*/
unsigned int hash(const char *key);

/*
    Creates an empty Macros Table
    @return A pointer to the table
*/
m_table *create_m_table(void);

/*
    Add an entry to the table
    @param hashtable Pointer to the table to add the entry to.
    @param key Pointer to the key of the data.
    @param data Pointer to the data.
*/
void add_m_entry(m_table *hashtable, const char *macro_name, const char *macro_content);

/*
    Allocating memory to the macro_name and the macro_content and filling the memory
    @param key Pointer to the key of the pair.
    @param data Pointer to the data of the pair.
    @return A table_entry object with next set to null.
*/
m_table_entry *m_table_pair(const char *macro_name, const char *macro_content);

/*
    Gets a macro content from a macros table
    @param hashtable A pointer to the macros table
    @param macro_name The macro to get its content
    return A pointer to the macro content
 */
char *get_from_m_table(m_table *hashtable, const char *macro_name);

/*
    Deletes an entry from a macros table
    @param hashtable Pointer to the macros table
    @param macro_name The macro to delete from the table
*/
void delete_m_entry(m_table *hashtable, const char *macro_name);

/*
    Prints a macros table
    @param hashtable A pointer to the table to be printed
*/
void m_table_dump(m_table *hashtable);

/*
    Frees the memory of a macro table
    @param hashtable A pointer to the table to be freed
*/
void free_m_table(m_table *hashtable);




#endif 
