#include "neural_network.h"
#include "constants.h"

#include <Eigen/Dense>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

NeuralNetwork::NeuralNetwork(const char *locationsDir) {
  loadLocations(locationsDir);
}

NeuralNetwork::~NeuralNetwork() {}

void NeuralNetwork::train(const char *imagesDir) {
  if (readImagesDir(imagesDir)) {
    std::cout << "Failed to load training data" << std::endl;
    return;
  }
  fastForward();
  solveWeightsMatrix();
  // TODO el resto
}

int NeuralNetwork::readImagesDir(const char *imagesDir) {
  std::string outputsFilePath = std::string(imagesDir) + "/outputs.txt";
  std::ifstream inputFile(outputsFilePath);

  if (!inputFile.is_open()) {
    std::cerr << "Error: Could not open outputs.txt in directory: " << imagesDir
              << std::endl;
    return 1;
  }

  std::string line;
  int trainingIndex = 0;

  while (std::getline(inputFile, line) && trainingIndex < TRAINING_DATA_SIZE) {
    std::stringstream ss(line);
    std::string filename, outputsStr;

    if (!std::getline(ss, filename, ',') || !std::getline(ss, outputsStr)) {
      std::cerr << "Error: Invalid line format in outputs.txt: " << line
                << std::endl;
      return 1;
    }

    std::string imageFilePath = std::string(imagesDir) + "/" + filename;

    int width, height;
    if (m_imageHandler.loadImageAsBits(imageFilePath.c_str(),
                                       m_trainingImages[trainingIndex].image)) {
      std::cerr << "Error: Failed to load image: " << imageFilePath
                << std::endl;
      return 1;
    }

    // Parse the output array
    outputsStr.erase(0, 1); // Remove '['
    outputsStr.pop_back();  // Remove ']'

    std::stringstream outputsSS(outputsStr);
    std::string outputVal;
    int outputIndex = 0;

    while (std::getline(outputsSS, outputVal, ',') &&
           outputIndex < OUTPUT_LAYER_SIZE) {
      m_trainingImages[trainingIndex].outputs[outputIndex] =
          static_cast<unsigned char>(std::stoi(outputVal));
      outputIndex++;
    }

    if (outputIndex != OUTPUT_LAYER_SIZE) {
      std::cerr << "Error: Incorrect number of outputs in line: " << line
                << std::endl;
      return 1;
    }

    trainingIndex++;
  }

  if (trainingIndex != TRAINING_DATA_SIZE) {
    std::cerr
        << "Warning: outputs.txt did not contain enough training data. Loaded: "
        << trainingIndex << " expected: " << TRAINING_DATA_SIZE << std::endl;
  }

  return 0;
}

void NeuralNetwork::printTrainingImages() {
  for (int i = 0; i < TRAINING_DATA_SIZE; ++i) {
    std::cout << "Training Image " << i << ":" << std::endl;

    // Print the image data (16x16 grid)
    std::cout << "Image Data:" << std::endl;
    for (int j = 0; j < INPUT_LAYER_SIZE; ++j) {
      std::cout << static_cast<int>(m_trainingImages[i].image[j]);
      if ((j + 1) % 16 == 0) {
        std::cout << std::endl;
      }
    }

    // Print the output array
    std::cout << "Outputs: [";
    for (int j = 0; j < OUTPUT_LAYER_SIZE; ++j) {
      std::cout << static_cast<int>(m_trainingImages[i].outputs[j]);
      if (j < OUTPUT_LAYER_SIZE - 1) {
        std::cout << ", ";
      }
    }
    std::cout << "]" << std::endl;
    std::cout << "------------------------" << std::endl;
  }
}

