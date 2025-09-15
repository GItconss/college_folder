#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *intermediate = fopen("intermediate.txt", "r");
    FILE *optab_file = fopen("optab.txt", "r");
    FILE *symtab_file = fopen("symtab.txt", "r");
    FILE *output_file = fopen("output.txt", "w");

    if (!intermediate || !optab_file || !symtab_file || !output_file) {
        printf("Error: unable to open one or more files.\n");
        return 1;
    }

    char label[20], opcode[20], operand[20];
    char optab_opcode[20], optab_code[20];
    char sym_label[20], sym_address[20];
    int locctr, start_address = 0, program_length = 0;

    // First line should be START
    fscanf(intermediate, "%X %s %s %s", &locctr, label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        start_address = (int)strtol(operand, NULL, 16);
        fprintf(output_file, "H^%s^%06X^", label, start_address);
        fgets(operand, sizeof(operand), intermediate); // move to next line
    }

    // Compute program length (last line in intermediate has END)
    fseek(intermediate, -50, SEEK_END);
    while (fscanf(intermediate, "%X %s %s %s", &locctr, label, opcode, operand) == 4) {
        if (strcmp(opcode, "END") == 0) {
            program_length = locctr - start_address;
            break;
        }
    }
    fprintf(output_file, "%06X\n", program_length);

    // Reset file pointer to start
    rewind(intermediate);
    fscanf(intermediate, "%X %s %s %s", &locctr, label, opcode, operand); // skip first line

    fprintf(output_file, "T^%06X^", start_address);

    char object_code[20];
    int text_length_pos = ftell(output_file);
    fprintf(output_file, "00");  // placeholder for text record length

    int text_length = 0;

    // Process intermediate file
    while (fscanf(intermediate, "%X %s %s %s", &locctr, label, opcode, operand) == 4 &&
           strcmp(opcode, "END") != 0) {

        rewind(optab_file);
        int opcode_found = 0;

        while (fscanf(optab_file, "%s %s", optab_opcode, optab_code) == 2) {
            if (strcmp(opcode, optab_opcode) == 0) {
                // search operand in SYMTAB
                rewind(symtab_file);
                while (fscanf(symtab_file, "%s %s", sym_label, sym_address) == 2) {
                    if (strcmp(operand, sym_label) == 0) {
                        sprintf(object_code, "%s%s", optab_code, sym_address);
                        fprintf(output_file, "^%s", object_code);
                        text_length += 3;
                        break;
                    }
                }
                opcode_found = 1;
                break;
            }
        }

        if (!opcode_found) {
            if (strcmp(opcode, "WORD") == 0) {
                sprintf(object_code, "%06X", atoi(operand));
                fprintf(output_file, "^%s", object_code);
                text_length += 3;
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C') {
                    int i;
                    char chars[20];
                    strncpy(chars, operand + 2, strlen(operand) - 3);
                    chars[strlen(operand) - 3] = '\0';
                    for (i = 0; i < strlen(chars); i++) {
                        sprintf(object_code, "%02X", chars[i]);
                        fprintf(output_file, "^%s", object_code);
                        text_length++;
                    }
                } else if (operand[0] == 'X') {
                    char hexval[20];
                    strncpy(hexval, operand + 2, strlen(operand) - 3);
                    hexval[strlen(operand) - 3] = '\0';
                    fprintf(output_file, "^%s", hexval);
                    text_length += strlen(hexval) / 2;
                }
            }
        }
    }

    // Update text record length
    fseek(output_file, text_length_pos, SEEK_SET);
    fprintf(output_file, "%02X", text_length);
    fseek(output_file, 0, SEEK_END);

    // Write End record
    fprintf(output_file, "\nE^%06X\n", start_address);

    fclose(intermediate);
    fclose(optab_file);
    fclose(symtab_file);
    fclose(output_file);

    printf("PASS 2 complete. Object program written to output.txt\n");

    return 0;
}
