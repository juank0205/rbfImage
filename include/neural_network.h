#pragma once

#include "constants.h"
#include "image_handler.h"
#include "neuron.h"

#include <array>
#include <Eigen/Dense>

struct TrainingData {
  std::array<unsigned char, 256> image;
  std::array<unsigned char, OUTPUT_LAYER_SIZE> outputs;
};

class NeuralNetwork {
public:
  NeuralNetwork(const char *locationsDir);
  ~NeuralNetwork();

  void train(const char *imagesDir);
  void classify(const char *inputImage);

  void printTrainingImages();
  void printNeurons();

private:
  ImageHandler m_imageHandler;
  std::array<TrainingData, HIDDEN_LAYER_SIZE> m_trainingImages;
  std::array<Neuron, HIDDEN_LAYER_SIZE> m_neurons;
  std::array<std::array<double, HIDDEN_LAYER_SIZE>, OUTPUT_LAYER_SIZE>
      m_weights;
  Eigen::MatrixXd m_weightsMat;
  std::array<std::array<double, HIDDEN_LAYER_SIZE>, INPUT_LAYER_SIZE>
      m_hiddenLayerActivationValues;
  bool m_areWeightsLoaded;

  int readImagesDir(const char *imagesDir); // rellenar training Images

  void fastForward();
  void solveWeightsMatrix();
  void loadLocations(const char *locationsDir);
  void saveWeights();
  void loadWeights();
};
