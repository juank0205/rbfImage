#include "image_handler.h"
#include <array>
#include <iostream>

void printBitArray(const std::array<unsigned char, 256> &bitArray) {
  for (int i = 0; i < 256; ++i) {
    std::cout << static_cast<int>(bitArray[i]);
    if ((i + 1) % 16 == 0) {
      std::cout << std::endl;
    }
  }
}

int main(int argc, char *argv[]) {
  ImageHandler image;
  std::array<unsigned char, 256> data;
  if (image.loadImageAsBits("res/1.png", data)) {
    std::cout << "Nosirvio" << std::endl;
  } else {
    printBitArray(data);
  }

  return 0;
}
