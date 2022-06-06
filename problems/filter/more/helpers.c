#include <stdio.h>
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

// Check if value exceeds 255, if true return 255, else return original value
int check(int value)
{
    if (value > 255)
    {
        return 255;
    }
    return value;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Initialize gx and gy values
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int x = 0; // For iterating through height of gx and gy
            int gxRed = 0;
            int gxGreen = 0;
            int gxBlue = 0;
            int gyRed = 0;
            int gyGreen = 0;
            int gyBlue = 0;
            for (int a = i - 1; a <= i + 1; a++)
            {
                int y = 0; // For iterating through width of gx and gy
                for (int b = j - 1; b <= j + 1; b++)
                {
                    if (a < 0 || a > height - 1 || b < 0 || b > width - 1) // Continue loop if the pixel doesn't exist
                    {
                        y++;
                        continue;
                    }
                    else
                    {
                        // Calculating gx and gy values of one pixel
                        gxRed += copy[a][b].rgbtRed * gx[x][y];
                        gxGreen += copy[a][b].rgbtGreen * gx[x][y];
                        gxBlue += copy[a][b].rgbtBlue * gx[x][y];
                        gyRed += copy[a][b].rgbtRed * gy[x][y];
                        gyGreen += copy[a][b].rgbtGreen * gy[x][y];
                        gyBlue += copy[a][b].rgbtBlue * gy[x][y];
                        y++;
                    }
                }
                x++;
            }
            image[i][j].rgbtRed = check(round(sqrt(pow(gxRed, 2) + pow(gyRed, 2))));
            image[i][j].rgbtGreen = check(round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2))));
            image[i][j].rgbtBlue = check(round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2))));
        }
    }
    return;
}