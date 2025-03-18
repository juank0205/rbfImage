#include "image_handler.h"
#include "constants.h"

#include <iostream>
#include <stb_image.h>

ImageHandler::ImageHandler() {}
ImageHandler::~ImageHandler() {}

int ImageHandler::loadImageAsBits(const char *filename,
                                  std::array<unsigned char, INPUT_LAYER_SIZE> &bitData) {
  int channels, width, height;
  unsigned char *data = stbi_load(filename, &width, &height, &channels, 1);

  if (data == nullptr) {
    std::cerr << "Failed to load image: " << filename << std::endl;
    return 1;
  }

  if (width != IMAGE_WIDTH || height != IMAGE_HEIGHT) {
    std::cerr << "Image is not " << IMAGE_WIDTH << "x" << IMAGE_HEIGHT << std::endl;
    stbi_image_free(data);
    return 1;
  }

  for (int i = 0; i < INPUT_LAYER_SIZE; ++i) {
    bitData[i] = (data[i] == 0) ? 1 : 0; 
  }

  stbi_image_free(data);
  return 0;
}
