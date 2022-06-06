#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool not_only_alpha(string s);
char rotate(char c);
int DICT[25];

int main(int argc, char *argv[])
{
    // Check whether the usage is correct or not
    if (argc != 2 || not_only_alpha(argv[1]))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (argc == 2 && strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        string key = argv[1];
        for (int i = 0; i < 26; i++)
        {
            DICT[i] = toupper(key[i]);
        }
        // Check if string contains duplicate characters
        for (int i = 1; i < 26; i++)
        {
            if (DICT[i - 1] == DICT[i])
            {
                printf("Key must not contain duplicate characters.\n");
                return 1;
            }
        }
        string plain = get_string("plaintext: "); // Prompts user for input
        for (int i = 0; i < strlen(plain); i++)
        {
            plain[i] = rotate(plain[i]);
        }
        printf("ciphertext: %s\n", plain); // Prints output
        return 0;
    }
}

// Function to check whether the string consists solely of alphabets or not
bool not_only_alpha(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (!isalpha(s[i]))
        {
            return true;
        }
    }
    return false;
}

// Function to rotate char according to the key
char rotate(char c)
{
    if (isupper(c)) // Check if character is uppercase
    {
        return DICT[c - 65];
    }
    else if (islower(c)) // Check if character is lowercase
    {
        return DICT[c - 97] + 32;
    }
    else
    {
        return c; // Return the character itself if character is not an alphabet
    }
}