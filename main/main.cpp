#include "neural_network.h"

int main(int argc, char *argv[]) {
  NeuralNetwork network("res/locations");
  // network.printNeurons();

  network.train("res/trainingImages");
  //network.printTrainingImages();

  return 0;
}