int NeuralNetwork::loadLocations(const char *locationsDir) {
  std::string outputsFilePath = std::string(locationsDir) + "/locations.txt";
  std::ifstream inputFile(outputsFilePath);

  if (!inputFile.is_open()) {
    std::cerr << "Error: Could not open locations.txt in directory: "
              << locationsDir << std::endl;
    return 1;
  }

  std::string line;
  int locationsIndex = 0;
  std::array<unsigned char, INPUT_LAYER_SIZE> locationBuffer;

  while (std::getline(inputFile, line) && locationsIndex < HIDDEN_LAYER_SIZE) {
    std::stringstream ss(line);
    std::string filename;

    if (!std::getline(ss, filename)) {
      std::cerr << "Error: Invalid line format in locations.txt: " << line
                << std::endl;
      return 1;
    }

    std::string imageFilePath = std::string(locationsDir) + "/" + filename;

    int width, height;
    if (m_imageHandler.loadImageAsBits(imageFilePath.c_str(), locationBuffer)) {
      std::cerr << "Error: Failed to load image: " << imageFilePath
                << std::endl;
      return 1;
    }
    m_neurons[locationsIndex] = Neuron(locationBuffer);

    locationsIndex++;
  }

  if (locationsIndex != HIDDEN_LAYER_SIZE) {
    std::cerr << "Warning: locations.txt did not contain enough data. Loaded: "
              << locationsIndex << " expected: " << HIDDEN_LAYER_SIZE
              << std::endl;
  }

  return 0;
}

void NeuralNetwork::printNeurons() {
  for (auto neuron : m_neurons) {
    neuron.printLocation();
  }
}

void NeuralNetwork::fastForward() {
  for (int i = 0; i < TRAINING_DATA_SIZE; i++) {
    for (int j = 0; j < HIDDEN_LAYER_SIZE; j++) {
      m_hiddenLayerActivationValues[i][j] =
          m_neurons[j].activationFunction(m_trainingImages[i].image);
    }
  }
  std::cout << "fastforward" << std::endl;
}

void NeuralNetwork::solveWeightsMatrix() {
  Eigen::MatrixXd hValues(TRAINING_DATA_SIZE, HIDDEN_LAYER_SIZE);
  for (int i = 0; i < TRAINING_DATA_SIZE; i++) {
    for (int j = 0; j < HIDDEN_LAYER_SIZE; j++) {
      hValues(i, j) = m_hiddenLayerActivationValues[i][j];
    }
  }
  std::cout << hValues << std::endl;
  Eigen::MatrixXd expectedValues(TRAINING_DATA_SIZE, OUTPUT_LAYER_SIZE);
  for (int i = 0; i < TRAINING_DATA_SIZE; i++) {
    for (int j = 0; j < OUTPUT_LAYER_SIZE; j++) {
      expectedValues(i, j) = m_trainingImages[i].outputs[j];
    }
  }
  std::cout << expectedValues << std::endl;
  std::cout << hValues.completeOrthogonalDecomposition().pseudoInverse()
            << std::endl;
  m_weightsMat = (hValues.completeOrthogonalDecomposition().pseudoInverse() *
                  expectedValues)
                     .transpose();
  std::cout << "matriz pesos\n" << m_weightsMat << std::endl;
}

int NeuralNetwork::classify(const char *inputImage) {
  std::array<unsigned char, INPUT_LAYER_SIZE> inputImageArr;

  if (m_imageHandler.loadImageAsBits(inputImage, inputImageArr)) {
    std::cout << "Failed to load image..." << std::endl;
    return -1;
  }

  Eigen::VectorXd activationValues(HIDDEN_LAYER_SIZE);
  for (int i = 0; i < HIDDEN_LAYER_SIZE; i++) {
    activationValues(i) = m_neurons[i].activationFunction(inputImageArr);
  }

  auto results = m_weightsMat * activationValues;
  std::cout << "Outputs: \n---------------------" << std::endl;
  std::cout << results << "\n";
  std::cout << "---------------------" << std::endl;

  double max = results[0];
  int maxIndex = 0;

  for (int i = 1; i < OUTPUT_LAYER_SIZE; i++) {
    if (results[i] > max) {
      max = results[i];
      maxIndex = i;
    }
  }

  return maxIndex;
}
