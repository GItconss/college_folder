#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char opcode[10], operand[10], label[10];
char code[10], mnemonic[10];
char symLabel[10];
int symAddr;

int searchSymtab(char *symbol, FILE *symtab) {
    rewind(symtab);
    while (fscanf(symtab, "%s\t%X", symLabel, &symAddr) == 2) {
        if (strcmp(symLabel, symbol) == 0) {
            return symAddr;
        }
    }
    return -1;
}

int main() {
    FILE *fp1, *fp2, *fp3, *fp4, *fp5;
    int locctr = 0, startAddr = 0, programLength, lastAddr = 0;
    char objCode[50];
    char programName[10];  

    fp1 = fopen("output.txt", "r");      // intermediate file from Pass 1
    fp2 = fopen("optab.txt", "r");       // operation table
    fp3 = fopen("symtab.txt", "r");      // symbol table
    fp4 = fopen("objectcode.txt", "w");  // object program
    fp5 = fopen("listing.txt", "w");     // listing file

    if (fp1 == NULL || fp2 == NULL || fp3 == NULL || fp4 == NULL || fp5 == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    // Read first line from intermediate file
    fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        startAddr = (int)strtol(operand, NULL, 16);
        strcpy(programName, label);  
        fscanf(fp1, "%X\t%s\t%s\t%s", &locctr, label, opcode, operand);
    } else {
        startAddr = 0;
        locctr = 0;
        strcpy(programName, "      "); // default blank name
    }

    // Write HEADER record first
    fprintf(fp4, "H^%-6s^%06X^000000\n", programName, startAddr);  

    int textStart = locctr;
    char textRecord[70] = "";
    int textLen = 0;

    // Process each line until END
    while (strcmp(opcode, "END") != 0) {
        int found = 0;
        rewind(fp2);
        strcpy(objCode, "");

        // Search OPTAB
        while (fscanf(fp2, "%s\t%s", code, mnemonic) == 2) {
            if (strcmp(opcode, code) == 0) {
                int operandAddr = 0;
                if (strcmp(operand, "**") != 0) {
                    operandAddr = searchSymtab(operand, fp3);
                }
                // Special case: RSUB has no operand
                if (strcmp(opcode, "RSUB") == 0) {
                    strcpy(objCode, "4C0000");
                } else {
                    sprintf(objCode, "%s%04X", mnemonic, operandAddr);
                }
                found = 1;
                break;
            }
        }

        // If not in OPTAB
        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                sprintf(objCode, "%06X", atoi(operand));
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C') {
                    int i;
                    strcpy(objCode, "");
                    for (i = 2; operand[i] != '\''; i++) {
                        char hex[3];
                        sprintf(hex, "%02X", operand[i]);
                        strcat(objCode, hex);
                    }
                } else if (operand[0] == 'X') {
                    strncpy(objCode, &operand[2], strlen(operand) - 3);
                    objCode[strlen(operand) - 3] = '\0';
                }
            } else {
                strcpy(objCode, "");
            }
        }

        // Write object code to Text record
        if (strlen(objCode) > 0) {
            if (textLen + strlen(objCode) / 2 > 30) {
                fprintf(fp4, "T^%06X^%02X%s\n", textStart, textLen, textRecord);
                textStart = locctr;
                textLen = 0;
                strcpy(textRecord, "");
            }

            char temp[25];
            snprintf(temp, sizeof(temp), "^%s", objCode);
            strcat(textRecord, temp);
            textLen += strlen(objCode) / 2;
        }

        // --- Write to LISTING FILE ---
        fprintf(fp5, "%04X\t%-6s\t%-6s\t%-6s\t%s\n",
                locctr, label, opcode, operand, objCode);

        lastAddr = locctr;  // keep track of last address
        fscanf(fp1, "%X\t%s\t%s\t%s", &locctr, label, opcode, operand);
    }

    // Write last text record
    if (textLen > 0) {
        fprintf(fp4, "T^%06X^%02X%s\n", textStart, textLen, textRecord);
    }

    // Program length
    programLength = lastAddr - startAddr;

    // Update HEADER with actual program length
    fseek(fp4, 0, SEEK_SET);
    fprintf(fp4, "H^%-6s^%06X^%06X\n", programName, startAddr, programLength);

    // End record
    fprintf(fp4, "E^%06X\n", startAddr);

    printf("Pass 2 completed.\nObject program -> objectcode.txt\nListing file  -> listing.txt\n");

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);

    return 0;
}
    fclose(intermediate);
    fclose(optab_file);
    fclose(symtab_file);
    fclose(output_file);

    printf("PASS 2 complete. Object program written to output.txt\n");

    return 0;
}
