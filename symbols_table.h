#ifndef MMN14_SYMBOLS_TABLE_H
#define MMN14_SYMBOLS_TABLE_H

#include "language_definition.h"
/* Symbols Table Implementation */
/* Define an entry in a symbols table */
typedef struct s_table_entry{
    char *symbol;
    int symbol_addr;
    symbol_t symbol_type;
    struct s_table_entry *next;
} s_table_entry;

/* Define a symbol table */
typedef struct {
    s_table_entry **entries;
} s_table;

/*
    Creates an empty Symbol Table
    @return A pointer to the table
*/
s_table *create_s_table(void);

/*
    Add an entry to the table
    @param hashtable Pointer to the table to add the entry to.
    @param key Pointer to the key of the data.
    @param data Pointer to the data.
*/
void add_s_entry(s_table *hashtable, const char *symbol, int symbol_addr, symbol_t symbol_type);

/*
    Allocating memory to the symbol name and assigning the symbol address and type.
    @param key Pointer to the key of the pair.
    @param data Pointer to the data of the pair.
    @return A table_entry object with next set to null.
*/
s_table_entry *s_table_pair(const char *symbol, int symbol_addr, symbol_t symbol_type);

/*
    Gets a symbol entry from a macros table
    @param hashtable A pointer to the macros table
    @param symbol The symbol to get its entry
    return A pointer to the symbol entry
 */
s_table_entry *get_from_s_table(s_table *hashtable, const char *symbol);

/*
    Deletes an entry from a symbol table
    @param hashtable Pointer to the symbol table
    @param symbol The symbol to delete from the table
*/
void delete_s_entry(s_table *hashtable, const char *symbol);

/*
    Prints a symbol table
    @param hashtable A pointer to the table to be printed
*/
void s_table_dump(s_table *hashtable);

/*
    Frees the memory of a symbol table
    @param hashtable A pointer to the table to be freed
*/
void free_s_table(s_table *hashtable);



#endif 
