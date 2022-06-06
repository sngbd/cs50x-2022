#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Average sum of rgb
            float fsum = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            int sum = round(fsum);
            image[i][j].rgbtRed = sum;
            image[i][j].rgbtGreen = sum;
            image[i][j].rgbtBlue = sum;
        }
    }
    return;
}

// Check, set, and return the value to 255 if it exceeds 255 and set the value to 0 if it is below 0, otherwise return the original value
int check(float value)
{
    if (value > 255.0)
    {
        return 255;
    }
    else if (value < 0)
    {
        return 0;
    }
    return round(value);
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            image[i][j].rgbtRed = check(sepiaRed);
            image[i][j].rgbtGreen = check(sepiaGreen);;
            image[i][j].rgbtBlue = check(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int count = width - 1;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap two pixels
            RGBTRIPLE tmp = image[i][count];
            image[i][count] = image[i][j];
            image[i][j] = tmp;
            count--;
        }
        count = width - 1;
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int tmpred = 0, tmpgreen = 0, tmpblue = 0; // Initialize temporary variable to store sum of rgb for new pixel;
            float den = 0; // Initialize the denominator for averaging;
            for (int a = i - 1; a <= i + 1; a++)
            {
                for (int b = j - 1; b <= j + 1; b++)
                {
                    if (a < 0 || a > height - 1 || b < 0 || b > width - 1) // Continue loop if the pixel doesn't exist
                    {
                        continue;
                    }
                    tmpred += copy[a][b].rgbtRed;
                    tmpgreen += copy[a][b].rgbtGreen;
                    tmpblue += copy[a][b].rgbtBlue;
                    den += 1.0;
                }
            }
            // Set new pixel's rgb
            image[i][j].rgbtRed = round(tmpred / den);
            image[i][j].rgbtGreen = round(tmpgreen / den);
            image[i][j].rgbtBlue = round(tmpblue / den);
        }
    }
    return;
}