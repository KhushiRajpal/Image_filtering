#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //converting to black and white style
    double average = 0.0;
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            average = round((pixel.rgbtBlue + pixel.rgbtRed + pixel.rgbtGreen) / 3.0);
            int final_avg = (int)average ;
        
            image[i][j].rgbtGreen = final_avg;
            image[i][j].rgbtBlue = final_avg;
            image[i][j].rgbtRed = final_avg ;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // creating the basic ass sepia 
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            double red = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            double green = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue) ;
            double blue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (red > 255)
            {
                image[i][j].rgbtRed = 255 ;
            }
            else
            {
                image[i][j].rgbtRed = red ;
            }
            if (green > 255)
            {
                image[i][j].rgbtGreen = 255 ;
            }
            else
            {
                image[i][j].rgbtGreen = green ;
            }
            if (blue > 255)
            {
                image[i][j].rgbtBlue = 255 ;
            }
            else
            {
                image[i][j].rgbtBlue = blue ;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
        // Temporary storage
    RGBTRIPLE temp;

    // Iterate over every row of the image
    for (int i = 0; i < height; i++)
    {
        // Iterate over every column that are less than width / 2
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels on horizontally opposite sides
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Creating a copy variable for our code
    
    // Starting the for loop to copy the  image pixels into the code
    
     // Temporary storage
    RGBTRIPLE temp[height][width];

    // Copying the image to keep an unaltered version to loop over
    memcpy(temp, image, sizeof(RGBTRIPLE) * height * width);

    // Iterate over every row of the image
    for (int i = 0; i < height; i++)
    {
        // Iterate over every column of the image
        for (int j = 0; j < width; j++)
        {
            // Initiate average counter at 0.0
            // Gotta avoid the truncated integer problem
            float average = 0.0;
            // Initiate RGB values at 0
            int red = 0;
            int green = 0;
            int blue = 0;

            // Iterate over rows around current row
            for (int k = -1; k <= 1; k++)
            {
                // Iterate over columns around current column
                for (int l = -1; l <= 1; l++)
                {
                    // If current row + next row are within bounds
                    // If current column + next column are within bounds
                    if (i + k != height &&
                        i + k != -1 &&
                        j + l != width &&
                        j + l != -1)
                    {
                        // Update RGB values to the sum both pixels' RGB values
                        red += temp[i + k][j + l].rgbtRed;
                        green += temp[i + k][j + l].rgbtGreen;
                        blue += temp[i + k][j + l].rgbtBlue;
                        // Increment average by one for one pixel in the sum
                        average++;
                    }
                }
            }
            // Set each RGB values to their blurred values
            image[i][j].rgbtRed = round(red / average);
            image[i][j].rgbtGreen = round(green / average);
            image[i][j].rgbtBlue = round(blue / average);
        }
    }
    return;
}

