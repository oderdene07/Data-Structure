#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int case_insensitive = 0;

int insensitive(const char a)
{
        if (case_insensitive && a >= 'A' && a <= 'Z')
                return a | 32;
        return a;
}

void KMP(const char *pattern, int *dfa[], int R)
{
        int patt_length = strlen(pattern);
        int x, c, j;
        dfa[pattern[0]][0] = 1;
        for (x = 0, j = 1; j < patt_length; j++)
        {
                for (c = 0; c < R; c++)
                        dfa[c][j] = dfa[c][x];
                dfa[pattern[j]][j] = j + 1;
                x = dfa[pattern[j]][x];
        }
}

int find(const char *buf, int n, int index, const char *pattern, int m, int *dfa[], int *pline)
{
        int i, j;

        for (i = index, j = 0; i < n && j < m; i++)
        {
                j = dfa[insensitive(buf[i])][j];
                if (buf[i] == '\n')
                        (*pline)++;
        }
        if (j == m)
                return i - m;
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
        int *dfa[256];
        int m = strlen(pattern);
        int n = strlen(buf);
        for (i = 0; i < R; i++)
                dfa[i] = (int *)malloc(sizeof(int) * m);

        KMP(pattern, dfa, R);

        do
        {
                ret = find(buf, n, ret + 1, pattern, m, dfa, &line);
                if (ret != -1)
                {
                        printf("%d: ", line);
                        /*
                          Олдсон газраас доошоо 5
                          дээшээ 5 тэмдэгтийг хэвлэнэ.
                         */
                        int L = ret - 5;
                        int R = ret + m + 5;
                        if (L < 0)
                                L = 0;
                        if (R >= n)
                                R = n;
                        for (i = L; i <= R; i++)
                                printf("%c", buf[i]);
                        printf("\n");
                }
        } while (ret != -1);

        for (i = 0; i < R; i++)
                free(dfa[i]);
        free(buf);
        return 0;
}
