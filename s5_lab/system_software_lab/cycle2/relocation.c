#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void toBinary(int n, char *out, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        out[bits - 1 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    out[bits] = '\0';
}

int main() {
    FILE *obj = fopen("../ipop/objcode-rel", "r");
    if (!obj) {
        printf("Could not open file...\n");
        return 1;
    }

    int locctr = 0, start_addr = 0, new_start, addr_diff = 0;
    char ch;

    printf("Enter New Starting Address: ");
    scanf("%X", &new_start);
    locctr = new_start;

    while ((ch = fgetc(obj)) != EOF) {
        if (ch == 'H') {
            char pname[10];
            int length;
            fscanf(obj, "%s %X %X", pname, &start_addr, &length);

            printf("\nProgram Name: %s\n", pname);
            printf("Starting Address: %X\n", start_addr);
            printf("Program Length: %X\n", length);

            addr_diff = new_start - start_addr;
        }

        else if (ch == 'T') {
            int start, length, rel;
            fscanf(obj, "%X %X %X", &start, &length, &rel);

            char rel_bits[20];
            toBinary(rel, rel_bits, 12);  // convert relocation bits to binary string

            locctr = new_start + (start - start_addr);
            printf("\nText Record (Start: %X, Length: %X)\n", start, length);

            for (int i = 0; i < length / 3; i++) {
                int code;
                fscanf(obj, "%X", &code);
                if (rel_bits[i] == '1')
                    code += addr_diff;

                char ocode[7];
                sprintf(ocode, "%06X", code);

                for (int j = 0; j < 6; j += 2)
                    printf("%04X: %c%c\n", locctr++, ocode[j], ocode[j + 1]);
            }
        }

        else if (ch == 'E') {
            break;
        }
    }

    fclose(obj);
    return 0;
}
