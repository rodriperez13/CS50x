#include <math.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg = 0, r = 0, g = 0, b = 0, round_avg = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            r = image[i][j].rgbtRed;
            g = image[i][j].rgbtGreen;
            b = image[i][j].rgbtBlue;
            avg = (r + g + b) / 3;
            round_avg = round(avg);
            image[i][j].rgbtRed = round_avg;
            image[i][j].rgbtGreen = round_avg;
            image[i][j].rgbtBlue = round_avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    {
        for (int  i = 0; i < height; i++)
        {
            for (int j = 0; j < width / 2; j++)
            {
                tmp = image[i][j];
                image[i][j] = image[i][width - j - 1];
                image[i][width - j - 1] = tmp;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    RGBTRIPLE(*blur_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Esquina izquierda superior
            if (i == 0 && j == 0)
            {
                tmp.rgbtRed = round((image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i][j].rgbtRed) / 4.0);
                tmp.rgbtGreen = round((image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j].rgbtGreen) / 4.0);
                tmp.rgbtBlue = round((image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j].rgbtBlue) / 4.0);
                blur_image[i][j] = tmp;
            }
            //Esquina izquierda inferior
            else if (i == (height - 1) && j == 0)
            {
                tmp.rgbtRed = round((image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i][j].rgbtRed) / 4.0);
                tmp.rgbtGreen = round((image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j].rgbtGreen) / 4.0);
                tmp.rgbtBlue = round((image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j].rgbtBlue) / 4.0);
                blur_image[i][j] = tmp;
            }
            //Esquina derecha inferior
            else if (i == 0 && j == (width - 1))
            {
                tmp.rgbtRed = round((image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed + image[i][j].rgbtRed) / 4.0);
                tmp.rgbtGreen = round((image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen) / 4.0);
                tmp.rgbtBlue = round((image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue) / 4.0);
                blur_image[i][j] = tmp;
            }
            //Esquina derecha superior
            else if (i == (height - 1) && j == (width - 1))
            {
                tmp.rgbtRed = round((image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed + image[i][j].rgbtRed) / 4.0);
                tmp.rgbtGreen = round((image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen) / 4.0);
                tmp.rgbtBlue = round((image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue) / 4.0);
                blur_image[i][j] = tmp;
            }
            //EDGES
            //Left edge
            else if (j == 0 && i != 0 && i != height - 1)
            {
                tmp.rgbtRed = round((image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed +image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j].rgbtRed) / 6.0);
                tmp.rgbtGreen = round((image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen +image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i][j].rgbtGreen) / 6.0);
                tmp.rgbtBlue = round((image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue +image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j].rgbtBlue) / 6.0);
                blur_image[i][j] = tmp;
            }
            //Inferior edge
            else if(i == (height - 1) && j != 0 && j != (width - 1))
            {
                tmp.rgbtRed = round((image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i][j].rgbtRed) / 6.0);
                tmp.rgbtGreen = round((image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j].rgbtGreen) / 6.0);
                tmp.rgbtBlue = round((image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j].rgbtBlue) / 6.0);
                blur_image[i][j] = tmp;
            }
            //Superior edge
            else if (i == 0 && j != 0 && j != (width - 1))
            {
                tmp.rgbtRed = round((image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i][j].rgbtRed) / 6.0);
                tmp.rgbtGreen = round((image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +image[i + 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j].rgbtGreen) / 6.0);
                tmp.rgbtBlue = round((image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +image[i + 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j].rgbtBlue) / 6.0);
                blur_image[i][j] = tmp;
            }
            //Right edge
            else if(j == (width - 1) && i != 0 && i != (height - 1))
            {
                tmp.rgbtRed = round((image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i][j].rgbtRed) / 6.0);
                tmp.rgbtGreen = round((image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j].rgbtGreen) / 6.0);
                tmp.rgbtBlue = round((image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue +image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j].rgbtBlue) / 6.0);
                blur_image[i][j] = tmp;
            }
            else
            {
                tmp.rgbtRed = round((image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed  + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j].rgbtRed) / 9.0);
                tmp.rgbtGreen = round((image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j].rgbtGreen) / 9.0);
                tmp.rgbtBlue = round((image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue  + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j].rgbtBlue) / 9.0);
                blur_image[i][j] = tmp;
            }
        }
    }
    //Copio la imagen blur en la imagen original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blur_image[i][j];
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    int sepiaRed = 0,sepiaGreen = 0, sepiaBlue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round (.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round (.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round (.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaRed >= 255.0)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            if (sepiaGreen >= 255.0)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            if (sepiaBlue >= 255.0)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}
