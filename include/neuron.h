#pragma once

#include "constants.h"

#include <array>

class Neuron {
public:
  Neuron(std::array<unsigned char, INPUT_LAYER_SIZE> location);
  Neuron();
  ~Neuron();

  double
  activationFunction(const std::array<unsigned char, INPUT_LAYER_SIZE> &input);

  void printLocation();
private:
  std::array<unsigned char, INPUT_LAYER_SIZE> m_location;
};
