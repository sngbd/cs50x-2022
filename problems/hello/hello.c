#include <stdio.h>
#include <cs50.h>

int main()
{
    string name = get_string("What's your name? "); // Prompts user for input
    printf("Hello %s\n", name); // Prints output
}