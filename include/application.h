#pragma once

#include "neural_network.h"

class Application {
public:
  Application();
  ~Application();

  void start();

private:
  NeuralNetwork m_neuralNetwork;

  void menu();
  void handleTrain();
  void handleLoadWeights();
  void handleClassify();
};
