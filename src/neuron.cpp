#include "neuron.h"

#include <iostream>

Neuron::Neuron() {}

Neuron::~Neuron() {}
Neuron::Neuron(std::array<unsigned char, INPUT_LAYER_SIZE> location)
    : m_location(location) {}

double Neuron::activationFunction(
    const std::array<unsigned char, INPUT_LAYER_SIZE> &input) {
  return 0;
}

void Neuron::printLocation() {
  for (int i = 0; i < 256; ++i) {
    std::cout << static_cast<int>(m_location[i]);
    if ((i + 1) % 16 == 0) {
      std::cout << std::endl;
    }
  }
}
