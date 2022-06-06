#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Size of a block to read from the card and to write to the jpg files
    const int BLOCK_SIZE = 512;
    // Check usage
    if (argc < 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    // Open card
    FILE *file = fopen(argv[1], "r");
    // Initialize jpg file to null
    FILE *img = NULL;
    typedef uint8_t BYTE;
    BYTE buffer[BLOCK_SIZE];
    char filename[8];
    int count = 0;
    bool open = false;
    // Iterate through all of the blocks in the card
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // Check if the current block is a beginning of a jpg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            open = true;
            if (count != 0)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w");
            fwrite(buffer, BLOCK_SIZE, 1, img);
            count++;
        }
        else if (open) // Check if the current block is a continuation of a jpg file
        {
            fwrite(buffer, BLOCK_SIZE, 1, img);
        }
    }
    fclose(img);
    fclose(file);
}