// By: Duel Mood
// TA: Anthony Smith
// Lab time: 11:30am on Tuesdays

#include <stdio.h>
#include <string.h>

int factorial(int n);
void runHanoi(int n, char x, char y, char z);
void reverseString(char *, char *);

int main()
{
    char loop = 1;
    char iterations = 0;
    while (loop)
    {
        int selection;
        printf("Select an option:\n");
        printf("1. Factorial\n");
        printf("2. Tower of Hanoi\n");
        printf("3. Reverse a string\n");
        printf("4. Exit\n");
        scanf("%d", &selection);

        switch (selection)
        {
        case 1:
        {
            int number;
            printf("Enter a number: ");
            scanf("%d", &number);
            printf("The factorial of %d is: %d\n", number, factorial(number));
            break;
        }
        case 2:
        {
            int number;
            printf("Enter the number of disks: ");
            scanf("%d", &number);
            printf("The steps to solve the Tower of Hanoi with %d disks are:\n", number);
            runHanoi(number, 'A', 'B', 'C');
            break;
        }
        case 3:
        {
            char str[50];
            char reversedStr[50];

            printf("Enter a string to reverse: ");
            scanf("%s", str);
            reverseString(str, reversedStr);
            printf("The string \"%s\" reversed is: %s\n", str, reversedStr);
            break;
        }
        case 4:
            loop = 0;
            break;
        default:
            printf("Invalid option.\nTry again.\n");
        }

        iterations++;
        printf("\n");
    }

    return iterations;
}

// Recursively calculates the factorial n
int factorial(int n)
{
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

// Prints all steps in solving the Tower of Hanoi
void runHanoi(int n, char x, char y, char z)
{
    if (n == 1)
    {
        printf("Move disk from rod %c to rod %c\n", x, z);
    }
    else
    {
        runHanoi(n - 1, x, z, y);
        runHanoi(1, x, y, z);
        runHanoi(n - 1, y, x, z);
    }
}

// Reverses a string using recursion
void _reverseString(char *str, int start, int end)
{
    if (start >= end)
        return; // Base case

    // Swap two characters at start and end indices
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;

    // Move one step inwards towards center
    _reverseString(str, start + 1, end - 1);
}

// Reverses the src string and stores the result in dest.
void reverseString(char *src, char *dest)
{
    int length = 0;
    while (src[length] != '\0')
    { // Are we allowed to use strlen()?
        length++;
    }

    // Memcopy
    for (int i = 0; i < length; i++)
    {
        dest[i] = src[i];
    }
    dest[length] = '\0'; // Null-terminate

    _reverseString(dest, 0, length - 1);
}