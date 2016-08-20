#ifndef MNIST_LOADER
#define MNIST_LOADER

#include <string>
#include <iostream>
#include <linux/limits.h> // for PATH_MAX
#include <fstream>

class mnist_loader {
  std::string labelFileName;
  std::string imageFileName;

  // Constants taken from MNIST site.
  const static int MMAGIC_OFFSET = 0;
  const static int OFFSET_SIZE = 4;

  const static int LABEL_MAGIC = 2049;
  const static int IMAGE_MAGIC = 2051;

  const static int NUMBER_ITEMS_OFFSET = 4;
  const static int ITEMS_SIZE = 4;

  const static int NUM_ROWS_OFFSET = 8;
  const static int ROWS_SIZE = 4;

  const static int NUM_COLS_OFFSET = 12;
  const static int COLS_SIZE = 4;

  const static int ROWS = 28;
  const static int COLS = 28;

  const static int IMAGE_OFFSET = 16;
  const static int IMAGE_SIZE = ROWS * COLS;

  public:
    // Constructor
    mnist_loader (std::string labelFileName, std::string imageFileName);

    // Getters
    std::string get_labelFileName ();
    std::string get_imageFileName ();

    // Load Files
    void load_labels ();
    void load_images ();
};

#endif
