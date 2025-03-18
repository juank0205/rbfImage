#include "neural_network.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <vec3.hpp>

NeuralNetwork::NeuralNetwork(const char *locationsDir) {
  loadLocations(locationsDir);
}

NeuralNetwork::~NeuralNetwork() {}

void NeuralNetwork::train(const char *imagesDir) {
  if (readImagesDir(imagesDir)) {
    std::cout << "Failed to load training data" << std::endl;
    return;
  }
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

  while (std::getline(inputFile, line) && trainingIndex < HIDDEN_LAYER_SIZE) {
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

  if (trainingIndex != HIDDEN_LAYER_SIZE) {
    std::cerr
        << "Warning: outputs.txt did not contain enough training data. Loaded: "
        << trainingIndex << " expected: " << HIDDEN_LAYER_SIZE << std::endl;
  }

  return 0;
}

void NeuralNetwork::printTrainingImages() {
  for (int i = 0; i < HIDDEN_LAYER_SIZE; ++i) {
    std::cout << "Training Image " << i << ":" << std::endl;

    // Print the image data (16x16 grid)
    std::cout << "Image Data:" << std::endl;
    for (int j = 0; j < 256; ++j) {
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

void NeuralNetwork::loadLocations(const char *locationsDir) {
  std::filesystem::path dirPath(locationsDir);
  int neuronIndex = 0;

  for (const auto &entry : std::filesystem::directory_iterator(dirPath)) {
    if (neuronIndex >= HIDDEN_LAYER_SIZE) {
      break; // Stop if we have loaded enough neurons
    }

    if (entry.is_regular_file() && entry.path().extension() == ".png") {
      int width, height;
      std::array<unsigned char, 256> imageData;

      if (m_imageHandler.loadImageAsBits(entry.path().string().c_str(),
                                         imageData)) {
        std::cerr << "Error: Failed to load image: " << entry.path().string()
                  << std::endl;
      }

      m_neurons[neuronIndex] = Neuron(imageData);
      neuronIndex++;
    }
  }

  if (neuronIndex != HIDDEN_LAYER_SIZE) {
    std::cerr << "Warning: Directory did not contain enough images. Loaded: "
              << neuronIndex << " expected: " << HIDDEN_LAYER_SIZE << std::endl;
  }
}

void NeuralNetwork::printNeurons() {
  for (auto neuron : m_neurons) {
    neuron.printLocation();
  }
}
