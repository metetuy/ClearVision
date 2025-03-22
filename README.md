# ClearVision

ClearVision is a command-line tool for processing grayscale images, applying filters, performing arithmetic operations, and embedding/extracting hidden messages using steganography.

## Features
- Apply Mean, Gaussian, and Unsharp Mask filters
- Add and subtract images
- Compare images for equality
- Convert images into a disguised format and reconstruct them
- Encrypt and decrypt messages within images using LSB steganography

## Installation

### Prerequisites
- C++ compiler with C++17 support
- OpenCV (if required by `GrayscaleImage` implementation)

### Compilation
```sh
make
```

## Usage

```sh
clearvision <operation> <arg1> <arg2> ...
```

### Available Operations

#### Filtering
```sh
clearvision mean <image> <kernel_size>
clearvision gauss <image> <kernel_size> <sigma>
clearvision unsharp <image> <kernel_size> <amount>
```

#### Image Arithmetic
```sh
clearvision add <image1> <image2>
clearvision sub <image1> <image2>
clearvision equals <image1> <image2>
```

#### Steganography
```sh
clearvision disguise <image>
clearvision reveal <dat_file>
clearvision enc <image> <message>
clearvision dec <image> <message_length>
```

## Examples

### Applying a Mean Filter
```sh
clearvision mean input.png 3
```
Saves output as `mean_filtered_input_3.png`.

### Encrypting a Message
```sh
clearvision enc image.png "Hello, world!"
```

### Decrypting a Message
```sh
clearvision dec image.png 13
```


