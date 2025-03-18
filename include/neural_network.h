#pragma once

#include "constants.h"
#include "image_handler.h"
#include "neuron.h"

#include <Eigen/Dense>
#include <array>

struct TrainingData {
  std::array<unsigned char, INPUT_LAYER_SIZE> image;
  std::array<unsigned char, OUTPUT_LAYER_SIZE> outputs;
};

class NeuralNetwork {
public:
  NeuralNetwork(const char *locationsDir);
  ~NeuralNetwork();

  void train(const char *imagesDir);
  int classify(const char *inputImage);

  void printTrainingImages();
  void printNeurons();

private:
  ImageHandler m_imageHandler;
  std::array<TrainingData, TRAINING_DATA_SIZE> m_trainingImages;
  std::array<Neuron, HIDDEN_LAYER_SIZE> m_neurons;
  Eigen::MatrixXd m_weightsMat;
  std::array<std::array<double, HIDDEN_LAYER_SIZE>, TRAINING_DATA_SIZE>
      m_hiddenLayerActivationValues;
  bool m_areWeightsLoaded;

  int readImagesDir(const char *imagesDir); // rellenar training Images
  int loadLocations(const char *locationsDir);
  void fastForward();
  void solveWeightsMatrix();
  void saveWeights();
  void loadWeights();
};
