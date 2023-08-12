#ifndef MMN14_SECOND_PASS_H
#define MMN14_SECOND_PASS_H

#include "symbols_table.h"
#include "language_definition.h"
#include "lexer.h"

/*
    This function processes a line in the second pass of the assembler.
    @param lt The lex tree of the line (Abstract Syntax Tree)
    @param table The symbol table
    @param line The processed line information
    @return TRUE if the line was processed successfully, FALSE otherwise
*/
bool second_pass_line_process(struct lex_tree lt, s_table *table, line_info line);

/*
    This function encodes the labels into the code image.
    @param symbol_table The symbol table
    @param code_image The code image
    @param ic The instruction counter
*/
void second_pass_label_encoding(s_table *symbol_table, machine_w *code_image, long ic);

#endif 
