#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");
        if (!fp) {
            printf("wunzip: cannot open file\n");
            exit(1);
        }

        uint32_t count;
        char c;

        while (fread(&count, sizeof(uint32_t), 1, fp) == 1) {
            if (fread(&c, sizeof(char), 1, fp) != 1) {
                break;  // 🔥 critical
            }

            for (uint32_t j = 0; j < count; j++) {
                printf("%c", c);
            }
        }

        fclose(fp);
    }
    printf("\n");
    return 0;
}
