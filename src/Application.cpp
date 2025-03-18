#include "application.h"
#include <iostream>

Application::Application() : m_neuralNetwork("res/locations") {}

Application::~Application() {}

void Application::start() { menu(); }

void Application::menu() {
  int option = -1;
  while (option != 0) {
    std::cout << "===== RBF Neural Network Menu =====\n"
              << "1. Train the network\n"
              << "2. Load weights from file\n"
              << "3. Classify input\n"
              << "0. Exit\n"
              << "Enter your choice: ";
    std::cin >> option;
  
    switch (option) {
      case 1: 
        handleTrain();
        break;
      case 2: 
        handleLoadWeights();
        break;
      case 3: 
        handleClassify();
        break;
      case 0:
        std::cout << "Seeya..." << std::endl;
        break;
      default:
        std::cout << "Select a valid option..." << std::endl;
        break;
    }
  }
}

void Application::handleTrain() {
  std::cout << "Training..." << std::endl;
  m_neuralNetwork.train("res/trainingImages");
}

void Application::handleLoadWeights() {
  std::cout << "Loading weights from file..." << std::endl;
  //TODO falta eso
}

void Application::handleClassify() {
  std::string filename;
  std::cout << "Enter the input file name: ";
  std::cin >> filename;
  std::cout << "Processing input..." << std::endl;
  m_neuralNetwork.classify(filename.c_str());
}
