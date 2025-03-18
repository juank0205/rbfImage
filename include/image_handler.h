#pragma once
#include <array>
#include "constants.h"

class ImageHandler {
public:
  ImageHandler();
  ~ImageHandler();
  
  int loadImageAsBits(const char *filename, std::array<unsigned char, INPUT_LAYER_SIZE> &bitData);
};
