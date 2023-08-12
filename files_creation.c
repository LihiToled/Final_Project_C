#include <stdio.h>
#include <stdlib.h>
#include "language_definition.h"
#include "utils.h"
#include "symbols_table.h"
#include "mcro_table.h"
#define BASE64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" /*array of base64 characters */


void write_obj_file(char *filename, machine_w code_image[], long ic, data_w data_image[], long dc){
    FILE *file_des;
    int i;
    unsigned int value;
    char *obj_filename = str_allocate_cat(filename, ".ob");
    const char *const b64_chars= BASE64;
    unsigned int msb,lsb;

    /* Try to create a new .ob file */
    file_des = fopen(obj_filename, "w");
    if(file_des == NULL){
        printf("Couldn't open the file %s.\n", obj_filename);
        free(obj_filename);
        return;
    }

    fprintf(file_des, "%ld %ld\n", ic, dc); /* Print the header */
    /* Print the code image */
    for(i = 0; i < ic; i++){
        if(code_image[i].word.f_word != NULL){
            value = *(unsigned int*) code_image[i].word.f_word;
        }
        msb = (value >> 6) & 0x3F ;
        lsb = value & 0x3F;
        fprintf(file_des,"%c%c",b64_chars[msb],b64_chars[lsb]);

        fprintf(file_des, "\n");
    }
    /* Print the data image */
    for(i = 0; i < dc; i++){
        value = data_image[i].data;
        msb = (value >> 6)&0x3F ;
        lsb = value & 0x3F;
        fprintf(file_des,"%c%c",b64_chars[msb],b64_chars[lsb]);

        fprintf(file_des, "\n");
    }
    /* Free the allocated memory */
    free(obj_filename);
    fclose(file_des);
}


void write_ent_file(char *filename, s_table *symbol_table){
    int i;
    FILE *file_des;
    char *ent_filename = str_allocate_cat(filename, ".ent");

    /* Try to create .ent file */
    file_des = fopen(ent_filename, "w");
    if(file_des == NULL){
        printf("Couldn't open the file %s.\n", ent_filename);
        free(ent_filename);
        return;
    }
    /* Print the entry symbols */

    for (i=0; i < TABLE_SIZE; ++i) {
        s_table_entry *entry = symbol_table->entries[i];

        if (entry == NULL) {
            continue;
        }

        for(;;) {
            if(entry->symbol_type == ENTRY_SYMBOL){
                fprintf(file_des, "%s\t\t%d\n", entry->symbol, (entry->symbol_addr) + 100);
            }
            if (entry->next == NULL) {
                break;
            }
            entry = entry->next;
        }
    }


    /* Free the allocated memory */
    free(ent_filename);
    fclose(file_des);
}



void write_ext_file(char *filename, s_table *symbol_table, machine_w code_image[], long ic){
    int num = 0; /* Counts the number of times used an .extern instruction */
    int i;
    FILE *file_des;
    char *ext_filename = str_allocate_cat(filename, ".ext");

    /* Check if there was an .extern instruction in the file. */
    for(i = 0; i < ic; i++){
        if(code_image[i].label != NULL){
            num++;
        }
    }
    if(num == 0){
        free(ext_filename);
        return;
    }
    /* Try to create .ext file */
    file_des = fopen(ext_filename, "w");
    if(file_des == NULL){
        printf("Couldn't open the file %s.\n", ext_filename);
        free(ext_filename);
        return;
    }
    /* Print the extern symbols */
    for(i=0; i < ic; i++){
        if(code_image[i].label != NULL){
            s_table_entry *entry = get_from_s_table(symbol_table, code_image[i].label);
            if(entry->symbol_type == EXTERN_SYMBOL){
                fprintf(file_des, "%s   %d\n",entry->symbol,  i + IC_INIT_VALUE);
            }
        }
    }
    /* Free the allocated memory */
    free(ext_filename);
    fclose(file_des);
}
