#include "SecretImage.h"

// Constructor: split image into upper and lower triangular arrays
SecretImage::SecretImage(const GrayscaleImage &image)
{
    // TODO: Your code goes here.
    int height = image.get_height();
    int width = image.get_width();

    // 1. Dynamically allocate the memory for the upper and lower triangular matrices.
    upper_triangular = new int[(height + 1) * height / 2];
    lower_triangular = new int[(height - 1) * height / 2];

    // 2. Fill both matrices with the pixels from the GrayscaleImage.
    int i1 = 0;
    int i2 = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j < i)
            {
                lower_triangular[i1++] = image.get_pixel(i, j);
            }
            else
            {
                upper_triangular[i2++] = image.get_pixel(i, j);
            }
        }
    }
}

// Constructor: instantiate based on data read from file
SecretImage::SecretImage(int w, int h, int *upper, int *lower)
{
    // TODO: Your code goes here.
    // Since file reading part should dynamically allocate upper and lower matrices.
    width = w;
    height = h;
    // You should simply copy the parameters to instance variables.
    int upperSize = (height + 1) * height / 2;
    int lowerSize = (height - 1) * height / 2;

    upper_triangular = new int[upperSize];
    lower_triangular = new int[lowerSize];

    for (int i = 0; i < upperSize; i++)
    {
        upper_triangular[i] = upper[i];
    }

    for (int i = 0; i < lowerSize; i++)
    {
        lower_triangular[i] = lower[i];
    }
}

// Destructor: free the arrays
SecretImage::~SecretImage()
{
    // TODO: Your code goes here.
    // Simply free the dynamically allocated memory
    // for the upper and lower triangular matrices.
    delete[] upper_triangular;
    delete[] lower_triangular;
}

// Reconstructs and returns the full image from upper and lower triangular matrices.
GrayscaleImage SecretImage::reconstruct() const
{
    GrayscaleImage image(width, height);
    int i1 = 0;
    int i2 = 0;

    // TODO: Your code goes here.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j < i)
            {
                image.set_pixel(i, j, lower_triangular[i1++]);
            }
            else
            {
                image.set_pixel(i, j, upper_triangular[i2++]);
            }
        }
    }

    return image;
}

// Save the filtered image back to the triangular arrays
void SecretImage::save_back(const GrayscaleImage &image)
{
    // TODO: Your code goes here.
    // Update the lower and upper triangular matrices
    // based on the GrayscaleImage given as the parameter.
}

// Save the upper and lower triangular arrays to a file
void SecretImage::save_to_file(const std::string &filename)
{
    // TODO: Your code goes here.
    // 1. Write width and height on the first line, separated by a single space.
    // 2. Write the upper_triangular array to the second line.
    // Ensure that the elements are space-separated.
    // If there are 15 elements, write them as: "element1 element2 ... element15"
    // 3. Write the lower_triangular array to the third line in a similar manner
    // as the second line.
}

// Static function to load a SecretImage from a file
SecretImage SecretImage::load_from_file(const std::string &filename)
{
    // TODO: Your code goes here.
    // 1. Open the file and read width and height from the first line, separated by a space.
    // 2. Calculate the sizes of the upper and lower triangular arrays.
    // 3. Allocate memory for both arrays.
    // 4. Read the upper_triangular array from the second line, space-separated.
    // 5. Read the lower_triangular array from the third line, space-separated.
    // 6. Close the file and return a SecretImage object initialized with the
    //    width, height, and triangular arrays.
    SecretImage secret_image(nullptr);
    return secret_image;
}

// Returns a pointer to the upper triangular part of the secret image.
int *SecretImage::get_upper_triangular() const
{
    return upper_triangular;
}

// Returns a pointer to the lower triangular part of the secret image.
int *SecretImage::get_lower_triangular() const
{
    return lower_triangular;
}

// Returns the width of the secret image.
int SecretImage::get_width() const
{
    return width;
}

// Returns the height of the secret image.
int SecretImage::get_height() const
{
    return height;
}
