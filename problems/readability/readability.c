#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main()
{
    string text = get_string("Text: ");
    float letters = count_letters(text);
    float words = count_words(text);
    float sentences = count_sentences(text);
    float L = letters / words * 100; // Calculate average number of letters per 100 words in the text
    float S = sentences / words * 100; // Calculate average number of sentences per 100 words in the text
    int index = round(0.0588 * L - 0.296 * S - 15.8); // Calculate index

    // Prints output
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// Count letters
int count_letters(string text)
{
    int ltr = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (toupper(text[i]) - 65 < 0 || toupper(text[i]) - 65 > 25)
        {
            continue; // If char is not an alphabet then continue the loop
        }
        ltr++;
    }
    return ltr;
}

// Count words
int count_words(string text)
{
    int wrd = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            wrd++;
        }
    }
    return wrd + 1;
}

// Count sentences
int count_sentences(string text)
{
    int stc = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            stc++;
        }
    }
    return stc;
}