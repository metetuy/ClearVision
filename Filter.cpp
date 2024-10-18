#include "Filter.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <numeric>
#include <math.h>

// Mean Filter
void Filter::apply_mean_filter(GrayscaleImage &image, int kernelSize)
{
    // TODO: Your code goes here.
    // 1. Copy the original image for reference.
    int height = image.get_height();
    int width = image.get_width();
    int **img = image.get_data();

    int padSize = kernelSize / 2;

    int **paddedImageCopy = new int *[height + 2 * padSize];

    for (int i = 0; i < height + 2 * padSize; i++)
    {
        paddedImageCopy[i] = new int[width + 2 * padSize];
    }

        // Copy original image data to the center of the padded image
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            paddedImageCopy[i + padSize][j + padSize] = img[i][j];
        }
    }


    // 2. For each pixel, calculate the mean value of its neighbors using a kernel.
    for (int i = padSize; i < height; i++)
    {
        for (int j = padSize; j < width; j++)
        {
            int sum = 0;
            for (int row = -padSize; row <= padSize; row++)
            {
                for (int col = -padSize; col <= padSize; col++)
                {
                    sum += paddedImageCopy[i + row][j + col];
                }
            }
            // 3. Update each pixel with the computed mean.
            img[i - padSize][j - padSize] = sum / (kernelSize * kernelSize);
        }
    }
        // Free padded image memory
    for (int i = 0; i < height + 2 * padSize; i++) {
        delete[] paddedImageCopy[i];
    }
    delete[] paddedImageCopy;


}

// Gaussian Smoothing Filter
void Filter::apply_gaussian_smoothing(GrayscaleImage &image, int kernelSize, double sigma)
{
    // TODO: Your code goes here.
    // 1. Create a Gaussian kernel based on the given sigma value.
    // 2. Normalize the kernel to ensure it sums to 1.
    // 3. For each pixel, compute the weighted sum using the kernel.
    // 4. Update the pixel values with the smoothed results.
}

// Unsharp Masking Filter
void Filter::apply_unsharp_mask(GrayscaleImage &image, int kernelSize, double amount)
{
    // TODO: Your code goes here.
    // 1. Blur the image using Gaussian smoothing, use the default sigma given in the header.
    // 2. For each pixel, apply the unsharp mask formula: original + amount * (original - blurred).
    // 3. Clip values to ensure they are within a valid range [0-255].
}
