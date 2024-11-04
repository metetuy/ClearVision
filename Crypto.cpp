#include "Crypto.h"
#include "GrayscaleImage.h"

// Extract the least significant bits (LSBs) from SecretImage, calculating x, y based on message length
std::vector<int> Crypto::extract_LSBits(SecretImage &secret_image, int message_length)
{
    std::vector<int> LSB_array;
    // TODO: Your code goes here.

    // 1. Reconstruct the SecretImage to a GrayscaleImage.
    GrayscaleImage image = secret_image.reconstruct();
    // 2. Calculate the image dimensions.
    int height = image.get_height();
    int width = image.get_width();
    // 3. Determine the total bits required based on message length.
    int total_bits_required = message_length * 7;
    // 4. Ensure the image has enough pixels; if not, throw an error.
    int image_size = width * height;
    if (image_size < total_bits_required)
    {
        throw std::runtime_error("ERROR: NOT ENOUGH PIXELS TO EXTRACT THE SECRET MESSAGE.");
    }
    // 5. Calculate the starting pixel from the message_length knowing that
    //    the last LSB to extract is in the last pixel of the image.
    int starting_pixel_id = image_size - total_bits_required;

    // 6. Extract LSBs from the image pixels and return the result.
    for (int i = starting_pixel_id; i < image_size; i++)
    {
        int row = i / height;
        int col = i % width;

        int pixel_value = image.get_pixel(row, col);
        LSB_array.push_back(pixel_value & 1);
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
        throw std::runtime_error("ERROR: LSB ARRAY SIZE SHOULD BE A MULTIPLE OF 7.");
    }

    // 2. Convert each group of 7 bits into an ASCII character.
    for (int i = 0; i < LSB_array.size(); i += 7)
    {
        int ascii_value = 0;

        for (int j = 0; j < 7; ++j)
        {
            ascii_value = ascii_value * 2 + LSB_array[i + j];
        }

        // 3. Collect the characters to form the decrypted message.
        message += static_cast<char>(ascii_value);
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
        for (int i = 6; i >= 0; --i)
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
    // TODO: Your code goes here.
    int height = image.get_height();
    int width = image.get_width();
    int image_size = height * width;
    int total_bits_required = LSB_array.size();
    // 1. Ensure the image has enough pixels to store the LSB array, else throw an error.
    if (image_size < total_bits_required)
    {
        throw std::runtime_error("ERROR: NOT ENOUGH PIXELS TO EMBED THE SECRET MESSAGE.");
    }
    // 2. Find the starting pixel based on the message length knowing that
    //    the last LSB to embed should end up in the last pixel of the image.
    int starting_pixel_id = image_size - total_bits_required;

    // 3. Iterate over the image pixels, embedding LSBs from the array.
    int bit_i = 0;
    for (int i = starting_pixel_id; i < image_size; i++)
    {

        int row = i / height;
        int col = i % width;

        int pixel_value = image.get_pixel(row, col);
        pixel_value = (pixel_value & ~1) | LSB_array[bit_i];
        image.set_pixel(row, col, pixel_value);
        bit_i++;
    }

    // 4. Return a SecretImage object constructed from the given GrayscaleImage
    //    with the embedded message.
    SecretImage secret_image(image);
    return secret_image;
}
