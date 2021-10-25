# Converts image files into .bin files with the following formatting:
#   byte 0 = red value (0-255)
#   byte 1 = green value (0-255)
#   byte 2 = blue value (0-255)
#   etc... (repeats)

from PIL import Image
import os

# Writes the given image to a .bin file
def WriteImageToBin(fileImgInput, fileBinOutput):
    # Delete the old bin file
    if os.path.exists(fileBinOutput):
        os.remove(fileBinOutput)

    # Create a new version of the file
    file = open(fileBinOutput, 'wb')

    image = Image.open(fileImgInput)
    width, height = image.size
    pixel_data = image.load()

    for y in range(height):
        for x in range(width):
            col = pixel_data[x, y]
            file.write(int.to_bytes(col[0], 1, byteorder='big')) # Red
            file.write(int.to_bytes(col[1], 1, byteorder='big')) # Green
            file.write(int.to_bytes(col[2], 1, byteorder='big')) # Blue
    file.close()

def main():
    # TODO: Convert all files in the patterns folder using WriteImageToBin
    print()

if __name__ == '__main__':
    main()