#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    uint32_t count = 0;
    char prev = '\0';

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");
        if (!fp) {
            printf("wzip: cannot open file\n");
            exit(1);
        }

        int c;
        while ((c = fgetc(fp)) != EOF) {
            char curr = (char)c;

            if (count == 0) {
                prev = curr;
                count = 1;
            } 
            else if (curr == prev) {
                count++;
            } 
            else {
                fwrite(&count, sizeof(uint32_t), 1, stdout);
                fwrite(&prev, sizeof(char), 1, stdout);

                prev = curr;
                count = 1;
            }
        }

        fclose(fp);
    }

    // 🔥 CRITICAL: final flush
    if (count > 0) {
        fwrite(&count, sizeof(uint32_t), 1, stdout);
        fwrite(&prev, sizeof(char), 1, stdout);
    }

    return 0;
}
