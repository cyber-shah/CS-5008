#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 50000

typedef unsigned long long ull;

// don't forget to allocate space for your table (multi-demi array of MAX x MAX)

ull pascaldp(int n, int i)
{
    ull** table = (ull**)malloc((n + 1) * sizeof(ull*));
    for (int line = 0; line <= n; line++) {
        table[line] = (ull*)malloc((line + 1) * sizeof(ull));
    }

    for (int line = 0; line <= n; line++) {
        for (int j = 0; j <= line; j++) {
            if (j == 0 || j == line) {
                table[line][j] = 1;
            } else {
                table[line][j] = table[line - 1][j - 1] + table[line - 1][j];
            }
        }
    }

    ull result = table[n][i];
    for (int line = 0; line <= n; line++) {
        free(table[line]);
    }
    free(table);
    return result;
}

ull pascalr(int n, int i)
{
    if (n == i || i == 0)
    {
        return 1;
    }
    else
    {
        return pascalr(n - 1, i) + pascalr(n - 1, i - 1);
    }
}

ull *recursion_helper(int n, bool print, int version) {
    ull * row = malloc((sizeof(ull)) * n);
    if(print) {
        for (int i = 0; i < n; i++)
        {
            ull tmp = 1;
            for (int j = 0; j <= i; j++)
            {
                if(version == 2) tmp = pascaldp(i, j);
                else if(version == 1) {
                    tmp = pascalr(i, j);
                }
                if(i+1 == n) row[j] = tmp;
                printf("%llu ", tmp);
            }
            printf("\n");
        }
    }else {
        n--; // for ob1 error
        for(int i = 0; i <= n; i++) {
            ull tmp = 1;
            if(version == 2) tmp = pascaldp(n, i);
            else tmp = pascalr(n, i);
            row[i] = tmp;
        }
    }
    return row;
}

void printSingleRow(ull* row, int size) {
    for(int i = 0; i < size; i++) {
        printf("%lu ", row[i]);
    }
    printf("\n");
}

ull *getPascalTriangle(int n, bool print, int version)
{

    if(version > 0) {
        return recursion_helper(n, print, version);
    }
    // implied else for iterative version
    ull** triangle = (ull**) malloc((n+1) * sizeof(ull*));
    for (int i = 0; i < n; i++)
    {
        triangle[i] = (ull*) malloc((i+1) * sizeof(ull));
        triangle[i][0] = 1;
        for (int j = 1; j <= i; j++)
        {
            if(i == j)  {
                triangle[i][j] = 1;
            }
            else {
                triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j];
            }
        }
        if (print) printSingleRow(triangle[i], i+1);
    }
    //if(print) printf("\n");

    return triangle[n-1];
}

void help() {
    printf("./pascal.out N [Type] [Print Level]\n");
    printf("\tN is the number of rows in the pascal triangle, required.\n");
    printf("\t[Type] is either 2 for dynamic programming version, 1 for recursive version, 0 for iterative version, defaults to 0.\n");
    printf("\t[Print Level] is 0 for no print/speed compare only, 1 for print final row only, 2 for print all rows, defaults to 0.\n");
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("at least two arguments needed!\n");
        help();
        return 1;
    }

    const int n = atoi(argv[1]);
    int type = 0;
    int print = 0;
    if (argc > 2) {
        type = atoi(argv[2]);
    }
    if(argc > 3) {
        print = atoi(argv[3]);
    }

    bool print_it = false;
    if (print > 1) {
        print_it = true;
    }
    ull *row_at_n = getPascalTriangle(n, print_it, type);
    if (print == 1) printSingleRow(row_at_n, n);
    return 0;
}