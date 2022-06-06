#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool not_only_digits(string s);
char rotate(char c, int key);

int main(int argc, char *argv[])
{
    // Check whether the usage is correct or not
    if (argc != 2 || not_only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        int key = atoi(argv[1]); // Convert string to integer;
        string plain = get_string("plaintext: "); // Prompts for user's input
        for (int i = 0; i < strlen(plain); i++)
        {
            plain[i] = rotate(plain[i], key); // Replace plaintext with rotated chars, i.e., the ciphertext
        }
        printf("ciphertext: %s\n", plain); // Prints output
    }
    return 0;
}

// Function to check whether the string consists solely of digits or not
bool not_only_digits(string s)
{
    int c = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (!isdigit(s[i]))
        {
            return true;
        }
    }
    return false;
}

// Function to rotate char according to the key
char rotate(char c, int key)
{
    if (isupper(c))
    {
        int chr = (c - 64 + key) % 26;
        return chr + 64;
    }
    else if (islower(c))
    {
        char chr = (c - 96 + key) % 26;
        return chr + 96;
    }
    else
    {
        return c;
    }
}