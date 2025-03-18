#include "neuron.h"

#include <iostream>

Neuron::Neuron() {}

Neuron::~Neuron() {}
Neuron::Neuron(std::array<unsigned char, INPUT_LAYER_SIZE> location)
    : m_location(location) {}


void Neuron::printLocation() {
  for (int i = 0; i < 256; ++i) {
    std::cout << static_cast<int>(m_location[i]);
    if ((i + 1) % 16 == 0) {
      std::cout << std::endl;
    }
  }
}

double Neuron::activationFunction(const std::array<unsigned char, INPUT_LAYER_SIZE> &input){
  double distance = 0;
  for(int i=0; i<256; i++){
    distance += pow(m_location[i]-input[i],2);
  }
  // distance = sqrt(distance);
  return exp(-distance/(2*NEURON_RADIUS));
}
