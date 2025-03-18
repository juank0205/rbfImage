#include "neural_network.h"
#include <Eigen/Dense>
#include <iostream>

int main(int argc, char *argv[]) {
  // NeuralNetwork network("res/locations");
  // // network.printNeurons();

  // network.train("res/trainingImages");
  // //network.printTrainingImages();
  // network.classify("res/5prueba.png");
  Eigen::MatrixXd m{{1, 1}, {0, 0}, {1, 1}};
  std::cout << m << "\n"
            << m.completeOrthogonalDecomposition().pseudoInverse() << std::endl;

  return 0;
}
