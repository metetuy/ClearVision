#include "SecretImage.h"

// Constructor: split image into upper and lower triangular arrays
SecretImage::SecretImage(const GrayscaleImage &image)
{
    // 
    height = image.get_height();
    width = image.get_width();

    upper_triangular = nullptr;
    lower_triangular = nullptr;

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
            if (j >= i)
            {
                upper_triangular[i2++] = image.get_pixel(i, j);
            }
            else
            {
                lower_triangular[i1++] = image.get_pixel(i, j);
            }
        }
    }
}

// Constructor: instantiate based on data read from file
SecretImage::SecretImage(int w, int h, int *upper, int *lower)
{
    // 
    // Since file reading part should dynamically allocate upper and lower matrices.
    // You should simply copy the parameters to instance variables.
    width = w;
    height = h;
    upper_triangular = upper;
    lower_triangular = lower;
}

// Destructor: free the arrays
SecretImage::~SecretImage()
{
    // 
    // Simply free the dynamically allocated memory
    // for the upper and lower triangular matrices.
    delete[] upper_triangular;
    delete[] lower_triangular;
    upper_triangular = nullptr;
    lower_triangular = nullptr;
}

// Reconstructs and returns the full image from upper and lower triangular matrices.
GrayscaleImage SecretImage::reconstruct() const
{
    GrayscaleImage image(width, height);
    int upperIndex = 0;
    int lowerIndex = 0;

    // 
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j >= i)
            {
                image.set_pixel(i, j, upper_triangular[upperIndex++]);
            }
            else
            {
                image.set_pixel(i, j, lower_triangular[lowerIndex++]);
            }
        }
    }

    return image;
}

// Save the filtered image back to the triangular arrays
void SecretImage::save_back(const GrayscaleImage &image)
{
    // 
    // Update the lower and upper triangular matrices
    // based on the GrayscaleImage given as the parameter.
    height = image.get_height();
    width = image.get_width();

    delete[] upper_triangular;
    delete[] lower_triangular;

    upper_triangular = nullptr;
    lower_triangular = nullptr;

    upper_triangular = new int[((width + 1) * width) / 2];
    lower_triangular = new int[((width - 1) * width) / 2];

    int upperIndex = 0;
    int lowerIndex = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j >= i)
            {
                upper_triangular[upperIndex++] = image.get_pixel(i, j);
            }
            else
            {
                lower_triangular[lowerIndex++] = image.get_pixel(i, j);
            }
        }
    }
}

// Save the upper and lower triangular arrays to a file
void SecretImage::save_to_file(const std::string &filename)
{
    // 

    std::ofstream file(filename);
    // 1. Write width and height on the first line, separated by a single space.
    file << width << " " << height << "\n";

    // 2. Write the upper_triangular array to the second line.
    // Ensure that the elements are space-separated.
    // If there are 15 elements, write them as: "element1 element2 ... element15"
    int upperSize = (width * (width + 1)) / 2;
    for (int i = 0; i < upperSize; i++)
    {
        file << upper_triangular[i];
        if (i < upperSize - 1)
        {
            file << " "; // Add space after each element except the last one
        }
    }

    file << "\n";

    // 3. Write the lower_triangular array to the third line in a similar manner
    // as the second line.
    int lowerSize = (width * (width - 1)) / 2;
    for (int i = 0; i < lowerSize; i++)
    {
        file << lower_triangular[i];
        if (i < lowerSize - 1)
        {
            file << " "; // Add space after each element except the last one
        }
    }

    file << "\n";

    file.close();
}

// Static function to load a SecretImage from a file
SecretImage SecretImage::load_from_file(const std::string &filename)
{
    // 
    // 1. Open the file and read width and height from the first line, separated by a space.
    std::ifstream file(filename);
    int width;
    int height;

    file >> width >> height;

    // 2. Calculate the sizes of the upper and lower triangular arrays.
    int upperSize = (width * (width + 1)) / 2;
    int lowerSize = (width * (width - 1)) / 2;
    // 3. Allocate memory for both arrays.

    int * upper_array = new int[upperSize];
    int * lower_array = new int[lowerSize];
    // 4. Read the upper_triangular array from the second line, space-separated.
    for (int i = 0; i < upperSize; i++)
    {
        file >> upper_array[i];
    }

    // 5. Read the lower_triangular array from the third line, space-separated.
    for (int i = 0; i < lowerSize; i++)
    {
        file >> lower_array[i];
    }

    // 6. Close the file and return a SecretImage object initialized with the
    //    width, height, and triangular arrays.
    file.close();
    SecretImage secret_image(width, height, upper_array, lower_array);

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
