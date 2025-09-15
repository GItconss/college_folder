#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {
    FILE *input_file = fopen("input.txt", "r");
    FILE *optab_file = fopen("optab.txt", "r");
    FILE *symtab_file = fopen("symtab.txt", "w+");
    FILE *intermediate = fopen("intermediate.txt", "w");

    if (!input_file || !optab_file || !symtab_file || !intermediate) {
        printf("Error: unable to open one or more files.\n");
        return 1;
    }

    char label[20], opcode[20], operand[20];
    char optab_opcode[20], optab_code[20];
    int locctr = 0, start_address = 0;
    bool opcode_found;

    
    fscanf(input_file, "%s %s %s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        start_address = (int)strtol(operand, NULL, 16);
        locctr = start_address;
        fprintf(intermediate, "%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        fgets(operand, sizeof(operand), input_file);
    } else {
        locctr = 0;
    }

    
    while (fscanf(input_file, "%s %s %s", label, opcode, operand) == 3 &&
           strcmp(opcode, "END") != 0) {

        if (strcmp(label, "-") != 0) {
            fprintf(symtab_file, "%s\t%04X\n", label, locctr);
        }

        rewind(optab_file);
        opcode_found = false;
        while (fscanf(optab_file, "%s %s", optab_opcode, optab_code) == 2) {
            if (strcmp(opcode, optab_opcode) == 0) {
                opcode_found = true;
                break;
            }
        }

        fprintf(intermediate, "%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        if (opcode_found) 
         {
            locctr += 3;
         } 
        else if (strcmp(opcode, "WORD") == 0)
         {
            locctr += 3;
         } 
        else if (strcmp(opcode, "RESW") == 0)
         {
            locctr += 3 * atoi(operand);
        } 
        else if (strcmp(opcode, "RESB") == 0) 
        {
            locctr += atoi(operand);
        } 
        else if (strcmp(opcode, "BYTE") == 0)
         {
            int len = strlen(operand);
            if (operand[0] == 'C' && operand[1]=='\'') {
                locctr += len - 3; 
            } 
            else if (operand[0] == 'X' && operand[1]=='\'') 
            {
                locctr += (len - 3) / 2; 
            }
        } 
        else 
        {
            printf("Error: invalid opcode %s\n", opcode);
            return 1;
        }
    }


    fprintf(intermediate, "%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    int program_length = locctr - start_address;
    printf("Program length = %04X\n", program_length);

    fclose(input_file);
    fclose(optab_file);
    fclose(symtab_file);
    fclose(intermediate);

    return 0;
}

