#include "neural_network.h"

int main(int argc, char *argv[]) {
  NeuralNetwork network("res/locations");
  // network.printNeurons();

  network.train("res/trainingImages");
  //network.printTrainingImages();
  network.classify("res/1prueba2.png");

  return 0;
}
