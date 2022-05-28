#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int case_insensitive = 0;

int max(int a, int b) { return (a > b) ? a : b; }

z

void BM(const char *pattern, int right[])
{
        int i, j, R = 256, patt_length = strlen(pattern);

        for (i = 0; i < R; i++)
                right[i] = -1;

        for (j = 0; j < patt_length; j++)
                right[pattern[j]] = j;
}

int find(const char *buf, int n, int index, const char *pattern, int m, int right[], int *pline)
{
        int i = index, j, k;
        while (i <= (n - m))
        {
                j = m - 1;
                while (j >= 0 && insensitive(pattern[j]) == insensitive(buf[i + j]))
                        j--;

                if (j < 0)
                {
                        for (k = index; k < i; k++)
                        {
                                if (buf[k] == '\n')
                                {
                                        (*pline)++;
                                }
                        }
                        return i;
                }
                else
                        i += max(1, j - right[insensitive(buf[i + j])]);
        }
        return -1;
}

int main(int argc, char *argv[])
{
        // Аргументийн тоо ядаж 3 байх ёстой.
        if (argc < 3)
        {
                printf("%s [-i] pattern FILE", argv[0]);
                exit(-1);
        }

        const char *pattern;
        if (argc > 3 && strcmp("-i", argv[1]) == 0)
        {
                case_insensitive = 1; // Том жижгийг хайхрахгүй адил гэж үзнэ.
                pattern = argv[2];
        }
        else
                pattern = argv[1];

        FILE *fin;
        fin = fopen(argv[argc - 1], "r");
        if (fin == NULL)
        {
                printf("Error openning %s file", argv[argc - 1]);
                exit(-1);
        }
        int len = 0;
        char ch;
        while (!feof(fin))
        {
                ch = fgetc(fin);
                len++; // Файлд доторх тэмдэгтүүдийг тоолъё.
        }
        char *buf;
        buf = (char *)malloc(sizeof(char) * (len + 1)); // Энд тэмдэгтүүдийг хадгална
        fseek(fin, 0, SEEK_SET);                        // Файл заагчийг буцаад эхлэлд нь аваачна.
        int i = 0;
        while (!feof(fin))
                buf[i++] = fgetc(fin); // Өгөгдлийг уншиж байна.
        buf[len - 1] = 0;              /* тэмдэгт мөр төгсгөл заагч */
        int ret = -1;
        int line = 0;

        int R = 256;
        int right[R];
        int m = strlen(pattern);
        BM(pattern, right);

        do
        {
                ret = find(buf, len - 1, ret + 1, pattern, m, right, &line);
                if (ret != -1)
                {
                        printf("%d: ", line);
                        /*
                          Олдсон газраас доошоо 5
                          дээшээ 5 тэмдэгтийг хэвлэнэ.
                         */
                        int L = ret - 5;
                        int R = ret + strlen(pattern) + 5;
                        if (L < 0)
                                L = 0;
                        if (R >= len)
                                R = len - 1;
                        for (i = L; i <= R; i++)
                                printf("%c", buf[i]);
                        printf("\n");
                }
        } while (ret != -1);

        free(buf);
        return 0;
}
