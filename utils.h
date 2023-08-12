#ifndef MMN14_UTILS_H
#define MMN14_UTILS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "language_definition.h"
#include "symbols_table.h"

/* Skips white space in a string by telling the index where white space ends */
#define SKIP_WHITE(string, index) \
        for (;string[(index)] && (isspace(string[index])); (++(index)))\
        ;
/*
        Concatenates two strings and allocates memory to the new string.
        @param first_str The first string to concatenate.
        @param second_str The second string to concatenate.
        return A pointer to the concatenated string.
*/
char *str_allocate_cat(char *first_str, char* second_str);

/*
        Splits a string into words by defined separators.
        @param string A pointer to the string to be split into words.
        @param separators By which separators to split the string.
        @param count A pointer to a variable to hold the number of words in the split string.
        @return A pointer to the first word in the split string.
*/
char **split_string(char *string, char *separators, int *count);

/*
        Frees the memory allocated to a split string.
        @param split_string The split string to be free.
        @param count The number of words in the string.
*/
void free_split_string(char **split_string, int count);


/*
        Prints an error message to the standard output.
        @param line The line where the error occurred (contains info about the file name and content of the line)
        @param format The formatted message to print.
        @param ... The variables needed to format the message. (Like in printf).
*/
void print_error_msg(line_info *line, const char *format, ...) ;


/*
        Prints a warning message to the standard output.
        @param line The line where the warning occurred (contains info about the file name and content of the line)
        @param format The formatted message to print.
        @param ... The variables needed to format the message. (Like in printf).
*/
void print_warning_msg(line_info *line, const char *format, ...);


/*
        Prints a data word to the standard output.
        @param word The data word to print.
*/

/*
        Freeing the code image.
        @param code_image The code image to be free
        @param ic The number of values in the list.
*/
void free_code_image(machine_w code_image[], long ic);

/*
        Creates a new machine word
        @return A pointer to the new machine word.
*/
machine_w *create_machine_w();


/*
        Updates the data symbols address in the symbol table.
        @param table The symbol table to update.
        @param ic The number of words in the code image.
*/
void update_data_symbols_address(s_table *table, long ic);

/*
        checks if a string is all digits.
        @param operand The string to check.
        @return TRUE if the string is all digits, FALSE otherwise.
*/
bool is_all_digits(const char *operand);


/*
        Checks if a string is a valid label.
        @param word The string to check.
        @return TRUE if the string is a valid label, FALSE otherwise.
*/
bool is_valid_label(char *word);

#endif 
