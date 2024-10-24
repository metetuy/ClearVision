#include "Crypto.h"
#include "GrayscaleImage.h"

// Extract the least significant bits (LSBs) from SecretImage, calculating x, y based on message length
std::vector<int> Crypto::extract_LSBits(SecretImage &secret_image, int message_length)
{
    std::vector<int> LSB_array;
    // TODO: Your code goes here.

    // 1. Reconstruct the SecretImage to a GrayscaleImage.
    GrayscaleImage img = secret_image.reconstruct();
    // 2. Calculate the image dimensions.
    int height = img.get_height();
    int width = img.get_width();
    // 3. Determine the total bits required based on message length.
    int total_bits_required = message_length * 8;
    // 4. Ensure the image has enough pixels; if not, throw an error.
    if (width * height < total_bits_required)
    {
        throw std::runtime_error("ERROR: NOT ENOUGH PIXELS TO CARRY THE SECRET MESSAGE.");
    }
    // 5. Calculate the starting pixel from the message_length knowing that
    //    the last LSB to extract is in the last pixel of the image.
    int startingPixel = (width * height) - total_bits_required;
    // 6. Extract LSBs from the image pixels and return the result.
    for (int i = startingPixel; i < width * height; i++)
    {
        int pixel_value = img.get_pixel(i / width, i % width);
        int lsb = pixel_value & 1;
        LSB_array.push_back(lsb);
    }

    return LSB_array;
}

// Decrypt message by converting LSB array into ASCII characters
std::string Crypto::decrypt_message(const std::vector<int> &LSB_array)
{
    std::string message;
    // TODO: Your code goes here.

    // 1. Verify that the LSB array size is a multiple of 7, else throw an error.
    if (LSB_array.size() % 7 != 0)
    {
        throw std::runtime_error("ERROR: LSB array size should be a multiple of 7.");
    }

    // 2. Convert each group of 7 bits into an ASCII character.
    for (int i = 0; i < LSB_array.size(); i += 7)
    {
        int ascii_value = 0; // Initialize the ASCII value for the character

        for (int j = 0; j < 7; ++j)
        {
            ascii_value = (ascii_value << 1) | LSB_array[i + j];
        }

        // 3. Collect the characters to form the decrypted message.
        message += static_cast<char>(ascii_value); // Convert ASCII value to character and append
    }

    // 4. Return the resulting message.
    return message;
}

// Encrypt message by converting ASCII characters into LSBs
std::vector<int> Crypto::encrypt_message(const std::string &message)
{
    std::vector<int> LSB_array;
    // TODO: Your code goes here.

    // 1. Convert each character of the message into a 7-bit binary representation.
    //    You can use std::bitset.

    for (char c : message)
    {
        std::bitset<7> bits(static_cast<unsigned char>(c));
        // 2. Collect the bits into the LSB array.
        for (int i = 0; i < 7; i++)
        {
            LSB_array.push_back(bits[i]);
        }
    }
    // 3. Return the array of bits.

    return LSB_array;
}

// Embed LSB array into GrayscaleImage starting from the last bit of the image
SecretImage Crypto::embed_LSBits(GrayscaleImage &image, const std::vector<int> &LSB_array)
{
    SecretImage secret_image(image);
    // TODO: Your code goes here.
    int height = image.get_height();
    int width = image.get_width();

    int image_size = height * width;
    // 1. Ensure the image has enough pixels to store the LSB array, else throw an error.
    if (LSB_array.size() > image_size)
    {
        throw std::runtime_error("ERROR: NOT ENOUGHT PIXELS");
    }
    // 2. Find the starting pixel based on the message length knowing that
    //    the last LSB to embed should end up in the last pixel of the image.
    int start_index = image_size - LSB_array.size();
    // 3. Iterate over the image pixels, embedding LSBs from the array.
    for (int i = 0; i < LSB_array.size(); i++)
    {
        int pixel_index = start_index + i;

        int pixel_value = image.get_pixel(pixel_index / width, pixel_index % width);

        pixel_value = (pixel_value & ~1) | (LSB_array[i] & 1);

        image.set_pixel(pixel_index / width, pixel_index % width, pixel_value);
    }
    // 4. Return a SecretImage object constructed from the given GrayscaleImage
    //    with the embedded message.

    return secret_image;
}
