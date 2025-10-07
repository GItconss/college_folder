#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *intermediate = fopen("intermediate.txt", "r");
    FILE *optab_file = fopen("optab.txt", "r");
    FILE *symtab_file = fopen("symtab.txt", "r");
    FILE *output_file = fopen("output.txt", "w");
    FILE *listing_file = fopen("listing.txt", "w");

    if (!intermediate || !optab_file || !symtab_file || !output_file || !listing_file)
    {
        printf("Error: unable to open one or more files.\n");
        return 1;
    }

    char label[20], opcode[20], operand[20];
    char optab_opcode[20], optab_code[20];
    char sym_label[20], sym_address[20];
    int locctr, start_address = 0, program_length = 0;

    // Read first line (START)
    fscanf(intermediate, "%X %s %s %s", &locctr, label, opcode, operand);
    if (strcmp(opcode, "START") == 0)
    {
        start_address = (int)strtol(operand, NULL, 16);
        fprintf(output_file, "H^%-6s^%06X^", label, start_address);
    }

    // Compute program length
    rewind(intermediate);
    while (fscanf(intermediate, "%X %s %s %s", &locctr, label, opcode, operand) == 4)
    {
        if (strcmp(opcode, "END") == 0)
        {
            program_length = locctr - start_address;
            break;
        }
    }
    fprintf(output_file, "%06X\n", program_length);

    // Reset to start, skip first START line
    rewind(intermediate);
    fscanf(intermediate, "%X %s %s %s", &locctr, label, opcode, operand);

    fprintf(output_file, "T^%06X^", start_address);
    long text_length_pos = ftell(output_file);
    fprintf(output_file, "00"); // Placeholder for text record length
    int text_length = 0;

    char object_code[20];

    // Process lines
    while (fscanf(intermediate, "%X %s %s %s", &locctr, label, opcode, operand) == 4 &&
           strcmp(opcode, "END") != 0)
    {

        if (strcmp(label, "**") == 0)
            strcpy(label, "");
        if (strcmp(operand, "**") == 0)
            strcpy(operand, "");

        object_code[0] = '\0';
        int opcode_found = 0;

        rewind(optab_file);
        while (fscanf(optab_file, "%s %s", optab_opcode, optab_code) == 2)
        {
            if (strcmp(opcode, optab_opcode) == 0)
            {
                opcode_found = 1;
                char address[20] = "0000";

                if (strlen(operand) > 0)
                {
                    rewind(symtab_file);
                    while (fscanf(symtab_file, "%s %s", sym_label, sym_address) == 2)
                    {
                        if (strcmp(operand, sym_label) == 0)
                        {
                            strcpy(address, sym_address);
                            break;
                        }
                    }
                }

                sprintf(object_code, "%s%s", optab_code, address);
                fprintf(output_file, "^%s", object_code);
                text_length += 3;
                break;
            }
        }

        if (!opcode_found)
        {
            if (strcmp(opcode, "WORD") == 0)
            {
                sprintf(object_code, "%06X", atoi(operand));
                fprintf(output_file, "^%s", object_code);
                text_length += 3;
            }
            else if (strcmp(opcode, "BYTE") == 0)
            {
                if (operand[0] == 'C')
                {
                    char chars[20];
                    strncpy(chars, operand + 2, strlen(operand) - 3);
                    chars[strlen(operand) - 3] = '\0';
                    for (int i = 0; i < strlen(chars); i++)
                    {
                        char temp[5];
                        sprintf(temp, "%02X", (unsigned char)chars[i]);
                        strcat(object_code, temp);
                    }
                    fprintf(output_file, "^%s", object_code);
                    text_length += strlen(chars);
                }
                else if (operand[0] == 'X')
                {
                    char hexval[20];
                    strncpy(hexval, operand + 2, strlen(operand) - 3);
                    hexval[strlen(operand) - 3] = '\0';
                    sprintf(object_code, "%s", hexval);
                    fprintf(output_file, "^%s", object_code);
                    text_length += strlen(hexval) / 2;
                }
            }
        }

        // Write listing file
        fprintf(listing_file, "%04X\t%-6s\t%-6s\t%-6s\t%s\n",
                locctr, label, opcode, operand, object_code);
    }

    // Update text record length
    fseek(output_file, text_length_pos, SEEK_SET);
    fprintf(output_file, "%02X", text_length);
    fseek(output_file, 0, SEEK_END);

    fprintf(output_file, "\nE^%06X\n", start_address);

    fclose(intermediate);
    fclose(optab_file);
    fclose(symtab_file);
    fclose(output_file);
    fclose(listing_file);

    printf("PASS 2 complete.\nObject program written to output.txt\nListing file written to listing.txt\n");
    return 0;
}
