#include "Crypto.h"
#include "GrayscaleImage.h"

// Extract the least significant bits (LSBs) from SecretImage, calculating x, y based on message length
std::vector<int> Crypto::extract_LSBits(SecretImage &secret_image, int message_length)
{
    // Initialize a vector to store the extracted LSBs
    std::vector<int> LSB_array;

    // Reconstruct the full grayscale image from the secret image's upper and lower triangular arrays
    GrayscaleImage image = secret_image.reconstruct();

    // 1. Calculate the image dimensions
    int height = image.get_height(); // Get the height of the image
    int width = image.get_width();   // Get the width of the image

    // 2. Calculate total bits to extract based on the message length (each character has 7 bits)
    int total_bits_required = message_length * 7; // Total bits needed to represent the secret message

    // 3. Ensure there are enough pixels in the image
    if (width * height < total_bits_required) // Check if the total number of pixels is sufficient
    {
        throw std::runtime_error("ERROR: NOT ENOUGH PIXELS TO EXTRACT THE SECRET MESSAGE.");
    }

    // 4. Calculate the starting pixel (bit) such that the last bit is in the last pixel
    int total_bits = width * height;                        // Calculate the total number of bits in the image (width * height)
    int start_pixel_idx = total_bits - total_bits_required; // Determine the starting pixel index for extraction

    // 5. Extract LSBs from the image pixels, starting from the calculated pixel
    int bit_idx = 0; // Initialize a bit index to keep track of how many bits we've extracted
    for (int idx = start_pixel_idx; idx < total_bits && bit_idx < total_bits_required; idx++)
    {
        // Calculate the x and y coordinates of the pixel based on the linear index
        int x = idx % width; // Get the x-coordinate (column) of the pixel
        int y = idx / width; // Get the y-coordinate (row) of the pixel

        // Get the pixel value at the calculated coordinates
        int pixel_value = image.get_pixel(y, x);

        // Extract the least significant bit (LSB) from the pixel value and add it to the LSB_array
        LSB_array.push_back(pixel_value & 1); // Extract LSB (the last bit) by performing a bitwise AND with 1
        bit_idx++;                            // Increment the bit index
    }

    // Return the array containing the extracted LSBs
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
    // Get the dimensions of the grayscale image
    int height = image.get_height(); // Retrieve the height of the image
    int width = image.get_width();   // Retrieve the width of the image

    // Calculate the total number of bits (pixels) in the image
    int total_bits = height * width;
    // Check if there are enough pixels to embed the LSB array
    if (LSB_array.size() > total_bits)
    {
        throw std::runtime_error("ERROR: NOT ENOUGH PIXELS TO EMBED MESSAGE");
    }

    // Calculate the starting pixel index to embed the LSBs, ensuring the last bit is in the last pixel
    int total_bits_required = LSB_array.size();             // Get the number of bits to embed
    int start_pixel_idx = total_bits - total_bits_required; // Determine the index of the first pixel to modify

    // Start embedding from the calculated starting pixel and proceed left to right across rows
    int bit_idx = 0; // Initialize the bit index to track the current position in the LSB array
    for (int idx = start_pixel_idx; idx < total_bits && bit_idx < LSB_array.size(); idx++)
    {
        // Calculate the x and y coordinates of the pixel based on the linear index
        int x = idx % width; // Get the x-coordinate (column) of the pixel
        int y = idx / width; // Get the y-coordinate (row) of the pixel

        // Retrieve the current pixel value from the grayscale image
        int pixel_value = image.get_pixel(y, x);

        // Modify only the least significant bit (LSB) of the pixel value
        // Clear the current LSB and set it to the value from the LSB_array
        pixel_value = (pixel_value & ~1) | LSB_array[bit_idx]; // Embed the bit
        image.set_pixel(y, x, pixel_value);                    // Update the pixel with the modified value

        bit_idx++; // Increment the bit index to move to the next bit in the LSB array
    }

    // Step 4: Return a new SecretImage initialized with the embedded message.
    SecretImage secret_image(image); // Create a SecretImage object using the modified grayscale image
    return secret_image;             // Return the SecretImage containing the embedded LSBs
}
