#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
    srand(time(nullptr));

    FILE* res = fopen("number.txt", "wb");
    assert(res);

    for(int i = 0; i < 16; i++)
    {
        int number =  rand() % (65535 + 1);
        fprintf(res, "%.*X\n", 4, number);
    }

    fclose(res);
    return 0;
}
