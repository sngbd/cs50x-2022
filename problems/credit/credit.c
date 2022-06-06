#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    string numstr = get_string("Number: ");
    int len = strlen(numstr);
    int sum = 0;
    // Convert string to long
    long long int num = atol(numstr);
    long long int tmp;
    long long int ten = 10;
    // Calculate products' digits
    do
    {
        tmp = num / ten;
        int dig = tmp % 10;
        int digs = dig * 2;
        int a = digs / 10;
        int b = digs % 10;
        sum += a + b;
        ten = ten * 100;
    }
    while (tmp != 0);
    ten = 1;
    tmp = num;
    // Sum the rest of numbers' digits
    do
    {
        int dig = tmp % 10;
        sum += dig;
        ten = ten * 100;
        tmp = num / ten;
    }
    while (tmp != 0);
    // Prints outputs
    if (sum % 10 == 0)
    {
        if (len == 13 || len == 16)
        {
            long long int pwr = pow(10, (len - 1));
            long long int pwr2 = pow(10, (len - 2));
            if (num / pwr == 4) // Check the first digit
            {
                printf("VISA\n");
            }
            else if (num / pwr2 >= 51 && num / pwr2 <= 55) // Check the first two digits
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (len == 15)
        {
            long long int pwr = pow(10, (len - 2));
            if (num / pwr == 34 || num / pwr == 37) // Check the first two digits
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n"); // Prints if numbers are invalid
    }
}