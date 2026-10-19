#include <stdio.h>

void main()
{
    char arr[5] = {1, 2, 3, 4, 5};
    for (char *ptr = arr; ptr < arr + 5; printf("%d\n", *ptr++)) {}
}
