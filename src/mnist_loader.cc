#include "mnist_loader.h"

// Constructor
mnist_loader::mnist_loader (std::string labelFileName, std::string imageFileName) :
  labelFileName(labelFileName), imageFileName(imageFileName) {}

// Getters
std::string mnist_loader::get_labelFileName () { return labelFileName; }
std::string mnist_loader::get_imageFileName () { return imageFileName; }

// Load Files
void mnist_loader::load_labels () {
  std::ifstream file(labelFileName);
  if ( file.is_open() ) {
    std::cout << "File opened." << std::endl;
  } else {
    std::cout << "File could not be opened." << std::endl;
  }
}
