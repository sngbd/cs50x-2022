#include <stdio.h>

int main()
{
    int n;

    // Prompts user for input, reprompts if input is invalid
    do
    {
        printf("Height: ");
        scanf("%d", &n);
    }
    while (!(n >= 1 && n <= 8));

    // Prints the pyramid
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n - i; j++)
        {
            printf(" "); // Prints the space
        }
        for (int k = 1; k <= i; k++)
        {
            printf("#"); // Prints the pyramid blocks
        }
        printf("\n");
    }
}