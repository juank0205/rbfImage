#pragma once
#include <array>

class ImageHandler {
public:
  ImageHandler();
  ~ImageHandler();
  
  int loadImageAsBits(const char *filename, std::array<unsigned char, 256> &bitData);
};
